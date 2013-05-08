#ifndef DLISTCONSTITER_H_
#define DLISTCONSTITER_H_

#include "dnode.h"

/**************************************************************\
   template const iterator class for doubly linked list class
\**************************************************************/

template <typename dataType> class dlistConstIter
{
   friend class dlist<dataType>;
   
   private:
      const dlist<dataType> *parent;
      dnode<dataType> *current;
   
   public:
      
      // constructor
      
      dlistConstIter(const dlist<dataType> *myParent, dnode<dataType> *position) :
         parent(myParent), current(position) {
      }
      
      // overloaded dereference operator
      const dataType& operator * () const {
         if (current == NULL) {
            throw std::invalid_argument("Attempting to dereference NULL in dlistIterator");
         }
         return current->data;
      }
      
      // overloaded arrow operator
      const dataType* operator -> () const {
         if (current == NULL) {
            throw std::invalid_argument("Attempting to dereference NULL in dlistIterator");
         }
         return &(current->data);
      }
      
      // overloaded prefix increment operator
      dlistConstIter<dataType> operator ++ () {
         if (current == NULL) {
            throw std::invalid_argument("Attempting to advance past end in dlistIterator");
         }
         current = current->next;
         return *this;
      }
      
      // overloaded postfix increment operator
      dlistConstIter<dataType> operator ++ (int) {
         dlistConstIter<dataType> current_data = *this;
         ++(*this);
         return current_data;
      }
      
      // overloaded prefix decrement operator
      dlistConstIter<dataType> operator -- () {
         if (current == parent->head) {
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
      dlistConstIter<dataType> operator -- (int) {
         dlistConstIter<dataType> current_data = *this;
         --(*this);
         return current_data;
      }
      
      // overloaded equality operator
      bool operator == (const dlistConstIter &other) {
         return current == other.current;
      }
      
      // overloaded inequality operator
      bool operator != (const dlistConstIter &other) {
         return current != other.current;
      }
};

#endif
