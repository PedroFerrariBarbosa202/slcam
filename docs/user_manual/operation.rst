.. operation.rst

   Copyright The SLCam Contributors.

   SLCam Documentation

   This work is licensed under the Creative Commons Attribution-ShareAlike 4.0
   International License. To view a copy of this license,
   visit http://creativecommons.org/licenses/by-sa/4.0/.

*********
Operation
*********

Parameters
==========

.. _tab:parameters:

.. list-table:: List of parameters.
   :widths: 10 40 15 15 20
   :header-rows: 1

   * - **ID**
     - **Name**
     - **Access**
     - **Type**
     - **Length [bytes]**
   * - 0
     - Firmware version
     - Read
     - uint16
     - 2
   * - 1
     - Hardware version
     - Read
     - uint16
     - 2
   * - 2
     - System Time
     - Read/Write
     - uint32
     - 4
   * - 3
     - Reset Counter
     - Read
     - uint32
     - 4
   * - 4
     - Number of Images in Buffer
     - Read
     - uint16
     - 2

Commands
========

To externally control and access the SLCam module, some commands are available through the serial interfaces of the board. A list with the commands is available in :numref:`tab:commands`. The format of the commands' answers can be seen in :numref:`tab:commands-ans`.

.. _tab:commands:

.. list-table:: List of commands.
   :widths: 10 30 40 20
   :header-rows: 1

   * - **ID**
     - **Name**
     - **Content**
     - **Interface**
   * - 0
     - Read Parameter
     - TBD
     - SPI, CAN
   * - 1
     - Write Parameter
     - TBD
     - SPI, CAN
   * - 2
     - Read Image
     - TBD
     - SPI, CAN

.. _tab:commands-ans:

.. list-table:: Format of the command's answers.
   :widths: 10 45 45
   :header-rows: 1

   * - **ID**
     - **Name**
     - **Content**
   * - 1
     - TBD
     - TBD
