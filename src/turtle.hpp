// turtle.hpp - Implemention of a turtle graphics class
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

#ifndef TURTLE_HPP
#define TURTLE_HPP

#define GLM_ENABLE_EXPERIMENTAL

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <cmath>
#include <map>
#include <vector>
#include <functional>
#include <string>
#include <iostream>
#include <stack>
#include "color.hpp"

using namespace glm;
using namespace std;

struct glLine {
  dvec3 color;
  dvec3 vertA;
  dvec3 vertB;
  double width;
};

class Turtle {
public:
  Turtle();
  void processWord(const string& word);
  function<void()> getDrawFunction();

protected:
  map<char,function<void(double)>> m_functions;
  map<char,double> m_defaults;
  vector<glLine> m_lines;
  
  virtual void constructFunctionMap();
};

class TurtleCartesian2D : public Turtle {
public:
  TurtleCartesian2D();
    
protected:
  void constructFunctionMap();

private:
  struct State {
    dvec2 position;
    dvec2 direction;
    double diameter;
    int color_index;

    State();
  };
  
  State m_state;
  stack<State> m_statestack;

};

class TurtleCartesian3D : public Turtle {
public:
  TurtleCartesian3D();

protected:
  void constructFunctionMap();

private:
  struct State {
    dvec3 position;
    dmat3x4 direction;
    double diameter;
    int color_index;

    State();
  };
  
  State m_state;
  stack<State> m_statestack;

};

#endif