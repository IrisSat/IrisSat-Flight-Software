# Flight Software for ManitobaSat
This repository contains software for the ManitobaSat Command and Data Handling (CDH) board. The directory structure is like so:
- /mbsat-fsw-libero contains the Libero project required for configuring the device.
- /mbsat-fsw-softconsole contains the SoftConsole project required to write and debug the software.


## Build Steps

### Required hardware
This project requires the Microsemi Smartfusion2 Maker Board.

### Required Software
This project requires SoftConsole 6.1 and Libero 12.1.

### Configure FPGA
1. Open the \*.prjx found in mbsat-fsw-libero, with Libero 12.1.
2. Connect the MSR board to the computer.
3. In the "Design Flow" panel on the left, double-click "Run PROGRAM Action".

### Configure your workspace
4. Select the root folder (i.e. ManitobaSat-Flight-Software) as your SoftConsole workspace.
5. Go to **File -> Import**.
6. On the Import window, select **General -> Existing C/C++ Projects into Workspace**.
7. Add "mbsat-fsw-softconsole" to your workspace. 

### Build and Debug
8. To build the SoftConsole project, go to **Project -> Build All**, or use **Ctrl-B**.
9. Go to **Run -> Debug Configurations**.
10. Double-click **GDB OpenOCD Debugging** to create a new Debugging configuration.
11. Under the "Main" tab, browse and select the "mbsat-fsw-softconsole" project as the project.
12. Under the "Debugger" tab, change the Config options to: **"--command "set DEVICE M2S010" --file board/microsemi-cortex-m3.cfg"**
13. Under the "Startup" tab, make sure that "Pre-run/Restart reset" is not checked.
14. With the MSR board connected, click "Apply", and then "Debug" to run the software.


## Useful links:
1. Maker Board IoT Demo project: https://www.digikey.com/eewiki/display/microcontroller/Getting+Started+with+the+Microsemi+SmartFusion+2+Maker-Board
2. Maker Board "First Project" Demo: https://github.com/tstana/M2S010-MKR-KIT_FirstProj/wiki

