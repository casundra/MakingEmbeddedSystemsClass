# Week 8 Homework - Heaps and Stacks

A copy of my final project code thus far is here, with some stuff commented out so that I can have a nice 1 Hz serial data output.

## Variables
I'm printing out:
* Stack Pointer
* Heap Pointer (constantly incrementing with a malloc just for funsies)
* Initialized Global Variable
* Uninitialized Global Variable
* Initialized Variable in main() before while(1) (what I'm calling Setup)
* Uninitialized Variable in main() before while(1)
* Static Variable in while(1)
* Normal Variable in while(1)

```
Stack Pointer:  20041FC0  
Heap Pointer:   20006538  
Beginning of bss:       20003548  
Endinging of bss:       20004438  
Initialized Global Variable:    20003354  
Uninitialized Global Variable:  20004430  
Initialized Setup Variable:     20041FD5  
Uninitialized Setup Variable:   20041FD8  
Static While(1) Variable:       2000416C  
Normal While(1) Variable:       20041FD6
```

Things on the Stack:
* Initialized Setup Variable
* Uninitialized Setup Variable
* Normal While(1) Variable

Things on the Heap:
* Initialized Global Variable
* Uninitialized Global Variable, in bss
* Static While(1) Variable, in bss

It makes sense that static variables are on the heap since they can't be "popped" - their value has to be remembered from loop to loop.  So heap storage is where they go.  Makes sense that "uninitialized" global variable is in bss since I believe zero is the default value.  Also makes sense that our static while(1) variable is in bss since it was actually initialized to zero.  "Initialized Global Variable" is not in bss, which makes sense because that one was initialized to the value of 1.

Interesting that variables in setup remain on the stack even though they're not ever going to be used again.  Seems like a waste.

Many thanks to Daniel for staying long on the homework help session and helped me with heap and stack variables - I had no idea where to look for them or how to access them.  And then I belatedly just saw the hint link now in the Discord.  Didn't even know there were homework hint links!

## Linker Script
Found it in:  
C:\Users\(username)\.platformio\packages\toolchain-gccarmnoneeabi\arm-none-eabi\lib\ldscripts  
Called "armelf.nx" (thank you internet)  
..and that's where I chicken out and say hell no to messing with things that are vital to operation that I don't understand.  :)

## Map File
Success!  Thanks to Tony Habib for the help - turns out that build_flags in platformio.ini are quite sensitive to whitespace.  Got rid of all around the -Wl section and it worked!  Now output.map is generated!  So exciting.  There were no real surprises, the addresses for stack, bss, initial heap were the same as output in the code.

```
; the below is very sensitive to whitespace!  Make sure there is none before and after, especially with -Wl options

build_flags = ; SDK 1.2.0 and above
        -D LIB_PICO_STDIO_USB
        -D LIB_PICO_STDIO_UART
        ;-D LIB_PICO_STDIO_SEMIHOSTING
        ;-v ; verbose output, holy shitballs this adds like 30+ seconds to the compile time
        -Wl,-Map,output.map
```
