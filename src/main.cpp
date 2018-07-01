#include"LSystem.hpp"

LSystem lsys;
ViewWindow view_window;

void drawlsys(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f,1.0f,1.0f, 1.0f);
    
    lsys.draw();

    glFlush();
}

int main(int argc, char *argv[]) {
    lsys.construct();
    view_window = lsys.generateViewWindow();
    view_window.scale(1.1);

    // cout << view_window.x_min << " " << view_window.x_max << " " << view_window.y_min << " " << view_window.y_max << endl;

    initWindow(500,500,"L-System",drawlsys,fitReshape);

    drawlsys();

    glutMainLoop();
    return 0;
}