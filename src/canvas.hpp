// canvas.hpp - Implementation of a 2-Dimensional 'canvas' using OpenGL
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

#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <functional>

using namespace std;
using namespace glm;

class Canvas {
public:
  Canvas();
  void draw();
  void setDrawFunction(function<void(void)> draw_function);
  void setColor(dvec3 color);
  void setName(string name);

private:
  function<void()> m_draw;
  double m_scale_factor;
  dvec3 m_color;
  dvec2 m_center;
  dvec2 m_scenter;
  dvec2 m_position;
  double m_scale;
  int m_mouse;
  string m_name;

  dvec3 unprojectPoint(const dvec3& win);
  dvec2 unprojectPlane(const dvec2& win);
  void applyView(void);

  void mouse(int button, int state, int x, int y);
  void motion(int x, int y);
  void passiveMotion(int x, int y);
  void display(void);

  void setCallbacks();

  static void mouseCallback(int button, int state, int x, int y);
  static void motionCallback(int x, int y);
  static void passiveMotionCallback(int x, int y);
  static void displayCallback(void);

  enum MOUSE_STATE{
    MOUSE_NULL = -1,
    MOUSE_LEFT_BUTTON,
	  MOUSE_MIDDLE_BUTTON,
	  MOUSE_RIGHT_BUTTON,
	  MOUSE_SCROLL_UP,
	  MOUSE_SCROLL_DOWN
  };

  enum DEFAULTS{
    WIDTH = 600,
    HEIGHT = 600
  };

};

#endif