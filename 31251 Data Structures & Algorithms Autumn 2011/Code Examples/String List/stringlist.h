/**************************************************\
   Definitions of memebers of stringlist class
\**************************************************/

#include <iostream>

using namespace std;

class stringlist
{
   private:
      int numstrings;
      string *strings;

   public:
      stringlist() : numstrings(0), strings(NULL) {
      }

      // copy constructor
      stringlist(const stringlist &other) :
         numstrings(other.numstrings), strings(new string[other.numstrings]) {
         for (int i=0; i<numstrings; i++) {
            strings[i] = other.strings[i];
         }
      }

      // destructor
      ~stringlist() {
         if (numstrings > 0) delete [] strings;
      }
  
      void printStrings();
      const string& getString(int num);
      void setString(int num, const char *astring);
      void setString(int num, const string &astring);
      int getNumstrings() {
         return numstrings;
      }
      void setNumstrings(int num);
      void swapStrings(stringlist &other) ;

      // overloaded operators
      stringlist& operator = (const stringlist &other) {
         stringlist temp(other);
         swapStrings(temp);
         return *this;
         // destructor for temp will be called at end of this function
      }
};

