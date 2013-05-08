#include <iostream>
#include <fstream>
#include <list>
#include <ctype.h>
#include <stdlib.h>

using namespace std;

char getChar(list<char>::iterator itr, int nodes);
int getWordLength(list<char>::iterator itr);
void printList(const list<char> &myList);
void fillList(list<char> &myList, const char *file);
char matchCase(char oldChar, char newChar);
void replaceC(list <char> &myList);
void replaceW(list <char> &myList);
void replacePH(list <char> &myList);
void replaceDouble(list <char> &myList);
void removeE(list <char> &myList);
void replaceTH(list <char> &myList);
void replaceOU(list <char> &myList);
void replaceEA(list <char> &myList);
void replaceED(list <char> &myList);

int main(int argc, char *argv[])
{  
   if (argc != 2) {  
      cout << "Syntax : euro file\n";
      return 0;
   }
   
   list<char> myList;

   fillList(myList, argv[1]);
   printList(myList);
   replaceDouble(myList);
   replaceC(myList);
   replaceDouble(myList);
   replaceW(myList);
   replacePH(myList);
   replaceTH(myList);
   replaceOU(myList);
   replaceEA(myList);
   replaceED(myList);
   removeE(myList);
   printList(myList);

   return 0;
}

void printList(const list<char> &myList)
{
   list<char>::const_iterator itr;
   
   for (itr = myList.begin(); itr != myList.end(); itr++ ) {
      cout << *itr;
   }
   cout << '\n' << '\n';
}

void fillList(list<char> &myList, const char *file)
{  
   ifstream fin;
   char c;

   fin.open(file);
   if (!fin) {
      cout << "ERROR - unable to read " << file << "\n";
      exit(0);
   }

   while (!fin.eof()) {
      c = fin.get();
      if(fin.good()) myList.push_back(c);
   }

   fin.close();
}

// Pass itr by value to look at node "nodes" distance from current letter

char getChar(list<char>::iterator itr, int nodes)
{  
   if (nodes > 0) {
      for (int i=0; i<nodes; i++) {
         itr++;
      }
   }
   else if (nodes < 0) {
      for (int i=0; i>nodes; i--) {
         itr--;
      }
   }
   return tolower(*itr);
}

// Pass itr by value to count number of characters in the word

int getWordLength(list<char>::iterator itr)
{  
   int n = 0;
   
   while (isalpha(*itr)) {       //Go to start of word
      itr--;
   }
   
   itr++;
   
   while (isalpha(*itr)) {       //Count characters in the word
      n++;      
      itr++;
   }
   
   return n--;        //Drop the trailing space off the count
}

char matchCase(char oldChar, char newChar)
{
   if (isupper(oldChar)) return toupper(newChar);
   else return newChar;
}

//Replace all doubles with a single character

void replaceDouble(list <char> &myList)
{  
   list<char>::iterator itr;

   for (itr = myList.begin(); itr != myList.end(); itr++ ) {
      if (getChar(itr, 0) == getChar(itr, 1) && isalpha(*itr)) {
         itr = myList.erase(itr);
      }
   }
}

//Replace soft 'c' with 's' and hard 'c' with 'k'

void replaceC(list <char> &myList)
{  
   list<char>::iterator itr;
   
   for (itr = myList.begin(); itr != myList.end(); itr++ ) {
      if (getChar(itr, 0) == 'c') {
         if (getChar(itr, 1)=='e' ||
            getChar(itr, 1)=='i' ||
            getChar(itr, 1)=='y')
         {
            *itr = matchCase(*itr, 's');
         }
         else *itr = matchCase(*itr, 'k');
      }
   }
}

//Replace 'w' with 'v'

void replaceW(list <char> &myList)
{  
   list<char>::iterator itr;
   
   for (itr = myList.begin(); itr != myList.end(); itr++ ) {
      if (getChar(itr, 0) == 'w') {
         *itr = matchCase(*itr, 'v');
      }
   }
}

//Replace 'ph' with 'f'

void replacePH(list <char> &myList)
{  
   list<char>::iterator itr;

   for (itr = myList.begin(); itr != myList.end(); itr++ ) {
      if (getChar(itr, 0) == 'p' && getChar(itr, 1) == 'h') {
         char temp = *itr;       //Store char for its case

         itr = myList.erase(itr);      //Deletes 'p' and moves itr to next
         *itr = matchCase(temp, 'f');       // Make the 'h' an 'f'
      }
   }
}

//Replace 'th' with 'z'

void replaceTH(list <char> &myList)
{  
   list<char>::iterator itr;

   for (itr = myList.begin(); itr != myList.end(); itr++ ) {
      if (getChar(itr, 0) == 't' && getChar(itr, 1) == 'h') {
         char temp = *itr;

         itr = myList.erase(itr);
         *itr = matchCase(temp, 'z');
      }
   }
}

//Replace 'ou' with 'u'

void replaceOU(list <char> &myList)
{  
   list<char>::iterator itr;
   
   for (itr = myList.begin(); itr != myList.end(); itr++ ) {
      if (getChar(itr, 0) == 'o' && getChar(itr, 1) == 'u') {
         char temp = *itr;

         itr = myList.erase(itr);
         *itr = matchCase(temp, 'u');
      }
   }
}

//Replace 'ea' with 'e'

void replaceEA(list <char> &myList)
{  
   list<char>::iterator itr;
   
   for (itr = myList.begin(); itr != myList.end(); itr++ ) {
      
      if (getChar(itr, 0) == 'e' && getChar(itr, 1) == 'a') {
         itr++;
         
         itr = myList.erase(itr);
      }
   } 
}

//Replace 'ed ' with 'd '

void replaceED(list <char> &myList)
{  
   list<char>::iterator itr;
   
   for (itr = myList.begin(); itr != myList.end(); itr++ ) {
      if (getChar(itr, 0) == 'e' &&
         getChar(itr, 1) == 'd' &&
         !isalpha(getChar(itr, 2)))
      {
         itr = myList.erase(itr);
      }
   }
}

//Remove trailing e if word is more than 3 characters long

void removeE(list <char> &myList)
{  
   list<char>::iterator itr;

   for (itr = myList.begin(); itr != myList.end(); itr++ ) {
      if (getChar(itr, 0) == 'e' &&
         !isalpha(getChar(itr, 1)) &&
         getWordLength(itr)>3)
      {
         itr = myList.erase(itr);      //Delete the trailing 'e'
      }
   }
}
