***************************************************************************Lab 3aAuthor: Zheng LuoEmail: luozheng@wustl.edu******************************************************************************************************************Brief Summary of Implementation***************************************
In PQNode.h I used 

    int key; // The key of the node
    T *value; // The value of the node
    Handle *handle; // The pointer pointed to handle object

to store the everything. 

In the Handle.h I used an attribute index to store the object index in the vector, when the nodes in the queue is extracted. Its index will be set to -1, so that means we invalidate the handle.

