
░ ████▓▒░▒██▒ ░  ░░▒████▒▒██░   ▓██░  ▒██▒ ░ ░▒████▒░██▓ ▒██▒▒██▒   ░██▒░██░▒██░   ▓██░ ▓█   ▓██▒░██████▒
░ ▒░▒░▒░ ▒▓▒░ ░  ░░░ ▒░ ░░ ▒░   ▒ ▒   ▒ ░░   ░░ ▒░ ░░ ▒▓ ░▒▓░░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒  ▒▒   ▓▒█░░ ▒░▓  ░
  ░ ▒ ▒░ ░▒ ░      ░ ░  ░░ ░░   ░ ▒░    ░     ░ ░  ░  ░▒ ░ ▒░░  ░      ░ ▒ ░░ ░░   ░ ▒░  ▒   ▒▒ ░░ ░ ▒  ░
░ ░ ░ ▒  ░░          ░      ░   ░ ░   ░         ░     ░░   ░ ░      ░    ▒ ░   ░   ░ ░   ░   ▒                                                                                                              

_With Great powers in C, comes great responsibilities in C_
________________________________________________________________________________________
# OpenTerm
C-based basic computer shell. Immitation Linux Shell enviornment with an 80s DOS-like computer Enviornment. 

_Recommended Using Linux for compilation and execution of the Shell instance_ 
_________________________________________________________________________________________
#### Prerequistes: 
 \
nCurses 5.7.0 or later linked with GCC
________________________________________________________________________________________
Step 1) Please make sure you are in the project dependency "??"

#### Installation & Importing Project Dependencies
 \
Clone the Reposiroty: 
```
$ git clone https://github.com/n43ee7/OpenTerm
```
Move to the _installed_ Directory:
```
$ cd OpenTerm/
```
Compile the Source Code:
_NOTE: Please use GCC instead of G++ for stabler results_
 \
 ```
gcc OpenTermv1.c OpenTermSup.c -lncurses -o OpenTerm
``
Now run a shell Instance:
```
$ ./OpenTerm
```
