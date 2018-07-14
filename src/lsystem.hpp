// lsystem.hpp - Implemention of an lsystem class
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

#ifndef LSYSTEM_HPP
#define LSYSTEM_HPP

#include <rapidjson/filereadstream.h> 
#include <rapidjson/document.h>
#include <glm/glm.hpp>
#include <cstdio>
#include <iostream>
#include <functional>
#include <map>
#include "color.hpp"
#include "turtle.hpp"
#include "canvas.hpp"

using namespace glm;
using namespace rapidjson;
using namespace std;

class LSystem {
public:
  LSystem();
  void loadFile(const string& filename);
  void construct();
  void draw();
  friend void drawLSystem(void);

private:
  Turtle m_turtle;
  Canvas m_canvas;
  map<char,string> m_rmap;
  string m_name, m_axiom, m_type;
  uint m_level;

  string generateWord();
};

#endif
