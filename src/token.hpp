// token.hpp - Token class for mathematical expressions
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

#include <map>
#include <string>
#include <vector>
#include <array>
#include <cstdint>
#include <algorithm>
#include <cctype>
#include <regex>
#include <functional>
#include <iostream>

using namespace std;
typedef unsigned int uint;

enum TOKEN_TYPE{
  UNDEFINED = -1,
  LITERAL,
  VARIABLE,
  OPERATOR,
  LEFT_PARENTHESIS,
  RIGHT_PARENTHESIS,
  DELIMETER,
  FUNCTION
};

class Token{
public:
  Token();
  Token(const TOKEN_TYPE& type, const string& label, const double& value);
  TOKEN_TYPE getType();
  string getLabel();
  double getValue();
  void setType(const TOKEN_TYPE& type);
  void setLabel(const string& label);
  void setValue(const double& value);

  friend ostream& operator<<(ostream& os, const Token& token);  

private:
  TOKEN_TYPE m_type;
  string m_label;
  double m_value;  

};

