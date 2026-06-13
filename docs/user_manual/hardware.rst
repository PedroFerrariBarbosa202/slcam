.. hardware.rst

   Copyright The SLCam Contributors.

   SLCam Documentation

   This work is licensed under the Creative Commons Attribution-ShareAlike 4.0
   International License. To view a copy of this license,
   visit http://creativecommons.org/licenses/by-sa/4.0/.

********
Hardware
********

This chapter presents a description of the hardware project of the SLCam payload. As the primary reference, a block diagram can be seen in :numref:`fig:block-diagram`.

.. _fig:block-diagram:

.. figure:: img/block-diagram.*
      :width: 80%
      :align: center
      :alt: Block diagram 

      Block diagram of the SLCam hardware.

Como pode ser visto no diagrama de blocos, o projeto de hardware do módulo pode ser dividido em duas partes: o sensore de imagem, e a placa de controle da câmera.

The following sections present a further description of the hardware project.

Image Sensor
============

In :numref:`fig:arducam-block-diagram`, it is shown the architecture of the image sensor module, which is a FPGA featuring a FIFO off chip memory and the OmniVision OV2640 as the image sensor.

.. _fig:arducam:

.. figure:: img/arducam-2mp.png
      :width: 50%
      :align: center
      :alt: Arducam Mini 2MP

      Arducam Mini 2MP Plus.

.. _fig:arducam-block-diagram:

.. figure:: img/arducam-block-diagram.png
      :width: 100%
      :align: center
      :alt: Block diagram Arducam

      Architecture of the Arducam Mini 2MP Plus.

.. subfigure:: AB
    :layout-sm: A|B
    :gap: 8px
    :subcaptions: below
    :name: myfigure
    :class-grid: outline

    .. image:: img/arducam-top.jpg
        :width: 70%
        :align: center
        :alt: Top view.

    .. image:: img/arducam-bottom.jpg
        :width: 70%
        :align: center
        :alt: Bottom view.

    Arducam Mini 2MP Plus top and bottom view.

.. _fig:arducam-dimensions:

.. figure:: img/arducam-dimensions.png
      :width: 50%
      :align: center
      :alt: Arducam Mini 2MP Dimensions

      Arducam Mini 2MP Plus dimensions.

A connector 1x08 linking all pins from Arducam to the controller.

Controller Board
================

This section presents some detailed information about the controller board of the SLCam payload, which is a controller designed to integrate with the Arducam in the sattelite.

Peripherals
***********

.. note::
    TODO

Layout
******

The payload was designed with 4 layers **as shown in figure x** in the KiCAD v5 software.

It has a thickness of 1.6 mm and surface finish of **TBC**, it was also designed with material **TBC** and it has **TBC** PCB specs. 

.. note::
   TODO: Layers photos!

The controller is a 42.2 :math:`\times` 25.4 mm board containing four mount holes with 3.2 mm of diameter.

