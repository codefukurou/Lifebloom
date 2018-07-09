// turtle.cpp - Implemention of a turtle graphics class
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

#include "turtle.hpp"

Turtle::Turtle(){
  constructFunctionMap();
  m_state.position = dvec3(0,0,0);
  m_state.direction = dmat3x4(1,0,0,
                              0,1,0,
                              0,0,0,
                              1,1,1);
  processWord("F(1.25)+F(0.75)--F+(180)F(0.50)F");
}

//Sample word: F(1.25)+F(0.75)--F+(180)F(0.50)

void Turtle::processWord(const string& word){
  string::size_type sz;
  string token;
  char symbol; 
  double argument;

  string::size_type i = 0;
  while( i < word.length()){
    if (word[(i+1)] == '(') {
      token = word.substr(i, word.find(')',i) - i + 1);
      symbol = token[0];
      argument = stod(token.substr(2,token.size() - 3) , &sz);
      i += token.length();
    } else {
      symbol = word[i];
      argument = m_defaults[symbol];
      i += 1;
    }
    cout << symbol << ":" << argument << endl;
    m_functions[symbol](argument);
    cout << m_state.position[0] << "," << m_state.position[1] << "," << m_state.position[2] << endl;
  }
}

function<void()> Turtle::getDrawFunction(){
  return ([=](){
    glBegin(GL_LINES);
    for(glLine l: m_lines){
      glColor3dv(value_ptr( l.color ));
      glVertex2dv(value_ptr( l.vertA ));
      glVertex2dv(value_ptr( l.vertB ));
    }
    glEnd();

  });
}

void Turtle::constructFunctionMap(){
  m_functions['F'] = [&](double value){
    // Get appropiate line data...
    dvec3 end_point = m_state.position + value * dvec3(m_state.direction[HEAD]);
    dvec3 color(0.15, 0.15, 0.15); //default, colour maps will come later
    
    // Create line and push it to the draw vector...
    glLine line = {color, m_state.position, end_point, m_state.diameter};
    m_lines.push_back(line);

    // Move turtle forward...
    m_state.position = end_point;
  };
  m_defaults['F'] = 1.0;

  m_functions['f'] = [&](double value){
    m_state.position += value * dvec3(m_state.direction[HEAD]);
  };
  m_defaults['f'] = 1.0;

  m_functions['+'] = [&](double value){
    m_state.direction = rotate(+value, dvec3(m_state.direction[UP]))*m_state.direction;
  };
  m_defaults['+'] = 90.0;

  m_functions['-'] = [&](double value){
    m_state.direction = rotate(-value, dvec3(m_state.direction[UP]))*m_state.direction;
  };
  m_defaults['-'] = 90.0;

  m_functions['^'] = [&](double value){
    m_state.direction = rotate(+value, dvec3(m_state.direction[LEFT]))*m_state.direction;
  };
  m_defaults['^'] = 90.0;

  m_functions['&'] = [&](double value){
    m_state.direction = rotate(-value, dvec3(m_state.direction[LEFT]))*m_state.direction;
  };
  m_defaults['&'] = 90.0;

  m_functions['<'] = [&](double value){
    m_state.direction = rotate(+value, dvec3(m_state.direction[HEAD]))*m_state.direction;
  };
  m_defaults['<'] = 90.0;

  m_functions['>'] = [&](double value){
    m_state.direction = rotate(-value, dvec3(m_state.direction[HEAD]))*m_state.direction;
  };
  m_defaults['>'] = 90.0;

  m_functions['|'] = [&](double value){
    m_state.direction = rotate( 180.0, dvec3(m_state.direction[HEAD]))*m_state.direction;
  };
  m_defaults['|'] = 0.0;

  m_functions['$'] = [&](double value){
    m_state.direction[LEFT] = dvec4(normalize(cross(dvec3(0,0,1), dvec3(m_state.direction[HEAD]))),1);
    m_state.direction[UP] = dvec4(cross(dvec3(m_state.direction[HEAD]), dvec3(m_state.direction[LEFT])),1);
  };
  m_defaults['$'] = 0.0;

  m_functions['['] = [&](double value){
    m_statestack.push(m_state);
  };
  m_defaults['['] = 0.0;

  m_functions[']'] = [&](double value){
    m_state = m_statestack.top();
    m_statestack.pop();
  };
  m_defaults[']'] = 0.0;

  m_functions['!'] = [&](double value){
    m_state.diameter -= value;
  };
  m_defaults['!'] = 1.0;

  m_functions['`'] = [&](double value){
    m_state.color_index += (int)round(value);
  };
  m_defaults['`'] = 1.0;

  // The following functions will be defined at a later date ()

  // m_functions['{'] = [&](double value){
    
  // };

  // m_functions['}'] = [&](double value){
    
  // };

  // m_functions['G'] = [&](double value){
    
  // };

  // m_functions['.'] = [&](double value){
    
  // };

  // m_functions['~'] = [&](double value){
    
  // };
}

