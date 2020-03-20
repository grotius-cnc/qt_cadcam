#include "origin.h"
#include <core_functions/variables.h>

origin::origin()
{
    //x origin line
       glLineWidth(1);
       glColor3f(0.0f, 1.0f, 0.0f); //green
       glBegin(GL_LINES);
       glVertex3d(0, 0, 0);  //start
       glVertex3d(25, 0, 0);  //end
       glEnd();

       //x origin cone
       double x;
       double y;
       int height = 5;
       int radius = 2;
       double angle = (2*M_PI)/8;

       glPushMatrix(); //add invidual item
       glTranslated(25,0,0);
       glRotated(90,0,1,0);

       glBegin(GL_TRIANGLE_STRIP);
           for(int sides = 0; sides <= 8 ; sides++ ) {
               x = radius * cos(angle);
               y = radius * sin(angle);
               angle = angle + (2*M_PI)/8;
               glVertex3d(x, y , 0);
               glVertex3d(0, 0 , height);
           }
       glEnd();
       glPopMatrix(); //pop invidual item

       //y origin line
       glColor4f(1.0f, 0.0f, 0.0f, 0.0f); //red
       glBegin(GL_LINES);
       glVertex3d(0, 0, 0);  //start
       glVertex3d(0, 25, 0);  //end
       glEnd();

       //y origin cone
       glPushMatrix(); //add invidual item
       glTranslated(0,25,0);
       glRotated(-90,1,0,0);

       glBegin(GL_TRIANGLE_STRIP);
           for(int sides = 0; sides <= 8 ; sides++ ) {
               x = radius * cos(angle);
               y = radius * sin(angle);
               angle = angle + (2*M_PI)/8;
               glVertex3d(x, y , 0);
               glVertex3d(0, 0 , height);
           }
       glEnd();
       glPopMatrix(); //pop invidual item

       //z origin line
       glColor3f(0.0f, 0.0f, 1.0f); //blue
       glBegin(GL_LINES);
       glVertex3d(0, 0, 0);  //start
       glVertex3d(0, 0, 25);  //end
       glEnd();

       //z origin cone
       glPushMatrix(); //add invidual item
       glTranslated(0,0,25);
       glRotated(0,1,0,0);

       glBegin(GL_TRIANGLE_STRIP);
           for(int sides = 0; sides <= 8 ; sides++ ) {
               x = radius * cos(angle);
               y = radius * sin(angle);
               angle = angle + (2*M_PI)/8;
               glVertex3d(x, y , 0);
               glVertex3d(0, 0 , height);
           }
       glEnd();
       glPopMatrix(); //pop invidual item
}
