// expression.cpp - Mathematical expression handler class
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

#include "expression.hpp"



Expression::Expression(){
  initializeProperties();
}

Expression::Expression(const string& expr){ 
  initializeProperties();
  tokenizeExpression(expr);
}

void Expression::setVariable(const string& name, const string& value){
  string::size_type sz;
  for(Token* t: m_postfix_tokens){
    if(t->getType()==VARIABLE && t->getLabel()==name){
      t->setType(LITERAL);
      t->setLabel("#");
      t->setValue(stod(value,&sz));
    }
  }
}

void Expression::initializeProperties(){
  m_function_properties["sin"] = {
    1,
    [&](){
      return sin(m_arg_memory[0]);
  }};
  m_function_properties["cos"] = {
    1,
    [&](){
      return cos(m_arg_memory[0]);
  }};
  m_function_properties["tan"] = {
    1,
    [&](){
      return tan(m_arg_memory[0]);
  }};
  m_function_properties["min"] = {
    2,
    [&](){
      return min(m_arg_memory[0],m_arg_memory[1]);
  }};
  m_function_properties["max"] = {
    2,
    [&](){
      return max(m_arg_memory[0],m_arg_memory[1]);
  }};
  m_function_properties["mod"] = {
    2,
    [&](){
      return fmod(m_arg_memory[0],m_arg_memory[1]);
  }};
  m_function_properties["abs"] = {
    1,
    [&](){
      return abs(m_arg_memory[0]);
  }};
  m_function_properties["exp"] = {
    1,
    [&](){
      return exp(m_arg_memory[0]);
  }};
  m_function_properties["sqrt"] = {
    1,
    [&](){
      return sqrt(m_arg_memory[0]);
  }};

  m_operator_properties["+"] = {
    true,
    2,
    [&](){
      return m_arg_memory[1] + m_arg_memory[0];
  }};
  m_operator_properties["-"] = {
    true,
    2,
    [&](){
      return m_arg_memory[1] - m_arg_memory[0];
  }};
  m_operator_properties["*"] = {
    true,
    3,
    [&](){
      return m_arg_memory[1] * m_arg_memory[0];
  }};
  m_operator_properties["/"] = {
    true,
    3,
    [&](){
      return m_arg_memory[1] / m_arg_memory[0];
  }};
  m_operator_properties["^"] = {
    false,
    4,
    [&](){
      return pow(m_arg_memory[1], m_arg_memory[0]);
  }};
  m_operator_properties["&"] = {
    true,
    3,
    [&](){
      return (m_arg_memory[1]) && (m_arg_memory[0]);
  }};
  m_operator_properties["|"] = {
    true,
    2,
    [&](){
      return (m_arg_memory[1]) || (m_arg_memory[0]);
  }};
  m_operator_properties["="] = {
    true,
    1,
    [&](){
      return m_arg_memory[1] == m_arg_memory[0];
  }};
}

