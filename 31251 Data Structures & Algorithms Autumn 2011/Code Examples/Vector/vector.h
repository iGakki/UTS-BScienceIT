#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdexcept>

/********************************************************\
   template class for vector
\********************************************************/

template<typename dataType> class vector
{
   private:
      static const int INITIAL_CAPACITY = 100;
      int currentCapacity;
      int numItems;
      dataType* theData;

      /********************************************************\
         misc functions
      \********************************************************/
 
      void resize(int newCapacity) {
         if (newCapacity > currentCapacity) { 
            // set aside space with extra capacity
            currentCapacity = newCapacity;
            dataType *newData = new dataType[newCapacity];
         
            // copy the items across to the new space
            for (int i=0; i<numItems; i++) {
               newData[i] = theData[i];
            }
            
            delete[] theData;
            theData = newData;
         }
      }
      
      void resize() {
         resize(currentCapacity * 2);
      }

      void swap(vector<dataType> &other) {
         // swap this vector with the other
         std::swap(numItems, other.numItems);
         std::swap(currentCapacity, other.currentCapacity);
         std::swap(theData, other.theData);
      }
      
   public:
   
      /********************************************************\
         constructors and destructors
      \********************************************************/
      
      // default constructor
      vector() : 
         currentCapacity(INITIAL_CAPACITY),
         numItems(0) {
         theData = new dataType[INITIAL_CAPACITY];
      }
      
      // copy constructor
      vector(const vector<dataType> &other) : 
         currentCapacity(other.currentCapacity),
         numItems(other.numItems) {
         theData = new dataType[other.currentCapacity]; 
   
         for (int i=0; i<numItems; i++) {
            theData[i] = other.theData[i];
         }
      }
      
      // destructor
      ~vector() {
         delete[] theData;
      }
      
      /********************************************************\
         vector size functions
      \********************************************************/
      
      bool empty() const {
         return (numItems == 0);
      }
   
      int size() const {
         return numItems;
      }
   
      /********************************************************\
         search function 
      \********************************************************/

      int find(const dataObject &findData, dataObject foundData) {
         // find the location of data in with keyval
         // set foundData to the data when found in vector
         // return location in vector or -1 if not found
   
         int loc;
   
         for (loc=0; loc<numItems; loc++) {
            if (theData[loc] == findData) {
               foundData = theData[loc];
               return loc;
            }
         }
         return -1;   
      }
   
      /********************************************************\
         insertion and push functions
      \********************************************************/
      
      void insert(const dataType& newData, int index) {
         // check index range  
         if (index < 0) {
            throw std::out_of_range("vector<dataType>::insert");
         }
      
         // ensure there is enough capacity to insert newData
         while (numItems >= currentCapacity || index >= currentCapacity) {
            // current capacity insufficient for appending newData
            resize();
         }
         
         // make space for inserting newData
         for (int i=numItems; i > index; i--) {
            theData[i] = theData[i-1];
         }
         
         // insert the newData
         theData[index] = newData;
         numItems++;
      }
      
      void push_back(const dataType& newData) {
         // append newData to end of the vector
         insert(newData, numItems);
      }
      
      void push_front(const dataType& newData) {
         // insert newData to front of the vector
         insert(newData, 0);
      }
      
      /********************************************************\
         erase, remove and pop functions
      \********************************************************/
      
      void erase(int index) {
         // check index range  
         if (index < 0 || index >= numItems) {
            throw std::out_of_range("vector<dataType>::erase");
         }
         
         // close up data and overwrite data to be erased
         for (int i= index+1; i<numItems; i++) {
            theData[i-1] = theData[i];
         }
         numItems--;
      }
      
      void pop_back() {
         erase(numItems-1);
      }
      
      void pop_front() {
         erase(0);
      }
        
      /********************************************************\
         overloaded operators
      \********************************************************/
      
      // overloaded [] operator
      dataType& operator [] (int index) {
         if (index < 0 || index >= numItems) {
            throw std::out_of_range("vector<dataType>::operator []");
         }
         return theData[index];
      }
      
      // overloaded const [] operator
      const dataType& operator [] (int index) const {
         return (*this)[index];
      }
      
      // overloaded assignment operator
      vector<dataType>& operator = (const vector<dataType> &other) {
         vector<dataType> theCopy(other);
         swap(theCopy);
         return *this;
      }
};

#endif
