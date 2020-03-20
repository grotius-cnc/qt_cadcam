#ifndef CAM_TEXT_H
#define CAM_TEXT_H
#include <QString>

class cam_text
{
public:
    cam_text();
    void draw_text(QString text);
    void load_text(double scale, QString filename);

};

#endif // CAM_TEXT_H
