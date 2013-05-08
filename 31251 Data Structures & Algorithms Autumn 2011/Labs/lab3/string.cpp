#include <iostream>

using namespace std;

const int STRINGSIZE = 100

void getString(char string[])
void reverseCase(char string[])
int numGraph(string[])


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

void reverseCase(char string[]);
{
   /****************************************************************\
      Reverse the case of all alphabetic characters in the string.
      That is, all upper case characters become lower case and 
      all lower case become upper case.
   \****************************************************************/
}

int numGraph(string[])
{
   /***************************************************************\
      Calculate the number of printable graphic characters in the
      string.
   \***************************************************************/

   int i, count;

   for (i=0; string[i] != '\0', i++)
   {
      if (isgraph(string[i])) count++;
   }
   return count; 
}

void getString(char string[])
{
   /************************************************************\
      
      Use getline function to get entire line of text up to

      maximum of STRINGSIZE-1 chars in length
   
   \************************************************************/
   
   
   
   cin << "Please enter a string to process\n";

   cin.getline(string, STRINGSIZE);
}
