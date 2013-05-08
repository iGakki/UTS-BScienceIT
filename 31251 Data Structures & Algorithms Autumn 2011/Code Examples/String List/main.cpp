/**************************************************\
   program to print entered arguments to screen
   using stringlist class
\**************************************************/

#include <iostream>
#include <stdexcept>

#include "stringlist.h"

using namespace std;

void loadStrings(stringlist &mystrings);
 
void loadStrings(stringlist &mystrings) 
{
    int numstrings;
    string astring;

    cout << "Please enter number of strings to be entered\n";
    cin >> numstrings;
    mystrings.setNumstrings(numstrings);

    cout << "Please enter the strings\n";
    for (int i=0; i<numstrings; i++) {
       cin >> astring;
       mystrings.setString(i, astring);
    }
}

int main() 
{
   stringlist mystrings, *stringsPtr = NULL;
   int numString;

   try {
      loadStrings(mystrings);

      // dynamically create a new stringlist and 
      // copy mystrings into it
      stringsPtr = new stringlist;
      *stringsPtr = mystrings;

      // change new string
      numString = stringsPtr->getNumstrings();
      stringsPtr->setString(numString/2, "NEWSTRING");

      // swap the two strings around
      stringsPtr->swapStrings(mystrings);

      // print both the strings
      cout << "\nFirst stringlist\n";
      mystrings.printStrings();
      cout << "\nDynamically created list\n";
      stringsPtr->printStrings();

      delete stringsPtr;
   } catch(out_of_range &ex) {
      cout << "\nERROR - Out of Range Exception thrown\n" << ex.what() << "\n";
      exit(1);
   } catch (runtime_error &ex) {
      cout << "\nERROR - Runtime Exception thrown\n" << ex.what() << "\n";
      exit(1);
   }
      
   return 0;
}

