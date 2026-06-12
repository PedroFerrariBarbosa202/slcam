.. firmware.rst

   Copyright The SLCam Contributors.

   SLCam Documentation

   This work is licensed under the Creative Commons Attribution-ShareAlike 4.0
   International License. To view a copy of this license,
   visit http://creativecommons.org/licenses/by-sa/4.0/.

********
Firmware
********

This chapter describes the main characteristics of the firmware part of the SLCam module.

Product Tree
============

The product tree of the firmware part of the SLCam module is available in :numref:`fig:product-tree-fw`. This product tree follows the architecture of the firmware, being divided according to the firmware layers.

.. _fig:product-tree-fw:

.. figure:: img/product-tree-fw.*
      :width: 100%
      :align: center
      :alt: Firmware product tree 

      Product tree of the firmware of the SLCam module.

Layers
======

The firmware flow of development goes from the low-level implementation (far right), with HAL layer being register-level operation, to Tasks Layer with very abstract and high-level code.

Hardware Abstraction Layer (HAL)
********************************

The HAL layer is the API libopencm3 developed STMicroelectronics; it includes register manipulating functions to accelerate development. The SLCam uses HAL to handle GPIO operations and serial communications such as SPI, UART, and :math:`I^2C`.

Drivers
*******

Driver Layer is created to have the flexibility of the HAL layer but contains only the necessary abstraction to be still generic enough to support all the functionalities needed in Devices or other Drivers modules.

Devices
*******

In this level of abstraction, the devices are used to create specific configurations with the Drivers Layer to build functions used in the Tasks layer. In opposition to the Drivers layer, the Devices do not communicate between themselves and are only used inside Tasks.

RTOS
****

The SLCam uses FreeRTOS kernel. Using an RTOS-based kernel enables the system to regularly maintain routine functions such as housekeeping, sensor reading, checking for receptions, and dealing with specific delays used in hardware, such as the radio. The priority level of a task dictates who has the most preference for execution. Initial delay and period are used to determine the delay time to execute the task initialization after a boot; this regulates the time between the task executions. The stack is the amount of memory delimited to execute a task.

System
******

The System layer is used for housekeeping and management routines; it contains the system log. Its executions occur in almost all the SLCam abstraction layers (except the Tests layer), mostly for log purposes.

Tasks
*****

Tasks are the FreeRTOS threads equivalent and are the uppermost abstraction layer of code inside the SLCam flow of execution. Each task is designated a priority level, initial delay, period, and stack size as shown in :numref:`tab:firmware-tasks`.

.. _tab:firmware-tasks:

.. list-table:: List of SLCam Tasks with configuration parameters.
   :widths: 20 20 20 20 20
   :header-rows: 1

   * - **Name**
     - **Priority**
     - **Initial Delay [ms]**
     - **Period [ms]**
     - **Stack [bytes]**
   * - Startup
     - Highest
     - 0
     - Aperiodic
     - 300
   * - Watchdog Reset
     - Lowest
     - 0
     - 100
     - 150
   * - Heartbeat
     - Lowest
     - 2000
     - 500
     - 150
   * - System Reset
     - Medium
     - 0
     - 3600000
     - 150
   * - Time Control
     - Medium
     - 1000
     - 1000
     - 150
   * - CSP Server
     - TBD
     - 0
     - TBC
     - TBC

Each of the tasks presented in :numref:`tab:firmware-tasks` is described below:

* **Startup**: This task is the first executed task when the system starts. All devices, libraries, and data structures are initialized in this task. When the execution is done, the remaining tasks of the system are allowed to execute.
* **Watchdog Reset**: This task resets the internal watchdog timer at every 100 ms. The internal watchdog has a maximum count time of 500 ms.
* **Heartbeat**: The heartbeat task keeps blinking a LED at a rate of 1 Hz during the execution of the system. Its purpose is to give visual feedback on the execution of the scheduler. This task does not have a specific purpose on the flight version of the module (the flight version of the PCB does not have LEDs).
* **System Reset**: This task resets the microcontroller by software every hour. This can be useful to clean up possible wrong values in variables, clean up the RAM, etc.
* **Time Control**: This task is responsible for the time management of the system. At every second, it increments the system time (epoch). Also, it saves the current system time in the non-volatile memory every minute.
* **CSP Server**: TODO.

Libraries
*********

The Libraries are used for algorithm purposes and are not related to any hardware. Their function removes the redundancy of creating multiple identical structures for different driver modules.

Tests
*****

Tests are used to verify and validate the Drivers and Devices' developed functionality. There are three types of tests: the static test uses the MISRA C: 2012 :cite:`misrac2012` guidelines to check for C safety standards, the unitary tests use the Cmocka :cite:`cmocka` library with mockups of the hardware, to validate the module in an algorithmic level, and the last test verifies the integration between hardware and firmware.
