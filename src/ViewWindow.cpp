#include "ViewWindow.hpp"

ViewWindow::ViewWindow() {
    x_min=0; x_max=0;
    y_min=0; y_max=0;
    x_range=0; y_range=0;
    x_center=0; y_center=0;
}

ViewWindow::ViewWindow(float _x_min, float _x_max, float _y_min, float _y_max) {
    x_min = _x_min, x_max = _x_max;
    y_min = _y_min, y_max = _y_max;
    x_range = x_max - x_min; y_range = y_max - y_min;
    x_center = x_min + x_range/2; y_center = y_min + y_range/2;
}

void ViewWindow::scale(float ratio){
    x_range *= ratio; y_range *= ratio;
    x_min = x_center - (x_range/2); x_max = x_center + (x_range/2);
    y_min = y_center - (y_range/2); y_max = y_center + (y_range/2);
}

void initWindow(int width, int height, std::string windowName, void (*display)(void), void (*reshape)(int, int)){
    int argc = 1;
    char *argv[1] = {(char*)"dummy"};
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(windowName.c_str());
    glutDisplayFunc(display);
    glutReshapeFunc(reshape); 
}

void fitReshape(GLsizei width, GLsizei height){
    if (height == 0) height = 1;
    GLfloat winRatio = (GLfloat)width / (GLfloat)height;
    GLfloat viewRatio = (GLfloat)view_window.x_range / (GLfloat)view_window.y_range;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (viewRatio > winRatio) {
        gluOrtho2D(view_window.x_min, view_window.x_max, view_window.y_center - (view_window.x_range/winRatio)/2, view_window.y_center + (view_window.x_range/winRatio)/2);
    } else {
        gluOrtho2D(view_window.x_center - (view_window.y_range*winRatio)/2, view_window.x_center + (view_window.y_range*winRatio)/2, view_window.y_min, view_window.y_max);
    }
}