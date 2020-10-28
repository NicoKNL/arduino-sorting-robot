# 2IO70 DBL Embedded Systems
This repository contains the work done by group *Not Full Nerds* for the TU/e in quartile 3 of 2019-2020.

# Overview
The goal of the project was to create an autonymous system which could:
* Attach to, and operate on, an existing factory belt system which transports black and white disks
* Recognize disk presence
* Recognize disk color
* Take disks from the factory
* And sort the disks into bins based on color

# Demo video
*Click to watch the video.*
[![Watch the video](https://img.youtube.com/vi/2bJaizOmCdo/maxresdefault.jpg)](https://youtu.be/2bJaizOmCdo)

# Hardware
The basis for the hardware consists of fischertechnik components. The Raspberry Pi platform is the main platform for the software. We also used additional components such as custom 3d printed parts, servos, stepper motor. Much of the interfacing between the software and hardware is achieved by linking the Raspberry Pi, through its GPIO, to Arduino controllers.

# Software
The core of the logic is set up in Dezyne, allowing for extensive model testing. Dezyne takes care of basic C++ code generation which represents the (validated and tested) model. 
