## Overview

Flexible Software Package (FSP) for Renesas RZ/A MPU Series

FSP is the next generation Arm® MPU software package from Renesas, that enables HMI devices and IoT connectivity through production ready peripheral drivers, FreeRTOS, and portable middleware stacks.
FSP includes best-in-class HAL drivers with high performance and low memory footprint. Middleware stacks with FreeRTOS integration are included to ease implementation of complex modules like communication.
The e² studio IDE provides support with intuitive configurators and intelligent code generation to make programming and debugging easier and faster.

FSP uses an open software ecosystem and provides flexibility in using your preferred RTOS, legacy code, and third-party ecosystem solutions.

### Current Release

[FSP v1.0.0](https://github.com/renesas/rza-fsp/releases/tag/v1.0.0)

### Supported RZ/A MPU Kits

- [RZ/A3UL Evaluation Board Kit](https://www.renesas.com/products/microcontrollers-microprocessors/rz-mpus/rza3ul-evaluation-board-kit-rza3ul-evaluation-board-kit)

### Known Issues

N/A

### Setup Instractions
<!--##### For existing users that are using RZ/A FSP with e² studio-->

- FSP versions of 1.0.0 and later require a minimum e² studio version of 2022-07.

If you have already installed a previous FSP release that included e² studio then you can download the packs separately. These are available for download under the Assets section for each release. There is a zipped version, FSP_Packs_\<version\>.zip, and an installer version, FSP_Packs_\<version\>.exe.

<!--
##### For new users that are using
1. Download the FSP with e² studio Installer from the Assets section of the [current release](https://github.com/renesas/rza-fsp/releases/tag/v1.0.0).
2. Run the installer. This will install the e² studio tool, FSP packs, GCC toolchain and other tools required to use this software. No additional installations are required.
-->

### Starting Development ###

1. Open e² studio and click File > New > C/C++ Project.
2. In the window that pops up, choose Renesas RZ/A in the left pane.

### Related Links

FSP Releases :  https://github.com/renesas/rza-fsp/releases

Documentation : https://renesas.github.io/rza-fsp

RZ/A Initial Program Loader : https://github.com/renesas/rza-initial-program-loader

RZ/A3UL Product Information : www.renesas.com/rza3ul

e² studio : www.renesas.com/e2studio

Support : www.renesas.com/support