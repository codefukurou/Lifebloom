// expression.hpp - Mathematical expression handler class
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
#include <stack>
#include <vector>
#include <cmath>
#include <array>
#include <functional>
#include "token.hpp"

class Expression{
public:
  Expression();
  Expression(const string& expr);
  void setVariable(const string& name, const string& value);
  void tokenizeExpression(string expr);
  double evaluate();

private:
  struct FunctionProperties{
    int num_args;
    function<double()> func;
  };

  struct OperatorProperties{
    bool is_left_associative;
    int precedence;
    function<double()> func;
  };

  map<string,FunctionProperties> m_function_properties;
  map<string,OperatorProperties> m_operator_properties;
  vector<Token*> m_postfix_tokens;
  array<double,2> m_arg_memory;

  void initializeProperties();

};