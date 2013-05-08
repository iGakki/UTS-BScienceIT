#ifndef DATAOBJECT_H_
#define DATAOBJECT_H_

#include <algorithm>

/***********************************************************\
   class for holding data to be stored in container objects
\***********************************************************/

struct dataObject
{
   int keyval;
   
   /********************************************************\
      place any other data declartions the data object 
      may need here
   \********************************************************/
   
   /********************************************************\
      constructors
   \********************************************************/
   
   // constructor
   dataObject() : keyval(-1) {}
   dataObject(int val) : keyval(val) {}
   
   // copy constructor
   dataObject(const dataObject &other) : keyval(other.keyval) {
      // copy any data in other to this
   }
   
   /********************************************************\
      misc functions
   \********************************************************/
   
   void swapObjects(dataObject &other) {
      std::swap(keyval, other.keyval);
      // swap any other data in dataObject
   }
   
   bool isKeyval(int val) const {
      return (val == keyval);
   }
   
   int getKeyval() const {
      return keyval;
   }
   
   int getHashval(int range) const {
      return (keyval % range);
   }

   bool empty() const {
      return (keyval == -1);
   }
   
   /********************************************************\
      overloaded operators
   \********************************************************/
   
   // overloaded assignment operator
   dataObject& operator = (const dataObject &other) {
      dataObject temp(other);
      swapObjects(temp);
      return *this;
   }
   
   // overloaded relational operators
   bool operator == (const dataObject &other) const {
      return (keyval == other.keyval);
   }
   
   bool operator != (const dataObject &other) const {
      return (keyval != other.keyval);
   }
   
   bool operator > (const dataObject &other) const {
      return (keyval > other.keyval);
   }
   
   bool operator < (const dataObject &other) const {
      return (keyval < other.keyval);
   }
   
   bool operator >= (const dataObject &other) const {
      return (keyval >= other.keyval);
   }
   
   bool operator <= (const dataObject &other) const {
      return (keyval <= other.keyval);
   }
};

#endif
