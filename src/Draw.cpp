#include"Draw.hpp"
#include<iostream>

void drawLines(vector<glLine> draw_list){
    glBegin(GL_LINES);
    for(unsigned int i = 0; i < draw_list.size(); i++){
        // cout << i << endl;
        glLineWidth(draw_list[i].width);
        glColor4fv(&draw_list[i].color[0]);
        // cout << draw_list[i].color[0] << " " << draw_list[i].color[1] << " " << draw_list[i].color[2] << " " << draw_list[i].color[3] << endl;
        glVertex3fv(&draw_list[i].vertA[0]);
        // cout << draw_list[i].vertA[0] << " " << draw_list[i].vertA[1] << " " << draw_list[i].vertA[2] << endl;
        glVertex3fv(&draw_list[i].vertB[0]);
        // cout << draw_list[i].vertB[0] << " " << draw_list[i].vertB[1] << " " << draw_list[i].vertB[2] << endl;
    }
    glEnd();
}