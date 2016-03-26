#ifndef __PQNODE_H
#define __PQNODE_H

#include <limits>

// Define a class PQNode for all the elements in the Priority Queue
//
template <class T>
class PQNode {
    
public:
    // Constructor for PQNode, set key the max value first,
    // and we decrease it later. Then we set the value for T value, 
    // finally we new a handle object and point to it, and initialze 
    // the index of handle object
    PQNode(int h, T* v):key(std::numeric_limits<int>::max()),value(v),handle(new Handle(h)){}
    // Return the key
    int getKey(){ return key; }
    // Set the index
    void setKey(int k){ key = k; }
    // Return the key
    T* getValue(){ return value; }
    // Set the index
    void setValue(T* v){ value = v; }
    // Return the handle
    Handle* getHandle(){ return handle; }
    // Set the index
    void setHandle(Handle* h){ handle = h; }
    
private:
    int key; // The key of the node
    T *value; // The value of the node
    Handle *handle; // The pointer pointed to handle object
    
};

#endif
