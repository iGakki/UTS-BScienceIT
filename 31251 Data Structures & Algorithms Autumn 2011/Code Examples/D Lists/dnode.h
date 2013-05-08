#ifndef DNODE_H
#define DNODE_H

/********************************************************\
   template node class for doubly linked list
\********************************************************/

template <typename dataType> struct dnode 
{
   dataType data;
   dnode *prev, *next;
         
   // constructors
   dnode() : prev(NULL), next(NULL) {
   }
   
   dnode(const dataType& dataItem, dnode *prevPtr, dnode *nextPtr) :
      data(dataItem), prev(prevPtr), next(nextPtr) {
   }
};

#endif
