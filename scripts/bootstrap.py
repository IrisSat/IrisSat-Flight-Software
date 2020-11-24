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
fileDir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(fileDir)

is_windows = (os.name == 'nt' or (os.getenv('SYSTEMROOT') is not None and 'windows' in os.getenv('SYSTEMROOT').lower()) or (os.getenv('COMSPEC') is not None and 'windows' in os.getenv('COMSPEC').lower()))

softconsole_path = "./iris-fsw-softconsole"
libraries_path = "./iris-fsw-softconsole/Libraries"

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
subprocess.run(f"{libraries_path}/libcsp/build.sh {softconsole_path} {optimization_flags}", shell=True)
