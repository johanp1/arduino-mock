#include <string>
#include "String.h"
#include <sstream>
#include <iostream>

using namespace std;

std::string to__string(int& value)
{
  //create an output string stream
  std::ostringstream os ;
  
  //throw the value into the string stream
  os << value;
  
  //convert the string stream into a string and return
  return os.str() ;
}

std::string to__string(float& value)
{
  //create an output string stream
  std::ostringstream os ;
  
  //throw the value into the string stream
  os << value;
  
  //convert the string stream into a string and return
  return os.str() ;
}

String::String(void)
{
  s = string("");
}

String::String(string& _s)
{
  s = string(_s);
}

String::String(const char* _c) 
{
  s = string(_c);
}

String::String(int _i) 
{
  s = string(to__string(_i));
}

String::String(size_t size, char ch)
{
   s = string(size, ch);
}

bool String::operator==(const String& rhs) const
{
   return (s.compare(rhs.s) == 0);
}

int String::indexOf(char ch)
{
   return (int)s.find_first_of(ch);
}

bool String::startsWith(String& _s)
{
   return s.find(_s.s) == 0;
}

void String::concat(string& _s)
{
  s.append(_s);
}

void String::concat(String& _s)
{
  s.append(_s.s);
}

void String::concat(const String& _s)
{
  s.append(_s.s);
}

void String::concat(const char* _c)
{
  s.append(_c);
}

void String::concat(const char ch)
{
   s.push_back(ch);
}

void String::concat(int _i)
{
  s.append(to__string(_i));
}

void String::concat(unsigned int _i)
{
int i = (int)_i;
  s.append(to__string(i));
}

void String::concat(float _f)
{
float f = (float)_f;
  s.append(to__string(f));
}

int String::compare(string& _s)
{
  return s.compare(_s);
}

int String::compare(String& _s)
{
  return s.compare(_s.s);
}

int String::compare(String _s)
{
  return s.compare(_s.s);
}

int String::compare(const char* _c)
{
  return s.compare(_c);
}

int String::compare(void)
{
  return s.compare("");
}

int String::compareTo(String& _s)
{
  return s.compare(_s.s);
}

int String::compareTo(string& _s)
{
  return s.compare(_s);
}

int String::compareTo(const char* _c)
{
  return s.compare(_c);
}

int String::length()
{
   return (int)s.length();
}

String String::substring(int from)
{
   string str = s.substr(from);
   return String(str);
}

String String::substring(int from, int to)
{
   string str = s.substr(from, to);
   return String(str);
}

char String::charAt(int n)
{
	return s[n];
}