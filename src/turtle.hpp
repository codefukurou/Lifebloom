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

class Turtle {
public:
  Turtle();
  void processWord(const string& word);
  function<void()> getDrawFunction();

private:
  // Direction vector indicies
  enum {
    HEAD, LEFT, UP
  };

  struct glLine {
    dvec3 color;
    dvec2 vertA;
    dvec2 vertB;
    double width;
  };

  struct State {
    dvec3   position;
    dmat3x4 direction;
    double  diameter;
    int     color_index;
  };

  map<char,function<void(double)>> m_functions;
  map<char,double> m_defaults;
  State m_state;
  stack<State> m_statestack;
  vector<glLine> m_lines;

  // Assign turtle functions
  void constructFunctionMap();

};

#endif