// main.cpp - Main entry point for program
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
#include "canvas.hpp"

int main( int argc, char **argv )
{
  glutInit( &argc, argv );

  Canvas canvas;
  Turtle turtle;

  canvas.setDrawFunction(turtle.getDrawFunction());

  canvas.draw();

  // string filename;
  // if(argc > 1){
  //   filename = argv[1];
  // }else{
  //   filename = "resource/twin_dragon.json";
  // }

  // LSystem lsystem;
  // lsystem.loadFile(filename);
  // lsystem.construct();
  // lsystem.draw();

  return 0;
}