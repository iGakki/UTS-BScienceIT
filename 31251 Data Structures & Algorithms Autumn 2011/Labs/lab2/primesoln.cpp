#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

void getNumber(int *number);
bool isPrime(int number);

int main()
{
   int number;

   getNumber(&number);

   if (isPrime(number)) 
      cout << "\n" << number << " is a prime number\n";
   else 
      cout << "\n" << number << " is not a prime number\n";

   return 0;
}

void getNumber(int *number)
{
   cout << "Please enter a positive number ";
   cin >> *number;
   if (!cin.good() || *number < 0)
   {
      cout << "Invalid number entered\n";
      exit(1);
   }
}

bool isPrime(int number)
{
   int count, s;

   // Eliminate 1, 2 & 3
   if (number == 1) return false;
   if (number < 4) return true;

   // Eliminate all other even numbers
   if (number % 2 == 0) return false;

   // eliminate all odd non-prime numbers
   s = (int) sqrt((double) number);
   for (count=3; count<=s; count+=2)
   {
      if (number % count == 0) return false;
   }
   return true;
}
