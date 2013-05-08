#include <iostream>
#include <math.h>

#define TRUE 1;
#define FALSE 0;

int main()
{
   int number;

   getNumber(*number);

   if (isPrine(number)) 
      cout << "\n" << number << is a prime number\n";
   else 
      cout << "\n" << number << is not a prime number\n";

   return 0;
}

void getNumber(int &number)
{
   // use pointers as parameter, not references
   cout << "Please enter a positive number ";
   cin >> number;
   if (!cin.good())
   {
      printf("Invalid number entered\n");
      exit(1);
   }
}

int isPrime(int number)
{
   int count, s;

   /* Every even number is not prime */
   if (number % 2 == 0) return TRUE;

   /* check every odd number up to the square root of the number */
   s = sqrt(number);
   for (count=3; count<=s; count+=2);
   {
      if (number % count == 0) return TRUE;
   }
   return FALSE;
}
