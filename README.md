# Command and Data Handling (CDH) for TSAT5
This repository contains software for the TSAT5 (2018-2020) Command and Data Handling (CDH) board. The directory structure is like so:
- /cdh-tsat5-libero contains the Libero project required for configuring the device.
- /cdh-tsat5-softconsole contains the SoftConsole project required to write and debug the software.


## Build Steps

### Required hardware
This project requires the Microsemi Smartfusion2 Maker Board.

### Required Software
This project requires SoftConsole 4.0 and Libero 11.9.2.

### Configure FPGA
1. Open the \*.prjx found in cdh-tsat5-libero, with Libero 11.9.2.
2. Connect the MSR board to the computer.
3. In the "Design Flow" panel on the left, double-click "Run PROGRAM Action".

### Configure your workspace
4. Select the root folder (i.e. cdh-tsat5) as your SoftConsole workspace.
5. Go to **File -> Import**.
6. On the Import window, select **General -> Existing C/C++ Projects into Workspace**.
7. Add "cdh-tsat5-softconsole" to your workspace. 

### Build and Debug
8. To build the SoftConsole project, go to **Project -> Build All**, or use **Ctrl-B**.
9. Go to **Run -> Debug Configurations**.
10. Double-click **GDB OpenOCD Debugging** to create a new Debugging configuration.
11. Under the "Main" tab, browse and select the "cdh-tsat5-softconsole" project as the project.
12. Under the "Debugger" tab, change the Config options to: **"--command "set DEVICE M2S010" --file board/microsemi-cortex-m3.cfg"**
12. With the MSR board connected, click "Apply", and then "Debug" to run the software.

## Licensing
This project is available under GNU General Public License v3.0 (GPL-3.0-or-later).

## Useful links:
1. Maker Board IoT Demo project: https://www.digikey.com/eewiki/display/microcontroller/Getting+Started+with+the+Microsemi+SmartFusion+2+Maker-Board
2. Maker Board "First Project" Demo: https://github.com/tstana/M2S010-MKR-KIT_FirstProj/wiki

## About UMSATS
UMSATS is a student driven group that works to build 3U nanosatellites to compete in the Canadian Satellite Design Challenge (CSDC). Our website can be found here: http://www.umsats.ca/
