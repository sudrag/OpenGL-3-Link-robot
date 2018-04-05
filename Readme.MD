## Overview
A 3 linked robotic manipulator where:

* The base rotates around the Y and Z axes.
* The elbow joint rotates only around the Z axis.
* The end effector rotates around the X and Z axes.

## To run

These instructions are written for an Ubuntu system where OPENGL libraries are preinstalled. The makefile is included in the repo. Once you clone it run
```
make && ./main
```
  
Once the window appears the robot in controlled using the following keys:
To increase and decrease the respective values for:
* Y axis of base  - `q` and `a`
* Z axis of base  - `w` and `s`
* Z axis of elbow - `e` and `d`
* Z axis of ee    - `r` and `f`
* X axis of ee    - `t` and `g` 
* Zoom in and out - `↑`and `↓` 
* Rotate camera   - `←`and `→` 

![Screenshot](https://github.com/sudrag/OpenGL-3-Link-robot/blob/master/pic.png)

