# Flight Software for IrisSat
This repository contains software for the IrisSat Command and Data Handling (CDH) board. The directory structure is like so:
- /iris-fsw-libero contains the Libero project required for configuring the device.
- /iris-fsw-softconsole contains the SoftConsole project required to write and debug the software.


## Build Steps

Git submodules are used in this project. Use the command "git submodule update --init" to make sure you have the submodule files.

The CSP library used in this project must be built before the software can be compiled.
Follow the instructions in iris-fsw-softconsole/Libraries/ to build the library.

Also the "Production" build of the softconsole project should be compiled before the Libero project is built because the Libero project will include the firmware binary as part of the FPGA image.


### Required hardware
This project requires the Microsemi Smartfusion2 Maker Board.

### Required Software
This project requires SoftConsole 6.1 and Libero 12.1.
### Configure your workspace
1. Select the root folder (i.e. IrisSat-Flight-Software) as your SoftConsole workspace.
2. Go to **File -> Import**.
3. On the Import window, select **General -> Existing C/C++ Projects into Workspace**.
4. Add "iris-fsw-softconsole" to your workspace. 

### Build
5. To build the SoftConsole project, go to **Project -> Build All**, or use **Ctrl-B**.

### Configure FPGA
6. Open the \*.prjx found in iris-fsw-libero, with Libero 12.1.
7. Connect the MSR board to the computer.
8. In the "Design Flow" panel on the left, double-click "Synthesize".
9. In the "Design Flow" panel on the left, double-click "Manage Constraints" and make sure  constraint\io\user.pdc is selected.
10. In the "Design Flow" panel on the left, double-click "Generate FPGA Array Data".
11. In the "Design Flow" panel on the left, double-click "Update eNVM Memory Content", double-click on the Data Storage client and select iris-fsw-softconsole/Production/iris-fsw-softconsole.hex as the content file.
12. In the "Design Flow" panel on the left, double-click "Run PROGRAM Action".

### Debug 
13. Go to **Run -> Debug Configurations**.
14. Double-click **GDB OpenOCD Debugging** to create a new Debugging configuration.
15. Under the "Main" tab, browse and select the "iris-fsw-softconsole" project as the project.
16. Under the "Debugger" tab, change the Config options to: **"--command "set DEVICE M2S010" --file board/microsemi-cortex-m3.cfg"**
17. Under the "Startup" tab, make sure that "Pre-run/Restart reset" is not checked.
18. With the MSR board connected, click "Apply", and then "Debug" to run the software.

*Also if the Libero project is modified, the firmware should be regenerated and copied to the softconsole project. Note that the CoreSPI firmware must be generated from the Microsemi Firmware Catalog and copied to the firmware folder in the softconsole project* 

## Software Dependancies:

### Cubesat Space Protocol (CSP)

This library is provides a communication protocol stack following the TCP/IP model. The MBSat flight software uses the CSP library for communication with the communication system on the satellite.



## Useful links:
1. Maker Board IoT Demo project: https://www.digikey.com/eewiki/display/microcontroller/Getting+Started+with+the+Microsemi+SmartFusion+2+Maker-Board
2. Maker Board "First Project" Demo: https://github.com/tstana/M2S010-MKR-KIT_FirstProj/wiki

