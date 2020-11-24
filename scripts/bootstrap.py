# Check python version
import sys
if not (sys.version_info.major == 3 and sys.version_info.minor >= 6):
    print("This script requires Python 3.6 or higher!")
    print("You are using Python {}.{}.".format(sys.version_info.major, sys.version_info.minor))
    sys.exit(1)

################################################################
# Script flags
import argparse
parser = argparse.ArgumentParser()

# Options:
parser.add_argument("--debug", dest="is_debug", default=False, help="Enable debug build")

# Parse arguments
args = parser.parse_args()

################################################################
# Paths
import os
from os.path import abspath

# Set cwd
print("Changing current working directory to the repository root")
repository_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(repository_dir)

softconsole_path = "./iris-fsw-softconsole"
libraries_path = "./iris-fsw-softconsole/Libraries"

################################################################
# Environment variables
import find_os

if find_os.is_windows:
    os.environ['CC'] = 'gcc.exe'
    os.environ['CXX'] = 'g++.exe'
else:
    os.environ['CC'] = 'gcc'
    os.environ['CXX'] = 'g++'

################################################################
# Optimization Flags

optimization_flags = "-O3"  # Release build: enable all optimizations

if args.is_debug:
    optimization_flags = "-O0 -g"  # Debug: enable debug flags and disable all optimizations

################################################################
# Bootstrapping dependencies
import subprocess
################################################################
# Submodules
print("Downloading submodules...")
subprocess.run("git submodule update --init --recursive", shell=True)

################################################################
# libcsp

print("Building libcsp...")
try:
    project_path = "../.."
    INCLUDES = f"{project_path}/FreeRTOS,"
    INCLUDES += f"{project_path}/FreeRTOS/FreeRTOS-Source,"
    INCLUDES += f"{project_path}/FreeRTOS/FreeRTOS-Source/include,"
    INCLUDES += f"{project_path}/FreeRTOS/FreeRTOS-Source/portable,"
    INCLUDES += f"{project_path}/FreeRTOS/FreeRTOS-Source/portable/GCC/ARM_CM3,"

    os.chdir(f"{libraries_path}/libcsp")
    subprocess.run(f'python waf configure --toolchain=arm-none-eabi- --enable-if-can --with-os=freertos --cflags "{optimization_flags}" --includes="{INCLUDES}"', check=True)
    subprocess.run('python3 waf build', check=True)
    os.remove(f"{project_path}/Libraries/CSP/libcsp.a")  # remove the old file

    from shutil import copyfile
    copyfile("build/libcsp.a", f"{project_path}/Libraries/CSP/libcsp.a")

finally:
    os.chdir(repository_dir)
