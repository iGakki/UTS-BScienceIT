#ifndef DLISTITERATOR_H_
#define DLISTITERATOR_H_

#include "dnode.h"

/********************************************************\
   template iterator class for doubly linked list class
\********************************************************/

template <typename dataType> class dlistIterator
{
   friend class dlist<dataType>;
   
   private:
      dlist<dataType> *parent;
      dnode<dataType> *current;
      
   public:
      
      // constructor
      dlistIterator(dlist<dataType> *myParent, dnode<dataType> *position) :
         parent(myParent), current(position) {
      }
   
      // overloaded dereference operator
      dataType& operator * () const {
         if (current == NULL) {
            throw std::invalid_argument("Attempting to dereference NULL in dlistIterator");
         }
         return current->data;
      }
      
      // overloaded arrow operator
      dataType* operator -> () const {
         if (current == NULL) {
            throw std::invalid_argument("Attempting to dereference NULL in dlistIterator");
         }
         return &(current->data);
      }
      
      // overloaded prefix increment operator
      dlistIterator<dataType> operator ++ () {
         if (current == NULL) {
            throw std::invalid_argument("Attempting to advance past end in dlistIterator");
         }
         current = current->next;
         return *this;
      }
      
      // overloaded postfix increment operator
      dlistIterator<dataType> operator ++ (int) {
         dlistIterator<dataType> current_data = *this;
         ++(*this);
         return current_data;
      }
      
      // overloaded prefix decrement operator
      dlistIterator<dataType> operator -- () {
         if (current == current->head) {
            throw std::invalid_argument("Attempting to move before begin in dlistIterator");
         }
         if (current == NULL) {
            current = parent->tail;
         } else {
            current = current->prev;
         }
         return *this;
      }
      
      // overloaded prefix decrement operator
      dlistIterator<dataType> operator -- (int) {
         dlistIterator<dataType> current_data = *this;
         --(*this);
         return current_data;
      }
      
      // overloaded equality operator
      bool operator == (const dlistIterator &other) {
         return current == other.current;
      }
      
      // overloaded inequality operator
      bool operator != (const dlistIterator &other) {
         return current != other.current;
      }
};

#endif
