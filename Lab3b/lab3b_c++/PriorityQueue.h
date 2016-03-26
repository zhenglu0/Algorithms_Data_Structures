//
// PRIORITYQUEUE.H
// A priority queue class supporting sundry operations needed for
// Dijkstra's algorithm.  This class is a template over some
// value type T.  To create a queue that works on objects of class
// Foo, declare, e.g., "PriorityQueue<Foo> x;".
//
// You should implement all the class methods in this header file,
// since the class definition must be visible at the point that the
// template is instantiated.
//
#ifndef __PRIORITYQUEUE_H
#define __PRIORITYQUEUE_H

#include "Handle.h"
#include "PQNode.h"

#include <iostream>
#include <vector>


template <class T>
class PriorityQueue {
    
public:

    // constructor
    //
    PriorityQueue(void)
    {
    }

    // destructor
    ~PriorityQueue(void)
    {
        // We should explicitly delete the objects in the memory heap
        // I will let OS deal with it this time, because all the handle
        // objects in the Handles were not deleted in main function
    }

    // Return true iff the queue is empty.
    //
    bool isEmpty(void)
    {
        return v.empty()? true : false;
    }

    // Insert a pair (key, value) into the queue, and return
    // a Handle to this pair so that we can find it later in
    // constant time.
    //
    Handle *insert(int key, T *value)
    {
        // Create a new node
        PQNode<T> *n = new PQNode<T>(v.size(),value);
        // Add the new node to the vector
        v.push_back(n);
        // Get the handle
        Handle *h = n->getHandle();
        // Decrease the key of the node, the original value is numeric_limits<int>::max()
        decreaseKey(h,key);
        // Return handle*
        return h;
    }

    // Return the smallest key in the queue.
    //
    int min(void)
    {
        return v[0]->getKey();
    }

    // Extract the (key, value) pair associated with the smallest
    // key in the queue and return its "value" object.
    //
    T *extractMin(void)
    {
        // Get the value of the min
        T* min = v[0]->getValue();
        // Swap the first node with the last node
        swapPQNode(v[0],v[v.size()-1]);
        // Set handle object special value 
        v[v.size()-1]->getHandle()->setIndex(-1);
        // Remove the last element at the end of the vector, which is v[v.size()-1])
        v.pop_back();
        // Fix the heap
        minHeapfy(0);
        // Return value
        return min;
    }


    // Look at the (key, value) pair referenced by Handle h.
    // If that pair is no longer in the queue, or its key
    // is <= newkey, do nothing and return false.  Otherwise,
    // replace "key" by "newkey", fixup the queue, and return
    // true.
    //
    bool decreaseKey(Handle *h, int newkey)
    {
        // If that pair is no longer in the queue, or its key is <= newkey,
        // do nothing and return false.
        if (h->getIndex() == -1 || v[h->getIndex()]->getKey() <= newkey)
            return false;
        // Set the newkey to the node, replace "key" by "newkey"
        v[h->getIndex()]->setKey(newkey);
        // Fixup the queue, and return true, if the parent is larger, we do the
        // swap operation
        while (h->getIndex() > 0 && v[parent(h->getIndex())]->getKey() > v[h->getIndex()]->getKey())
            swapPQNode(v[h->getIndex()],v[parent(h->getIndex())]);
        // Otherwise, replace "key" by "newkey", fixup the queue, and return true.
        return true;
    }


    // Get the key of the (key, value) pair associated with a 
    // given Handle. (This result is undefined if the handle no longer
    // refers to a pair in the queue.)
    //
    int handleGetKey(Handle *h)
    {
        return v[h->getIndex()]->getKey();
    }

    // Get the value object of the (key, value) pair associated with a 
    // given Handle. (This result is undefined if the handle no longer
    // refers to a pair in the queue.)
    //
    T *handleGetValue(Handle *h)
    {
        return v[h->getIndex()]->getValue();
    }
  
private:
    
    // Container used for Priority Queue, it store PQNode<T>
    std::vector< PQNode<T>* > v;
    
    // Find the Parent of the node
    int parent(int i) { return (i-1)/2; }
    
    // Find the left child of the node
    int left(int i) { return 2*i+1; }
    
    // Find the right child of the node
    int right(int i) { return 2*i+2; }
    
    // Swap two PQNode in the vector
    void swapPQNode(PQNode<T>* n1, PQNode<T>* n2)
    {
        // Store the temporary virables n1 and n2
        int keyTemp = n1->getKey();
        T* valueTemp = n1->getValue();
        int handleIndexTempN1 = n1->getHandle()->getIndex();
        int handleIndexTempN2 = n2->getHandle()->getIndex();
        Handle* handleTemp = n1->getHandle();
        // Set all the attributes of node2 to node1
        n1->setKey(n2->getKey());
        n1->setValue(n2->getValue());
        n1->setHandle(n2->getHandle());
        n1->getHandle()->setIndex(handleIndexTempN1);
        // Set all the attributes of node1 to node2
        n2->setKey(keyTemp);
        n2->setValue(valueTemp);
        n2->setHandle(handleTemp);
        n2->getHandle()->setIndex(handleIndexTempN2);
    }
    
    // min heapify function, used to fix one element violate the heap property, then
    // propergate down
    void minHeapfy(unsigned int i)
    {
        // Calcuate the left and the right child index
        unsigned int l = left(i);
        unsigned int r = right(i);
        unsigned int smallest;
        // Try to find the smallest element and remember its index
        if (l < v.size() && v[l]->getKey() < v[i]->getKey())
            smallest = l;
        else
            smallest = i;
        if (r < v.size() && v[r]->getKey() < v[smallest]->getKey())
            smallest = r;
        // Fix the violation
        if(smallest != i)
        {
            swapPQNode(v[i],v[smallest]);
            minHeapfy(smallest);
        }
    }
    
    
    // Here's how you give your operator<< for PriorityQueues access to
    // the guts of the queue.
    //
    template <class U>
    friend std::ostream &operator<< (std::ostream &, PriorityQueue<U> &);
    
};

  
// Print every element of the queue in the order in which it appears
// in the implementation (i.e. the array representing the heap).
//
template <class T>
std::ostream &operator<<(std::ostream &os, PriorityQueue<T> &q)
{
    // print out all the nodes in the queue by key and value
    for(unsigned int i = 0; i < q.v.size(); i++)
        os << "(" << q.v[i]->getKey() << ", " << *(q.v[i]->getValue()) << ")" << std::endl;

    return os;
}

#endif
