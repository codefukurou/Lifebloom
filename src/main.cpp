
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
#include "expression.hpp"
#include <regex>
#include <vector>
#include <string>
#include <sstream>

using namespace std;



// class Construction{
// public:
//   Construction();

// private:
//   struct Symbol{
//     char label;
//     vector<double> args;
//   };

//   char m_target_label;
//   char m_left_label;
//   char m_right_label;

//   Expression conditon;
  
//   Symbol* m_target;
//   Symbol* m_left;
//   Symbol* m_right;
// };

int main( int argc, char **argv )
{
  // glutInit( &argc, argv );

  string input;
  if(argc > 1){
    input = argv[1];
  }else{
    return 0;
  }

  Expression condition(input);

  cout << condition.evaluate() << endl;
  cout << (0.0 || 1.0 || 0.0) << endl;

  return 0;
}