void Expression::tokenizeExpression(string expr){
  vector<Token*> infix_tokens;

  string letter_buffer = "";
  string number_buffer = "";

  function<bool(const char&)> isComma = [](const char& c){
    return (c>=',');
  };

  function<bool(const char&)> isStop = [](const char& c){
    return (c=='.');
  };

  function<bool(const char&)> isDigit = [](const char& c){
    return (c>='0'&&c<='9');
  };

  function<bool(const char&)> isLetter = [](const char& c){
    return ((c>='a'&&c<='z')||(c>='A'&&c<='Z'));
  };

  function<bool(const char&)> isOperator = [](const char& c){
    return (c=='+'||c=='-'||c=='*'||c=='/'||c=='^');
  };

  function<bool(const char&)> isLeftParenthesis = [](const char& c){
    return (c=='(');
  };

  function<bool(const char&)> isRightParenthesis = [](const char& c){
    return (c==')');
  };

  function<void()> clearLetterBuffer = [&](){
    for(string::iterator it = letter_buffer.begin(); it != letter_buffer.end(); ++it){
      infix_tokens.push_back(new Token(VARIABLE, string(it, it+1), 0));
      if(it + 1 != letter_buffer.end()){
        infix_tokens.push_back(new Token(OPERATOR, "*", 0));
      }
    }
    letter_buffer = "";
  };

  function<void()> clearNumberBuffer = [&](){
    if(number_buffer.length()){
      string::size_type sz;
      infix_tokens.push_back(new Token(LITERAL, "#", stod(number_buffer, &sz)));
      number_buffer = "";
    }
  };

  expr.erase(remove_if(expr.begin(), expr.end(), ::isspace), expr.end());
  for(char c: expr){
    if(isDigit(c)){
      number_buffer.push_back(c);
    }else if(isStop(c)){
      number_buffer.push_back(c);
    }else if((c>='a'&&c<='z')||(c>='A'&&c<='Z')){      
      if(number_buffer.length()){
        clearNumberBuffer();
        infix_tokens.push_back(new Token(OPERATOR, "*", 0));
      }
      letter_buffer.push_back(c);
    }else if(isOperator(c)){
      clearNumberBuffer();
      clearLetterBuffer();
      infix_tokens.push_back(new Token(OPERATOR, string(1,c), 0));
    }else if(isLeftParenthesis(c)){
      if(letter_buffer.length()){
        infix_tokens.push_back(new Token(FUNCTION, letter_buffer, 0));
        letter_buffer="";
      }else if(number_buffer.length()){
        clearNumberBuffer();
        infix_tokens.push_back(new Token(OPERATOR, "*", 0));
      }
      infix_tokens.push_back(new Token(LEFT_PARENTHESIS, string(1,c), 0));
    }else if(isRightParenthesis(c)){
      clearLetterBuffer();
      clearNumberBuffer();
      infix_tokens.push_back(new Token(RIGHT_PARENTHESIS, string(1,c), 0));
    }else if(isComma(c)){
      clearNumberBuffer();
      clearLetterBuffer();
      infix_tokens.push_back(new Token(DELIMETER, string(1,c), 0));
    }
  }

  if(number_buffer.length()){
    clearNumberBuffer();
  }

  if(letter_buffer.length()){
    clearLetterBuffer();
  }

  stack<Token*> token_stack;
  vector<Token*>::iterator it = infix_tokens.begin();
  while(it != infix_tokens.end()){
    TOKEN_TYPE type = (*it)->getType();
    if(type==LITERAL||type==VARIABLE){
      m_postfix_tokens.push_back(*it);
    }else if(type==FUNCTION){
      token_stack.push((*it));
    }else if(type==OPERATOR){
      while(
          !token_stack.empty() &&         
          (
            (
              (token_stack.top()->getType() == FUNCTION) ||
              (m_operator_properties[token_stack.top()->getLabel()].precedence > m_operator_properties[(*it)->getLabel()].precedence) ||
              (m_operator_properties[token_stack.top()->getLabel()].precedence == m_operator_properties[(*it)->getLabel()].precedence && m_operator_properties[token_stack.top()->getLabel()].is_left_associative)
            ) && 
              (token_stack.top()->getType() != LEFT_PARENTHESIS)
          ))
      {
        m_postfix_tokens.push_back(token_stack.top());
        token_stack.pop();
      }
      token_stack.push(*it);
    }else if(type==LEFT_PARENTHESIS){
      token_stack.push(*it);
    }else if(type==RIGHT_PARENTHESIS){
      while(token_stack.top()->getType() != LEFT_PARENTHESIS){
        m_postfix_tokens.push_back(token_stack.top());
        token_stack.pop();
      }
      token_stack.pop();
    }
    ++it;
  }
  while(!token_stack.empty()){
    m_postfix_tokens.push_back(token_stack.top());
    token_stack.pop();
  }
}

double Expression::evaluate(){
  stack<double> value_stack;
  TOKEN_TYPE type;
  for(Token* t: m_postfix_tokens){
    type = t->getType();
    if(type==LITERAL){
      value_stack.push(t->getValue());
    }else if(type==FUNCTION){
      for(unsigned int i = 0; i < (unsigned int)m_function_properties[t->getLabel()].num_args; ++i){
        m_arg_memory[i] = value_stack.top();
        value_stack.pop();
      }
      value_stack.push(m_function_properties[t->getLabel()].func());
    }else if(type==OPERATOR){
      for(unsigned int i = 0; i < 2; ++i){
        m_arg_memory[i] = value_stack.top();
        value_stack.pop();
      }
      value_stack.push(m_operator_properties[t->getLabel()].func());
    }

  }
  return value_stack.top();
}