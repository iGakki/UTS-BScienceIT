/**************************************************\
   Definitions of memebers of stringlist class
\**************************************************/

#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "stringlist.h"

using namespace std;

void stringlist::printStrings() 
{
   for (int i=0; i<numstrings; i++) {
      cout << strings[i] << '\n';
   }
}

const string& stringlist::getString(int num) 
{
   if (num < 0 || num >= numstrings) {
      throw out_of_range("stringlist::getString");
   }
   return strings[num];
}

void stringlist::setString(int num, const char *astring) 
{
   if (num < 0 || num >= numstrings) {
      throw out_of_range("stringlist::setString");
   }
   strings[num] = astring;
}

void stringlist::setString(int num, const string &astring) 
{
   if (num < 0 || num >= numstrings) {
      throw out_of_range("stringlist::setString");
   }
   strings[num] = astring;
}

void stringlist::setNumstrings(int num) 
{
   if (numstrings != 0) {
      throw runtime_error("stringlist::setNumstrings - numstrings not 0");
   }
   if (num < 0) {
      throw out_of_range("stringlist::setNumstrings - num < 0");
   }
   numstrings = num;
   strings = new string[numstrings];
}

void stringlist::swapStrings(stringlist &other)
{
   swap(numstrings, other.numstrings);
   swap(strings, other.strings);
}

