
/********************************************************\
   Test program for demonstrating container types
\********************************************************/
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

#include <iostream>
#include <algorithm>

#include "dataobject.h"
#include "vector.h"

using namespace std;

double difUtime(struct timeval *first, struct timeval *second); 
int randNum();

double difUtime(struct timeval *first, struct timeval *second)
{
   // return the difference in seconds, including milli seconds

   double difsec =  second->tv_sec - first->tv_sec;

   return (difsec + (second->tv_usec - first->tv_usec) / 1000000.0);
}   

int randNum()
{
   // rand() produces pseudo-random number in range 0 to RAND_MAX
   // for most compilers RAND_MAX is 2^15-1
   // randNum() produces pseudo-random number in range 0 to 2^31-1
   
   static bool initialised = false;

   if (!initialised) {
      srand(time(NULL));
      initialised  = true;
   }
   
   return ((rand() << 16) + rand());
}   

int main()
{
   const int MAXDATA = 1000000;
   dataObject *doPtr;
   int i, keyvals[MAXDATA], data;
   
   // create testContainer
   vector<dataObject> testContainer;
   
   // data for calculating timing
   struct timeval first, second;
   double usecs;
   
   try {
      /*************************************************************\
         Initialise things to demonstrate the container
         - fill keyvals with number 2 digits greater than 
           container size
         - scramble keyvals
      \*************************************************************/
      
      for (i=0; i<MAXDATA; i++) keyvals[i] = (i * 100) + (randNum() % 100);
      for (i=0; i<MAXDATA; i++) swap(keyvals[i], keyvals[randNum() % MAXDATA]);
      
      /*************************************************************\
         test inserting MAXDATA data pieces into the container 
         with keyval 0 to MAXDATA-1 in random order
      \*************************************************************/
      
      gettimeofday(&first, NULL);
      for (i=0; i<MAXDATA; i++) {
         doPtr = new dataObject(keyvals[i]);
         testContainer.insert(*doPtr, i);
      }
     
      gettimeofday(&second, NULL);
      usecs = difUtime(&first, &second);
      cout << "MAXDATA = " << MAXDATA << " items in keyvals in random order\n";
      cout << "time taken to insert data into container = " << usecs << " seconds\n\n";
      
      /*************************************************************\
         test finding data in the container
      \*************************************************************/
      
      gettimeofday(&first, NULL);
      i = testContainer.find(dataObject(keyvals[0]), data);
      gettimeofday(&second, NULL);
      usecs = difUtime(&first, &second);
      if (i < 0) cout << "Not found\n"; else cout << "Found\n";
      cout << "time taken to find keyvals[0] in container = " << usecs << " seconds\n";
      
      gettimeofday(&first, NULL);
      i = testContainer.find(dataObject(keyvals[MAXDATA/2]), data);
      gettimeofday(&second, NULL);
      usecs = difUtime(&first, &second);
      if (i < 0) cout << "Not found\n"; else cout << "Found\n";
      cout << "time taken to find keyvals[MAXDATA/2] in container = " << usecs << " seconds\n";

      gettimeofday(&first, NULL);
      i = testContainer.find(dataObject(keyvals[MAXDATA-1]), data);
      gettimeofday(&second, NULL);
      usecs = difUtime(&first, &second);
      if (i < 0) cout << "Not found\n"; else cout << "Found\n";
      cout << "time taken to find keyvals[MAXDATA-1] in container = " << usecs << " seconds\n";
      
      gettimeofday(&first, NULL);
      i = testContainer.find(dataObject(MAXDATA*100), data);
      gettimeofday(&second, NULL);
      usecs = difUtime(&first, &second);
      if (i < 0) cout << "Not found\n"; else cout << "Found\n";
      cout << "time taken to find a keyval doesn't exist in container = " << usecs << " seconds\n";
      
      /*************************************************************\
         test removing data from the container
      \*************************************************************/
      
      gettimeofday(&first, NULL);
      testContainer.pop_front();
      gettimeofday(&second, NULL);
      usecs = difUtime(&first, &second);
      cout << "\ntime taken to erase first item from container = " << usecs << " seconds\n";
      
      gettimeofday(&first, NULL);
      testContainer.erase(testContainer.size()/2);
      gettimeofday(&second, NULL);
      usecs = difUtime(&first, &second);
      cout << "time taken to erase middle item from container = " << usecs << " seconds\n";
      
      gettimeofday(&first, NULL);
      testContainer.pop_back();
      gettimeofday(&second, NULL);
      usecs = difUtime(&first, &second);
      cout << "time taken to erase last item from container = " << usecs << " seconds\n";

   } catch (out_of_range &ex) {
      cout << "\nERROR - Out of Range Exception thrown\n" << ex.what() << "\n";
      exit(1);
   } catch (invalid_argument &ex) {
      cout << "\nERROR - Invalid Argument Exception thrown\n" << ex.what() << "\n";
      exit(1);
   } catch(...) {
      cout << "\nERROR - undefined Exception thrown\n";
      exit(1);
   }
   
   return 0;
}
