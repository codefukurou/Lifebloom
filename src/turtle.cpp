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
  initState();
}

void Turtle::addFunction(char c, string label, double param){
  m_fmap[c].push_back([&,label,param](void){
    if(label == "draw"){
      
      double dx = m_state["x"] + m_state["length"]*cos(m_state["theta"]*(M_PI/180));
      double dy = m_state["y"] + m_state["length"]*sin(m_state["theta"]*(M_PI/180));
      
      if(param==1) {
        glLine line;
        
        line.color = hsl2rgb(dvec4(m_state["hue"], m_state["saturation"], m_state["lightness"], m_state["alpha"]));
        line.vertA = dvec2(m_state["x"], m_state["y"]);
        line.vertB = dvec2(dx, dy);
        line.width = m_state["width"];
        
        m_lines.push_back(line);
      }
      
      m_state["x"] = dx;
      m_state["y"] = dy;
      
    } else if(label == "store") {
      
      if(param){
        m_sstack.push(m_state);
      }else{
        m_state = m_sstack.top();
        m_sstack.pop();
      }

    } else {
      m_state[label] += param;
    }
  });
}

void Turtle::initState(){
  m_state["hue"]          =   0;
  m_state["saturation"]   =   0;
  m_state["lightness"]    =  15;
  m_state["theta"]        =   0;
  m_state["length"]       =  10;
  m_state["x"]            =   0;
  m_state["y"]            =   0;
}

void Turtle::setState(string label, double value){
  m_state[label] = value;
}

void Turtle::generateDrawList(string word){
  for(char &c: word){
    if(m_fmap.find(c) != m_fmap.end()){
      for(function<void()> f: m_fmap[c]){
        f();
      }
    }
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