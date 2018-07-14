// token.cpp - Token class for mathematical expressions
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

#include "token.hpp"

Token::Token(){
  m_type = UNDEFINED;
  m_value = "";
}

Token::Token(TOKEN_TYPE type, string value){
  m_type = type;
  m_value = value;
}

ostream& operator<<(ostream& os, const Token& token){
  os << token.m_value << " [ " << token.m_type << " ]";
  return os;
}

vector<Token*> tokenizeExpression(string expr){
  vector<Token*> token_list;
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
      token_list.push_back(new Token(VARIABLE, string(it, it+1)));
      if(it + 1 != letter_buffer.end()){
        token_list.push_back(new Token(OPERATOR,"*"));
      }
    }
    letter_buffer = "";
  };

  function<void()> clearNumberBuffer = [&](){
    if(number_buffer.length()){
      token_list.push_back(new Token(LITERAL, number_buffer));
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
        token_list.push_back(new Token(OPERATOR, "*"));
      }
      letter_buffer.push_back(c);
    }else if(isOperator(c)){
      clearNumberBuffer();
      clearLetterBuffer();
      token_list.push_back(new Token(OPERATOR, string(1,c)));
    }else if(isLeftParenthesis(c)){
      if(letter_buffer.length()){
        token_list.push_back(new Token(FUNCTION, letter_buffer));
        letter_buffer="";
      }else if(number_buffer.length()){
        clearNumberBuffer();
        token_list.push_back(new Token(OPERATOR, "*"));
      }
      token_list.push_back(new Token(LEFT_PARENTHESIS, string(1,c)));
    }else if(isRightParenthesis(c)){
      clearLetterBuffer();
      clearNumberBuffer();
      token_list.push_back(new Token(RIGHT_PARENTHESIS, string(1,c)));
    }else if(isComma(c)){
      clearNumberBuffer();
      clearLetterBuffer();
      token_list.push_back(new Token(DELIMETER, string(1,c)));
    }
  }

  if(number_buffer.length()){
    clearNumberBuffer();
  }

  if(letter_buffer.length()){
    clearLetterBuffer();
  }

  return token_list;
}
