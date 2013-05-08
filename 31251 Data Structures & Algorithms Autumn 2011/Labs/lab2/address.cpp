#include <iostream>

using namespace std;

int main()
{
   unsigned int x = 6;
   unsigned int *y = &x;

   cout << "\nValue in x = " << x << "\n";
   cout << "Address of x = " << &x << "\n";

   cout << "\nAddress in y = " << y << "\n";
   cout << "Value of *y = " << *y << "\n";

   cout << "\nNow make *y = 8\n";
   *y = 8;
   cout << "Value of x = " << x << "\n";

   return 0;
}
