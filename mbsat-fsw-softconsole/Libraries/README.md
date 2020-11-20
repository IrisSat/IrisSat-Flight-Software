# Manitoba-Sat Flight Software Libraries

This folder contains the software dependencies used by the IrisSat flight software.

[Cubesat Space Protocol](#cubesat-space-protocol])


## Cubesat Space Protocol

This library is provides a communication protocol stack following the TCP/IP model. The MBSat flight software uses the CSP library for communication with the communication system on the satellite.

The CSP library is built and linked as a static library (binary).
The project settings have been modified to include the binary in the build. (-lcsp)
The project must be ran from flash whenever CSP is used since the library and code together do not fit in RAM.
A binary is included in the project, along with a modified build script for use if the library must be rebuilt.

### To build the library:

To build the library, you need the arm-none-eabi-gcc toolchain, and python3.

Start by getting the library from:
https://github.com/joehowarth17/libcsp.git

Make any changes to the library if necessary.

Next, run the build script which will configure, build and install the library.

To run the build script:
```
./build.sh 'path/to/mbsat-fsw-softconsole'  -Os -g
```
The first argument should be the path to the softconsole project, and the remaining arguments
should be the compilation flags.

-Os optimizes for size, and -g includes debug symbols. This combination has been tested.
-O0 will not include any optimization, useful for debugging.

The script will move the static library to the location:
```
path/to/mbsat-fsw-softconsole/Libraries/CSP
```
If changes were made to the source code, the modified files should manually be moved to the softconsole project, so that the correct files are used when debugging.
