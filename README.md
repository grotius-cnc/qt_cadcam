# QT_cadcam

This is a project i worked on. It's my first C++ project, not as good as Draftsight at this stage. 
The program is usable and i think i will write a brand new code in the future now my knowlegde in C++ and mathematics has improved.

The spline function has to be replaced, the cam engrave text function has to be improved. 
A perfect cubic-spline function is over here : https://github.com/grotius-cnc/cadcam/blob/master/opengl.cpp

The dxf read function's can be improved. A better dxf read in function is over here : https://github.com/grotius-cnc/cadcam/tree/master/dxf, it also read in splines and ellipses.

When the program is compiled, place the cadcam directory inside the directory where the ./cadcam executable lives.
This cadcam directory includes user defined settings like : layers, linetypes, colors etc.

The cadcam program is able to print the drawing as pdf or png format in a4,a3,a1,a0 dimensions.

For deployement i advice to use appimage. Look at their website. It's not complicated att all.

![](https://raw.githubusercontent.com/grotius-cnc/QT_cadcam/master/cadcam_screenshot.png)

![](https://raw.githubusercontent.com/grotius-cnc/QT_cadcam/master/cadcam_screenshot_gcode.png)

build on linux :
Qt Creator 4.8.2
Based on Qt 5.9.8 (GCC 5.3.1 20160406 (Red Hat 5.3.1-6), 64 bit)
