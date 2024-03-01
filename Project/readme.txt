To compile the code, make sure that you first have the MCB32 toolchain installed on your computer. If not, you can follow the instructions at: http://github.com/is1200-example-projects/mcb32tools/releases/

Next step is to opt to MCBTools using the following code in your respective terminal or another equivalent terminal: 

. /opt/mcb32tools/environment

Change to the project folder directory using the cd commands. Compile the code using "make" than install it on the chipkit using "make install" followed by the path to the serial port used by the Uno32, for example "make install TTYDEV=/dev/ttyS4" 

1. Open terminal
2. . /opt/mcb32tools/environment
3. change directory to project file
4. "make"
5. "make install TTYDEV=/dev/path-to-serial-port"
