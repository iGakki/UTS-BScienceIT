#include <iostream>
#include <list>
#include <ctype.h>

using namespace std;

void printList(const list<char> &myList);
void fillList(list<char> &myList, const string &vowels);
void changeCase(list <char> &myList);

void printList(const list<char> &myList)
{
   list<char>::const_iterator itr;
   
   for (itr = myList.begin(); itr != myList.end(); itr++ ) {
      cout << ' ' << *itr;                               //Print each element in the list
   }
   cout << '\n';
}

void fillList(list<char> &myList, const string &vowels)  //Pass in direct reference to list and string of vowels
{
   for (int i = 0; i<vowels.length(); i++) {
      myList.push_back(vowels[i]);                       //Add new element to the end of the vector
   }
}

void changeCase(list <char> &myList)
{
   list<char>::iterator itr;
   
   for (itr = myList.begin(); itr != myList.end(); itr++ ) {
      if (islower(*itr)) *itr = toupper(*itr);           //Change element to uppercase
      else *itr = toupper(*itr);
   }
}
   
int main ()
{
  string vowels = "aeiou";    //Initialise string of vowels
  list<char> myList;          //Initialise list of characters
  
  fillList(myList, vowels);
  printList(myList);
  changeCase(myList);
  printList(myList);
  
  return 0;
}

