// lsystem.cpp - Implemention of an lsystem class
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


#include "lsystem.hpp"

LSystem::LSystem(){
}

void LSystem::loadFile(const string& filename){
  // Load JSON File
  FILE* fp = fopen(filename.c_str(), "r");
  char read_buffer[65536];
  FileReadStream is(fp, read_buffer, sizeof(read_buffer));
  Document document;
  document.ParseStream(is);
  
  //TODO: Make this repetitive code as consice and compact as possible

  // Set Name
  if(document.HasMember("name")){
    assert(document["name"].IsString());
    m_canvas.setName(document["name"].GetString());
  } else {
    m_canvas.setName("Untitled");
  }

  // Set Type
  if(document.HasMember("type")){
    assert(document["type"].IsString());
    m_type = document["type"].GetString();
  } else {
    m_type = "cartesian-2d";
  }

  // Set Axiom
  assert(document.HasMember("axiom"));
  assert(document["axiom"].IsString());
  m_axiom = document["axiom"].GetString(); 
  
  if(document.HasMember("level")){
    assert(document["level"].IsInt());
    m_level = document["level"].GetInt(); 
  } else {
    m_level = 1; 
  }

  // Set Rules
  assert(document.HasMember("rules"));
  assert(document["rules"].IsObject());
  for (auto& member: document["rules"].GetObject()){
    assert(member.name.GetStringLength() == 1);
    assert(member.value.IsString());
    m_rmap[member.name.GetString()[0]] = member.value.GetString();
  }

  // Set Background

  if(document.HasMember("bg-color")){
    dvec3 hsl;
    assert(document["bg-color"].IsArray());
    assert(document["bg-color"].Size() == 3);
    for(uint index = 0; index < document["bg-color"].Size(); index++){
      assert(document["bg-color"][index].IsInt()||document["bg-color"][index].IsDouble());
      hsl[index] = document["bg-color"][index].GetDouble();
    }
    m_canvas.setColor(hsl2rgb(hsl));
  }

  // Set Init
  if(document.HasMember("init")){
    for (auto& member: document["init"].GetObject()){
      assert(member.value.IsInt()||member.value.IsDouble());
      m_turtle.setState(member.name.GetString(),member.value.GetDouble());
    }
  }

  // Set Functions
  assert(document.HasMember("functions"));
  assert(document["functions"].IsObject());
  for (auto& letter: document["functions"].GetObject()){
    assert(letter.name.GetStringLength() == 1);
    assert(letter.value.IsObject());
    for (auto& action: letter.value.GetObject()){
      char c = letter.name.GetString()[0];
      string label = action.name.GetString();
      double param;
      if(action.value.IsBool()){
        param = (double) action.value.GetBool();
      }else{
        param = action.value.GetFloat();
      }
      m_turtle.addFunction(c, label, param);
    }
  }
}

void LSystem::construct(){
  m_turtle.generateDrawList(expandSystem());
}

void LSystem::draw(){
  m_canvas.setDrawFunction(m_turtle.getDrawFunction());
  m_canvas.draw();
}

string LSystem::expandSystem(){
  string word = m_axiom;
  string temp;
  uint layer = m_level;
  while(layer > 0){
    temp = "";
    for(char &c: word){
      if(m_rmap.find(c) != m_rmap.end()){
        temp += m_rmap[c];
      }else{
        temp += c;
      }
    }
    word = temp;
    layer--;
  }
  return word;
}