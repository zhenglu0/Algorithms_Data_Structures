#ifndef __HANDLE_H
#define __HANDLE_H

class Handle {
    
public:
    // Constructor for Handle
    Handle(int i):index(i){}
    // Return the index
    int getIndex(){ return index; }
    // Set the index
    void setIndex(int i){ index = i; }
    
private:
    int index; // The key of the Handle
    
};

#endif
