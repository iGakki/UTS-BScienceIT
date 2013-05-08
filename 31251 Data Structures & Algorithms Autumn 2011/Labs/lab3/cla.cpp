#include <iostream>
#include <iomanip>
#include <stdlib.h>

/****************************************************\
   Program demonstrating Command Line Arguments
\****************************************************/

using namespace std;

void printSyntax(char program[]);

int main(int argc, char *argv[])
{
   // Convert celsius to fahrenheit
   double temp;
   char *endptr;

   // check that the correct number of aguments have been supplied
   // to the program when it is run
   if (argc != 2)
   {
      printSyntax(argv[0]);
      return 1;
   }

   // convert argv[1] to double and check if valid result
   temp = strtol(argv[1], &endptr, 10);
   if (endptr == argv[1])
   {
      // an invalid string has been entered as a float number
      printSyntax(argv[0]);
      return 1;  
   }

   cout << fixed << setprecision(2);
   cout << "fahrenheit value is " << temp * 9 / 5 + 32 << " degrees\n";
   return 0;
}

void printSyntax(char program[])
{ 
   cout << "syntax : " << program << " celsius\n";
   cout << "Celsius must be a real number\n";
   cout << "Will print the fahrenheit form of the celsius temperature\n";
}
