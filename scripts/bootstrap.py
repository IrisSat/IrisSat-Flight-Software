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

