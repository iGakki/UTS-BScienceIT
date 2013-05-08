#include <iostream>
#include <fstream>
#include <string>
#include "bintree.h"
#include <ctype.h>

using namespace std;

void loadDictionary(bintree<string> &treeRoot);
void spellCheck(bintree<string> &treeRoot, const char *file);
bool isSeparator(char prev, char c, char next);
string toLower(string str);
bool isNum(string str);

int main(int argc, char *argv[])
{  
   if (argc != 2) {  
      cout << "Syntax : dictionary file\n";
      return 0;
   }

   bintree<string> treeRoot;

   loadDictionary(treeRoot);
   spellCheck(treeRoot, argv[1]);

   return 0;
}

/* Reads the dictionary file, loading each word into a C++ string
 * object and then storing the string in a binary tree.
*/

void loadDictionary(bintree<string> &treeRoot)
{
   ifstream fin;
   
   fin.open("dict.txt");
   if (!fin) {
      cout << "ERROR - Unable to access " << "dict.txt" << "\n";
      exit(0);
   }

   while (!fin.eof()) {
      string str;
      
      if(fin.good()) {
         fin >> str;
         treeRoot.insert(str);
      }
   }
   fin.close();
}

/* Reads the text file char by char into a string, stopping when a
separator is found.  Each string is then matched to the dictionary.
Words not found in the dictionary are printed.  The total number of
words extracted and words not found in the dictionary are counted and
printed.
*/

void spellCheck(bintree<string> &treeRoot, const char *file)
{
   ifstream fin;
   string str;
   char c, prev;
   int mismatchCount = 0, wordCount = 0;
      
   fin.open(file);
   if (!fin) {
      cout << "ERROR - Unable to access " << file << "\n";
      exit(0);
   }

   while (!fin.eof()) {
      prev = c;
      c = fin.get();
      if(fin.good()) {
         if (!isSeparator(prev, c, fin.peek())) str.push_back(c);
         else if (str != "") {
            wordCount++;
            
            if (treeRoot.find(toLower(str)) == NULL && !isNum(str)) {
               cout << "Unknown word | " << str << "\n";
               mismatchCount++;
            }
            str = "";
         }
      }
   }
   cout << "A total of " << wordCount << " words were found in the file\n"
      << mismatchCount << " had unknown spelling";   
}

// Determines whether a given char matches our definition of a separator.

bool isSeparator(char prev, char c, char next)
{
   if ((isspace(prev) || isdigit(prev)) 
      && c == '.' && isdigit(next)) return false;
   else if (c == '\'') return false;
   else if (isspace(c) || ispunct(c) || c == '\r') return true;
   return false;
}

// Converts all letters in a given string to lower case.

string toLower(string str)
{
   string::iterator itr;
   
   for (itr = str.begin(); itr != str.end(); itr++) {
      *itr = tolower(*itr);
   }
   return str;
}

// Determines whether a given string is a valid number.

bool isNum(string str)
{
   string::iterator itr;
   int pointCount;
      
   for (itr = str.begin(); itr != str.end(); itr++) {
      if (*itr == '.') pointCount++;
      else if (!isdigit(*itr)) return false;
   }
   if (pointCount <= 1) return true;
   return false;
   
   /* The following piece of code was recommended by the assignment
   outline but fails to recognise a number with two decimal points as
   invalid:
   
   char * end;
   
   if ((strtod(str.c_str(), &end) != 0.0)) return true;
   return false;
   */
}
