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
It is easy to do this process in WSL:

```
sudo apt install gcc-arm-none-eabi
```
python is probably already installed.


Navigate to the libcsp folder and run the build script which will configure, build and install the library.

To run the build script:
```
./build.sh 'path/to/iris-fsw-softconsole'  -Os -g
```
If you are running this from the libcsp folder in the iris-fsw-softconsole project then the command is:

```
./build.sh ../.. -Os -g
```

The first argument should be the path to the softconsole project, and the remaining arguments
should be the compilation flags.

-Os optimizes for size, and -g includes debug symbols. This combination has been tested.
-O0 will not include any optimization, useful for debugging.

