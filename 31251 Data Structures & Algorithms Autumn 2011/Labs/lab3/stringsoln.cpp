#include <iostream>
#include <ctype.h>

using namespace std;

const int  STRINGSIZE = 100;

void getString(char string[]);
void reverseCase(char string[]);
int numGraph(char string[]);

int main()
{
   char string[STRINGSIZE];
   int count;

   getString(string);
   cout << "Entered string => " << string << "\n";

   count = numGraph(string);
   cout << "Number of graphic characters in string = " << count << "\n";

   reverseCase(string);
   cout << "Reverse case   => " << string << "\n";

   return 0;
}

void reverseCase(char *string)
{
   /****************************************************************\
      Reverse the case of all alphabetic characters in the string.
      That is, all upper case characters become lower case and 
      all lower case become upper case.
   \****************************************************************/

   int i;
   
   for (i=0; string[i] != '\0'; i++) {
      if (isupper((int) string[i])) 
         string[i] = tolower((int) string[i]);
      else 
         string[i] = toupper((int) string[i]);
   }
   
}

int numGraph(char string[])
{
   /****************************************************************\
      Calculate the number of printable graphic characters in the
      string.
   \****************************************************************/

   int i, count = 0;

   for (i=0; string[i] != '\0'; i++) {
      if (isgraph((int) string[i])) count++;
   }
   return count; 
}

void getString(char string[])
{
   /************************************************************\
      Use getline function to get entire line of text up to 
      maximum of STRINGSIZE-1 chars in length
   \************************************************************/
   
   cout << "Please enter a string to process\n";
   cin.getline(string, STRINGSIZE);
}
