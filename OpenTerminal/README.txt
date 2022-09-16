=================================================================================================================================================
                                                            OPENTERM README
=================================================================================================================================================
Nabeel Nayyar
8/22/2019


This is a curses implementation of a system terminal. The code is written in Standard C, to succesfully compile please follow the Compilation 
topic.

=================================================================================================================================================
                                                            Compilation Guidelines
=================================================================================================================================================

To compile this, please first have a linux machine, this program was developed and tested on a Debian kernel and the usage of NCURSES library has
trivial results on windows machines. Outputs may not be the as anticipated if compiling in any other operating system. 

    Step 1) Please make sure you are in the project dependency "??"

    > Now follow the comandline instructions:

        Step 2) $ gcc OpenTermv1.c OpenTermSup.c -lncurses -o OpenTerm

        Step 3) $ ./OpenTerm

Note: If post-execution the program reports any errors please view the Error Log of this 
=================================================================================================================================================
                                                                Commands of Use
=================================================================================================================================================
    > cd 
        Operator to change working directory
    
    > ls
        Lists contents of the working directory
    
    > clear
        Clears the terminal screen
    
    > editfn 
        Edit file name from a working directory
    
    > exit 
        Exits the terminal session
    
    > rm
        Operator to delete a file in the working directory
    
=================================================================================================================================================
                                                                Error Log
=================================================================================================================================================

    > ER:555 
    missing a "core file" please note the program depends on a few external files that should be INSIDE
    the working directory. These "core files" are used for pretty-printing certian details using NCURSES.  
