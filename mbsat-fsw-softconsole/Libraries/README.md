#Manitoba-Sat Flight Software Libraries

This folder contains the software dependancies used by the ManitobaSat flight software.

## Cubesat Space Protocol

This library is provides a communication protocol stack following the TCP/IP model. The MBSat flight software uses the CSP library for communication with the communication system on the satellite.

The CSP library is built and linked as a static library.

The project setting have been modified to include the binary in the build. (-lcsp)

The project must be ran from flash whenever CSP is used since the library and code together do not fit in RAM.

A binary is included in the project, along with a modified build script for use if the library must be rebuilt.

###To build the library:




