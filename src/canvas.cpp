// canvas.cpp - Implementation of a 2-Dimensional 'canvas' using OpenGL
// Copyright (C) 2018 Benjamin Lewis

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "canvas.hpp"

static Canvas* g_current_canvas = 0;

Canvas::Canvas(){
  m_scale_factor = 0.99;
  m_color = dvec3(0.9,0.9,0.9);
  m_center = dvec2(0,0);
  m_scenter = dvec2(0,0);
  m_position = dvec2(0,0);
  m_scale = 1.0;
  m_mouse = MOUSE_NULL;
  m_name = "Untitled";
}

void Canvas::draw(){
  glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
  glutInitWindowSize(DEFAULTS::WIDTH, DEFAULTS::WIDTH);
  glutCreateWindow(m_name.c_str());

  setCallbacks();

  glutMainLoop();
}

void Canvas::setCallbacks(){
  g_current_canvas = this;
  glutMouseFunc(Canvas::mouseCallback);
  glutMotionFunc(Canvas::motionCallback);
  glutDisplayFunc(Canvas::displayCallback);
  glutPassiveMotionFunc(Canvas::passiveMotionCallback);
}

void Canvas::setDrawFunction(function<void(void)> draw_function){
  m_draw = draw_function;
}

void Canvas::setColor(dvec3 color){
  m_color = color;
}

void Canvas::setName(string name){
  m_name = name;
}

dvec3 Canvas::unprojectPoint(const dvec3& window_point){
  ivec4 view;
  dmat4 projection, model;

  glGetDoublev(GL_MODELVIEW_MATRIX, &model[0][0]);
  glGetDoublev(GL_PROJECTION_MATRIX, &projection[0][0]);
  glGetIntegerv(GL_VIEWPORT, &view[0]);

  dvec3 world_point = unProject(window_point, model, projection, view);

  return world_point;
}

dvec2 Canvas::unprojectPlane(const dvec2& window_point){
  dvec3 world_point_1 = unprojectPoint(dvec3(window_point, 0.01));
  dvec3 world_point_2 = unprojectPoint(dvec3(window_point, 0.99));

  double u = -world_point_1.z / (world_point_2.z - world_point_1.z);
  
  if( u < 0 ) u = 0;
  if( u > 1 ) u = 1;

  return dvec2(world_point_1 + u*(world_point_2 - world_point_1));
}

void Canvas::applyView(){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  const double width  = glutGet(GLUT_WINDOW_WIDTH);
  const double height = glutGet(GLUT_WINDOW_HEIGHT);

  glOrtho(-width/2, width/2, -height/2, height/2, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glScaled(m_scale, m_scale, 1.0);
  glTranslated(-m_center[0], -m_center[1], 0);
}

void Canvas::mouse(int button, int state, int x, int y){
  m_mouse = button;
  y = glutGet(GLUT_WINDOW_HEIGHT) - y;
  m_position = ivec2(x, y);

  if(m_mouse == MOUSE_SCROLL_UP || m_mouse == MOUSE_SCROLL_DOWN){
    applyView();
    dvec2 prep_zoom = unprojectPlane(dvec2(x, y));

    m_scale = (m_mouse == MOUSE_SCROLL_UP) ? m_scale*m_scale_factor : m_scale/m_scale_factor;

    applyView();
    dvec2 post_zoom = unprojectPlane(dvec2(x, y));

    m_center += (prep_zoom - post_zoom);
  }

  if(m_mouse == MOUSE_LEFT_BUTTON){
    applyView();

    if(state == GLUT_DOWN){
      m_scenter = unprojectPlane(dvec2(x,y));
    }

    if(state == GLUT_UP){
      m_mouse = MOUSE_NULL;
    }
  }

  glutPostRedisplay();
}

void Canvas::motion(int x, int y){
  y = glutGet(GLUT_WINDOW_HEIGHT) - y;
  m_position = ivec2(x, y);

  if(m_mouse == MOUSE_LEFT_BUTTON){
    applyView();
    dvec2 cursor = unprojectPlane(dvec2(x, y));
    m_center +=(m_scenter - cursor);
  }

  glutPostRedisplay(); 
}

void Canvas::passiveMotion(int x, int y){
  y = glutGet(GLUT_WINDOW_HEIGHT) - y;
  m_position = ivec2(x, y);

  glutPostRedisplay(); 
}

void Canvas::display(void){
  glClearColor(m_color[0],m_color[1],m_color[2],1.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  applyView();

  m_draw();

  glutSwapBuffers();
}

void Canvas::mouseCallback(int button, int state, int x, int y){
  g_current_canvas->mouse(button, state, x, y);
}

void Canvas::motionCallback(int x, int y){
  g_current_canvas->motion(x, y);
}

void Canvas::passiveMotionCallback(int x, int y){
  g_current_canvas->passiveMotion(x, y);
}

void Canvas::displayCallback(){
  g_current_canvas->display();
}