#include <iostream>

/*
   This program demonstrates expressions mixing data
   types.
   Play around with the variables. Make sure you understand
   what is happening.
*/

using namespace std;

int main()
{
   int i = 10, j = 7, l;
   unsigned int k;
   double q = 3.56;
   char c;

   k = q * i - (2 * i) / j;
   // calculator gives 32.74285714
   cout << "k = " << k << "\n";

   c = q * i * j;
   l = c;
   // calculator gives 249.2
   cout << "l = " << l << "\n";

   k = -(i * q);
   // calculator gives -35.6
   cout << "k = " << k << "\n";

   return 0;
}
