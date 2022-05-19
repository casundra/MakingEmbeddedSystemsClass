# Week 8 Homework - Heaps and Stacks

A copy of my final project code thus far is here, with some stuff commented out so that I can have a nice 1 Hz serial data output.

I'm printing out:
* Stack Pointer
* Heap Pointer (constantly incrementing with a malloc just for funsies)
* Initialized Global Variable
* Uninitialized Global Variable
* Initialized Variable in main() before while(1) (what I'm calling the Setup)
* Uninitialized Variable in main() before while(1)
* Static Variable in while(1)
* Normal Variable in while(1)

Things on the Stack:
* Initialized Setup Variable
* Uninitialized Setup Variable
* Normal While(1) Variable

Things on the Heap:
* Initialized Global Variable
* Uninitialized Global Variable
* Static While(1) Variable

This makes sense to me as static variables can't be "popped" - their value has to be kept from loop to loop.  So heap storage is where they go.

Interesting that variables in setup remain on the stack even though they're not ever going to be used again.  Seems like a waste.

Many thanks to Daniel for staying long on the homework help session and helped me with heap and stack variables - I had no idea where to look for them or how to access them.


