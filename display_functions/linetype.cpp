#include "linetype.h"
#include <core_functions/variables.h>
#include <QByteArray>
#include <bits/stdc++.h>
#include <QBitArray>
#include <string>
#include <core_functions/variables.h>
using namespace std;

linetype::linetype(int i)
{  

    //    The line stipple pattern is just a 16-bit integer. So to get 6 dots followed by a short line, the pattern in binary could look like this:
    //    0101010101010111
    //    Splitting this into 4-bit groups gives:
    //    0101 0101 0101 0111
    //    And then converting each group to its hex digit:
    //    0x5557
    //    Which gives us the following call:
    //    glLineStipple(1, 0x5557);

    if(mode_cad){
        glLineStipple(double_cad_array[i][18] , int_cad_array[i][5]); //
    }
    if(mode_cam){
        glLineStipple(double_cam_array[i][18] , int_cam_array[i][5]); //
    }

}
