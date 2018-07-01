#include<GL/gl.h>
#include<vector>

using namespace std;

struct glLine {
    GLfloat color[4];
    GLfloat vertA[3];
    GLfloat vertB[3];
    GLfloat width;
};

void drawLines(vector<glLine> draw_list);