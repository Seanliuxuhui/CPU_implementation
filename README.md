# CPU_Implementation
<p>This repository will be changed all the time untill all the functions are implemented. </p>
</br>
<h3>Assignment 1 </h3>
<p>Assignment one is the basic implementation of the cpu with about 40 instruction being set to deal with different kinds of instruction
calls. When pulling this assignemnt directory out and pushing it into your linux os, you can run the command 'make' to first compile
some pre-write file. Then, you can run the command './xsim 10000(this number is arbitary) file.xo (this file extension is built by running 
./xas file.xas file.xo)'. Eventually, you are able to see the output after each instructions are handled correctly.
Within the assignment 1, there is another file called memcpy.xas, which deals with the memory copy function to copy an array of data 
from source memory block to destination memory block.</p>

<h3>Assignment 2 </h3>
<p>
Assignment 2 envolves with 5 more instructions that deals with interrupt calls. They are cli, trap and other 3 instructions. 
now when running './xsim 10000(arbitary rounds) .xo file or executable file 1000 (number of interrupts)', the output will be determined 
by the executable file. If, for instances, you use command ./xsmkos xos kernel.xo yello.xo zello.xo hello.xo goodbye.xo, you will have 
four programs running at the same time, which means the output will be 4 types of printing out.(for example yello.xo is designated to print out the 'Y')
Trap handler is also implemented in the kernel.xas and meant to deal with the trap call. 
</p>


