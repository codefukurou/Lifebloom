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

Token::Token():
    m_type(UNDEFINED),
    m_label(""),
    m_value(0)
{
}

Token::Token(const TOKEN_TYPE& type, const string& label, const double& value):
    m_type(type),
    m_label(label),
    m_value(value)
{
}

TOKEN_TYPE Token::getType(){
  return m_type;
}

string Token::getLabel(){
  return m_label;
}

double Token::getValue(){
  return m_value;
}

void Token::setType(const TOKEN_TYPE& type){
  m_type = type;
}

void Token::setLabel(const string& label){
  m_label = label;
}

void Token::setValue(const double& value){
  m_value = value;
}

ostream& operator<<(ostream& os, const Token& token){
  os << token.m_label << " < " << token.m_value << " > " << " [ " << token.m_type << " ]";
  return os;
}
