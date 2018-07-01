#include <GL/glut.h>
#include <string>
#include <iostream>

using namespace std;

struct ViewWindow {
    float x_min, x_max;
    float y_min, y_max;
    float x_range, y_range;
    float x_center, y_center;

    ViewWindow();
    ViewWindow(float, float, float, float);
    void scale(float);
};

void initWindow(int, int, std::string, void (*)(void), void (*)(int, int));

void fitReshape(GLsizei width, GLsizei height);

extern ViewWindow view_window;