#ifndef DLIST_H_
#define DLIST_H_

#include <stdexcept>

template <typename dataType> class dlist;

#include "dnode.h"
#include "dlistIterator.h"
#include "dlistConstIter.h"


/********************************************************\
   template class for doubly linked list
\********************************************************/
      

template <typename dataType> class dlist
{  
   private:
      dnode<dataType> *head, *tail;
      int numItems;
      
   public:
      /********************************************************\
         iterator friendship and functions
      \********************************************************/
      
      friend class dlistIterator<dataType>;
      friend class dlistConstIter<dataType>;
      
      dlistIterator<dataType> begin() {
         return dlistIterator<dataType>(this, head);
      }
      
      dlistConstIter<dataType> begin() const {
         return dlistConstIter<dataType> (this, head);
      }
      
      dlistIterator<dataType> end() {
         return dlistIterator<dataType>(this, NULL);
      }
      
      dlistConstIter<dataType> end() const {
         return dlistConstIter<dataType>(this, NULL);
      }
   
      /********************************************************\
         constructor and destructor functions
      \********************************************************/
      
      // default constructor
      dlist() :
         head(NULL), tail(NULL), numItems(0) {
      }
      
      // copy constructor
      dlist(const dlist<dataType> &other) :
         head(NULL), tail(NULL), numItems(0) { 
         for (dlistConstIter<dataType> itr = other.begin(); itr != other.end(); itr++) {
            push_back(*itr);
         }
      }
      
      // destructor
      ~dlist() {
         while(head != NULL) {
            // delete every dnode in list
            dnode<dataType> *current = head;
            head = head->next;
            delete current;
         }
      }
      
      /********************************************************\
         misc functions
      \********************************************************/
      
      void swap(dlist<dataType> &other) {
         std::swap(numItems, other.numItems);
         std::swap(head, other.head);
         std::swap(tail, other.tail);
      }
      
      bool empty() {
         return (numItems == 0);
      }
      
      int size() {
         return numItems;
      }

      bool find(const dataType &findData, dlistIterator<dataType> &itr)
      {
         // function for finding something in a dlist

         for (itr = begin(); itr != end(); itr++) {
            if (*itr == findData) return true;
         }
         return false;
      }
 
      /********************************************************\
         push and insertion functions
      \********************************************************/
      
      void push_front(const dataType &item) {
         head = new dnode<dataType>(item, NULL, head);
         if (!empty()) {
            head->next->prev = head;
         }
         else
         {
            tail = head;
         }
         numItems++;
      }
      
      void push_back(const dataType &item) {
         if (!empty()) {
            tail->next = new dnode<dataType> (item, tail, NULL);
            tail = tail->next;
            numItems++;
         } else {
            push_front(item);
         }
      }
      
      dlistIterator<dataType> insert(dlistIterator<dataType> pos, const dataType &item) {
         if (pos.current == head) {
            push_front(item);
            return begin();
         } else if (pos.current == NULL) {
            push_back(item);
            return dlistIterator<dataType>(this, tail);
         } else {
            dnode<dataType> *newNode = new dnode<dataType>(item, pos.corrent->prev, pos.current);
            pos.current->prev->next = newNode;
            pos.Current->prev = newNode;
            numItems++;
            return dlistIterator<dataType>(this, newNode);
         }
      }
      
      /********************************************************\
         pop and erase functions
      \********************************************************/
      
      void pop_front() {
         if (empty()) {
            throw std::invalid_argument("Attempting to pop front of empty list");
         }
         
         // slice out the front node
         dnode<dataType> *removeNode = head;
         head = head->next;
         if (head != NULL) {
            head->prev = NULL;
         } else {
            tail = NULL;
         }
         
         delete removeNode;
         numItems--;
      }

      void pop_back() {
         if (empty()) {
            throw std::invalid_argument("Attempting to pop back of empty list");
         }
         
         // slice out the back node
         dnode<dataType> *removeNode = tail;
         tail =  tail->prev;
         if (tail != NULL) {
            tail->next = NULL;
         } else {
            head = NULL;
         }
         
         delete removeNode;
         numItems--;
      }
      
      dlistIterator<dataType> erase(dlistIterator<dataType> &pos) {
         if (empty()) {
            throw std::invalid_argument("Attempting to erase from empty list");
         }
         if (pos == end()) {
            throw std::invalid_argument("Attempting to erase end()");
         }
         
         dlistIterator<dataType> returnIter = pos;
         returnIter++;
         
         if (pos.current == head) {
            pop_front();
         } else if (pos.current == tail) {
            pop_back();
         } else {
            dnode<dataType> *removeNode = pos.current;
            removeNode->prev->next = removeNode->next;
            removeNode->next->prev = removeNode->prev;
            numItems--;
            delete removeNode;
         }
         return returnIter;
      }
      
      /********************************************************\
         overloaded operators
      \********************************************************/
      
      // assignment operator
      dlist<dataType>& operator = (const dlist<dataType> &other) {
         dlist<dataType> tempCopy(other);
         swap(tempCopy);
         return *this;
      }
   
};

#endif
