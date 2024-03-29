#ifndef __ARDUINO_STRING_H_
#define __ARDUINO_STRING_H_

#include <string>

using namespace std;
string to__string(int& value);
string to__string(float& value);

class String
{
public:
   String(void);
   String(string& _s);
   String(const char* _c);
   String(int _i);
   String(size_t size, char ch);

   bool operator==(const String&) const;

   int indexOf(char ch);

   bool startsWith(String& _s);

   void concat(string& _s);
   void concat(String& _s);
   void concat(const String& _s);
   void concat(const char* _c);
   void concat(const char ch);
   void concat(int _i);
   void concat(unsigned int _i);
   void concat(float _f);
   int compare(string& _s);
   int compare(String& _s);
   int compare(String _s);
   int compare(const char* _c);
   int compare(void);
   int compareTo(String& _s);
   int compareTo(string& _s);
   int compareTo(const char* _c);
   int length();
   String substring(int from);
   String substring(int from, int to);
   char charAt(int n);
   void setCharAt(int index, char c);
   long toInt();
   float toFloat();

   string s;
};

#endif /* __ARDUINO_STRING_H_ */