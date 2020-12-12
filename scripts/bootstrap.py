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
import os.path

if find_os.is_windows:
    import glob
    microchip_toolchain_glob = glob.glob("C:/Microchip/*/arm-none-eabi-gcc/bin") +  glob.glob("C:/Microsemi/*/arm-none-eabi-gcc/bin")
    if microchip_toolchain_glob:
        microchip_toolchain_path = os.path.normpath(microchip_toolchain_glob[0])
        sys.path.extend(microchip_toolchain_path)
        os.environ['AR'] = os.path.join(microchip_toolchain_path, 'arm-none-eabi-ar.exe')
        os.environ['CC'] = os.path.join(microchip_toolchain_path, 'arm-none-eabi-gcc.exe')
        os.environ['CXX'] = os.path.join(microchip_toolchain_path, 'arm-none-eabi-g++.exe')
    else:
        os.environ['AR'] = 'arm-none-eabi-ar.exe'
        os.environ['CC'] = 'arm-none-eabi-gcc.exe'
        os.environ['CXX'] = 'arm-none-eabi-g++.exe'
else:
    os.environ['AR'] = 'arm-none-eabi-ar'
    os.environ['CC'] = 'arm-none-eabi-gcc'
    os.environ['CXX'] = 'arm-none-eabi-g++'

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
subprocess.run("git submodule update --init --recursive", shell=True, check=True)

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
    print("configuring...")
    subprocess.run(f'python waf configure --toolchain=arm-none-eabi- --enable-if-can --with-os=freertos --cflags "{optimization_flags}" --includes="{INCLUDES}"', shell=True, check=True)
    print("building...")
    subprocess.run('python waf build', shell=True, check=True)

finally:
    os.chdir(repository_dir)
