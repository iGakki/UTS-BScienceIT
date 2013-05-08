/**************************************************\
   program to print entered strings to screen
\**************************************************/

#include <iostream>

using namespace std;

void getStrings(int *numstringsPtr, string* &strings);
void printStrings(int numstrings, const string *strings);

int main() 
{
   string *strings = NULL;
   int numstrings = 0;

   getStrings(&numstrings, strings);
   printStrings(numstrings, strings);

   if (numstrings > 0) delete [] strings;

   return 0;
}

void getStrings(int *numstringsPtr, string* &strings)
{
   // get strings from user keyboard
   int numstrings;

   cout << "Enter number of strings ";
   cin >> numstrings;

   *numstringsPtr = numstrings;
   strings = new string[numstrings];

   cout << "Enter strings\n";
   for (int i=0; i<numstrings; i++) {
      cin >> strings[i];
   }
}

void printStrings(int numstrings, const string *strings)
{
   // print strings to screen

   cout << "Strings entered\n";
   for (int i=0; i<numstrings; i++) {
      cout << strings[i] << '\n';
   }
}


