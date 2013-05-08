#ifndef LINHASH_H_
#define LINHASH_H_

#include <stdexcept>

/********************************************************\
   template class for a linear hash table
\********************************************************/
      
template <typename dataType> class linHashtable
{  
   private:
      dataType *theTable;
      int range, numItems;
      
   public:
      /*******************************************************\
         constructors
      \*******************************************************/
      
      // constructor
      
      linHashtable(int r) : range(r), numItems(0) {
         theTable = new dataType[r];
      }
      
      /*******************************************************\
         status functions
      \*******************************************************/
      
      bool empty() const {
         return (numItems == 0);
      }
      
      bool full() const {
         return (numItems == range); 
      }         
      
      int getRange() const {
         return range;
      }
      
      int size() const {
         return numItems;
      }
       
      /*******************************************************\
         insertion erasure and find functions
      \*******************************************************/
      
      int insert(const dataType& newData)
      {  
         // insert newData into hash table and return number 
         // of clashes that occured while finding empty slot
         
         if (full()) {
            throw std::out_of_range("hash table is full");
         }
         
         int hashval = newData.getHashval(range);
         
         if (hashval < 0 || hashval >= range) {
            throw std::out_of_range("hash value out of range");
         }   
         
         int numClashes = 0;
         
         // starting with hashval, find place for newData in table
         while (!theTable[hashval].empty()) {
            hashval = (hashval + 1) % range;
            numClashes++;
         }
         
         theTable[hashval] = newData;
         numItems++;
         return numClashes;
      }
         
      void erase(const dataType& delData) 
      {
         int hashval = delData.getHashval(range);
         int next, start = hashval;
         
         // starting with hashval, find place of deldata in table
         while (theTable[hashval] != delData) {
            if (theTable[hashval].empty()) return;
            hashval = (hashval + 1) % range;
         }
         
         // find any other data in hashtable with same hash value and move.
         start = hashval;
         next = (start + 1) % range;
         hashval = delData.getHashval(range);
         
         while (!theTable[next].empty()) {
            if (theTable[next].getHashval(range) == hashval) {
               theTable[start] = theTable[next];
               start = next;
            }
            next = (next + 1) % range;            
         }   
         
         // make final space empty
         dataType emptyData;
         theTable[start] = emptyData;
         numItems--;
      }
      
      bool find(const dataType &findData, dataType &foundData) const 
      {   
         int hashval = findData.getHashval(range);
         
         // starting with position at hashval, find findData in table
         while (theTable[hashval] != findData) {
            if (theTable[hashval].empty()) return false;
            hashval = (hashval + 1) % range;
         }
         foundData = theTable[hashval];
         return true;
      }
};

#endif
