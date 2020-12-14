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
import os.path

# Set cwd
print("Changing current working directory to the repository root")
repository_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(repository_dir)

softconsole_path = "./iris-fsw-softconsole"
libraries_path = "./iris-fsw-softconsole/Libraries"

################################################################
# Environment variables
import utils

if utils.is_windows:
    import glob
    microchip_toolchain_glob = glob.glob("C:/Microchip/*/arm-none-eabi-gcc/bin") + glob.glob("C:/Microsemi/*/arm-none-eabi-gcc/bin")
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
import utils

# FreeRTOS
version_FREERTOS = "V9.0.0"
utils.download_git_branch(version_FREERTOS, "https://github.com/FreeRTOS/FreeRTOS-Kernel", libraries_path, "FreeRTOS-Kernel")

freertos_kernel_folder = os.path.join(libraries_path, 'FreeRTOS-Kernel')

# this is not needed for V10
if version_FREERTOS == "V9.0.0":
    # Move files to workaround the old folder structure of FreeRTOS-Kernel
    import shutil
    import pathlib
    source_folder = os.path.join(freertos_kernel_folder, 'FreeRTOS', 'Source')
    shutil.move(source_folder, libraries_path)     # move source content temporarily

    # Delete unneeded files
    shutil.rmtree(freertos_kernel_folder, ignore_errors=True)
    shutil.rmtree(os.path.join(freertos_kernel_folder, 'FreeRTOS'), ignore_errors=True)
    shutil.rmtree(os.path.join(freertos_kernel_folder, 'FreeRTOS-Plus'), ignore_errors=True)
    pathlib.Path(freertos_kernel_folder).mkdir(parents=True, exist_ok=True)

    # move content of source to freertos kernel folder
    source_temp_dir = os.path.join(libraries_path, 'Source')
    source_content = os.listdir(source_temp_dir)
    for file in source_content:
        shutil.move(os.path.join(source_temp_dir, file), os.path.join(freertos_kernel_folder, file))
    os.rmdir(source_temp_dir)


# remove portable directories not needed for Arm CORTEX M3
portable_folder = os.path.join(freertos_kernel_folder, 'portable')
portable_content = os.listdir(portable_folder)
for file in portable_content:
    if file != "portable" and file != "GCC" and file != "MemMang":
        shutil.rmtree(os.path.join(portable_folder, file), ignore_errors=True)

gcc_folder = os.path.join(portable_folder, "GCC")
gcc_content = os.listdir(gcc_folder)
for file in gcc_content:
    if file != "GCC" and file != "ARM_CM3":
        shutil.rmtree(os.path.join(gcc_folder, file), ignore_errors=True)


# Use heap_4.c from MemMang
memmang_folder = os.path.join(portable_folder, "MemMang")
memmang_content = os.listdir(memmang_folder)
for file in memmang_content:
    if file != "MemMang" and file != "heap_4.c":
        os.remove(os.path.join(memmang_folder, file))

################################################################
# libcsp

print("Building libcsp...")
try:
    project_path = "../.."
    INCLUDES = f"{project_path}/include,"
    INCLUDES += f"{project_path}/Libraries,"
    INCLUDES += f"{project_path}/Libraries/FreeRTOS-Kernel,"
    INCLUDES += f"{project_path}/Libraries/FreeRTOS-Kernel/include,"
    INCLUDES += f"{project_path}/Libraries/FreeRTOS-Kernel/portable,"
    INCLUDES += f"{project_path}/Libraries/FreeRTOS-Kernel/portable/GCC/ARM_CM3,"

    os.chdir(f"{libraries_path}/libcsp")
    print("configuring...")
    subprocess.run(f'python waf configure --toolchain=arm-none-eabi- --enable-if-can --with-os=freertos --cflags "{optimization_flags}" --includes="{INCLUDES}"', shell=True, check=True)
    print("building...")
    subprocess.run('python waf build', shell=True, check=True)

finally:
    os.chdir(repository_dir)
