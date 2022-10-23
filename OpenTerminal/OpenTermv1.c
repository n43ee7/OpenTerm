/****************************************************************************
 *  (c) Nabeel Nayyar (2022)                                                *
 *     University of Texas                                                  *
 *     CSE 3320 | Operating Systems | OpenTerm v1.0                         *
 *                                                                          *
 *              < Main OpenTerm runtime >                                   *
 ****************************************************************************/

#include "OpenTerm.h"

// Declaring all existing functions in the scope
void StartScreenInit();
void TerminalScreen(WINDOW *object);
void TerminalInstance(WINDOW *object, int cursor);

int main(){
    WINDOW *term; // Assigning a window instance

    initscr();			// Opens the Terminal in Curses mode
    StartScreenInit();  // Function for the start screen of the terminal
    clear();            // Clearing the screen

    // TODO: Thread for realtime time???
    time_t terminalTimeObj;   // Creating an object of time
    struct tm *terminaltime;  // Using tm struct from time.h
    time(&terminalTimeObj);  
    terminaltime = localtime(&terminalTimeObj);
    printw("System Time: %s", asctime(terminaltime)); // asctime for proper output
    
    // Starting the Terminal window
    refresh();
    TerminalScreen(term);    

    endwin();			// Closes the Terminal window and clears memory
    return 0;
}

void StartScreenInit(){
    FILE *motoFilePtr;
    // Opening the Terminal Moto files and checking
    if ((motoFilePtr = fopen("motd_term.txt", "r")) == NULL){
        printf("[ER:555] There was an error opening core file. Exitting....\n");
        exit(0); // No mood to work. sorry
    }
	
    // Prints the Terminal MOTO/logo
    char c; 
    c = fgetc(motoFilePtr);
    while (c != EOF) {
        printw ("%c", c);
        c = fgetc(motoFilePtr);
    }
    fclose(motoFilePtr); // Closing I/O as soon as done
    
    refresh(); // To call sleep refresh
    sleep(3); // Threads waiting for 2 seconds
}

void TerminalScreen(WINDOW * object){

    object = newwin(WINDOW_R, WINDOW_L, WINDOW_Y, WINDOW_X); // Dimentions to window
    box(object, 0, 0);    // Creating standard box boundary around the window

    mvwprintw(object, 0, 1, "OpenTerm v1.0");  // Terminal Heading 
    wrefresh(object);                          // Refresh and display loaded curses window
    TerminalInstance(object, WINDOW_R);        // Creating a terminal instance
}

void TerminalInstance(WINDOW *object, int cursor){
    // Variables in the instance of this function
    char cwd[DIR_LEN], cmd[CMD_LEN], opr[CMD_LEN], oprnd[CMD_LEN], *token;;
    DIR *OpenDir;
    int cr = 1; // Window Console Cursor
    char LOCATER[DIR_LEN];
    int rt_status;

    // Main instance of the Shell running
    while (1) {
        getcwd(cwd, DIR_LEN);
        mvwprintw(object, 1, 1, "Current Directory: %s", cwd); // CWD Handler Anchored to (1,1)
        mvwprintw(object, cr+1, 2, "> $ ");   
        wrefresh(object);  
        
        mvwgetstr(object, cr+1, 6, cmd); // Take console input    
        // TODO: Breaking input command <OPERATOR OPERAND> 
        token = strtok(cmd, " ");
        strcpy(opr, token);

        // Checking terminal commands to execute them
        if (strcmp(opr, "exit") == 0) {           // Exit 
            mvwprintw(object, cr+2, 2, "[!] Exiting OpenTerm!");
            wrefresh(object);
            sleep(1);
            exit(1);

        } else if (strcmp(opr, "help") == 0) {    // Help
            mvwprintw(object, cr+2, 2, "========================[!] Help=========================");       
            mvwprintw(object, cr+3, 2, "> cd <DIR>      (Operator to change working directory)"); 
            mvwprintw(object, cr+4, 2, "> ls            (Lists contents of the working directory)"); 
            mvwprintw(object, cr+5, 2, "> cls           (Clears the terminal screen)"); 
            mvwprintw(object, cr+6, 2, "> editfn <FILE> (Edit file name from a working directory)");
            mvwprintw(object, cr+7, 2, "> exit          (Exits the terminal session)"); 
            mvwprintw(object, cr+8, 2, "> rm <FILE>     (Deletes a file)"); 
            mvwprintw(object, cr+9, 2, "> run <FILE>    (Runs a executable)"); 
            cr = cr + 9;

        } else if (strcmp (opr, "cls") == 0){     // Clear console screen
            wclear(object);
            refresh();
            TerminalScreen(object);
        
        } else if (strcmp(opr, "ls") == 0) {      // List contents of working directory
            OpenDir = opendir(".");
            cr = (ConsoleDirectoryResponse(OpenDir, object, cr+2)-1);

        } else if (strcmp(opr, "cd") == 0){       // Change working directory
            mvwprintw(object, cr+2, 2, "Change DIR to:");
            mvwgetstr(object, cr+2, 18, oprnd);
            int check = ConsoleShiftDirectory(oprnd);
            if (check == 0) {
                mvwprintw(object, cr+3, 2, "[!] Invalid path, try again.");
            }
            cr = cr+2;
            
        } else if (strcmp (opr, "rm") == 0){      // Delete a file in working directory
            mvwprintw(object, cr+2, 2, "Name DIR or File to delete:");
            mvwgetstr(object, cr+2, 30, oprnd);
            // Pass 1, check if file exists in Working directory
            OpenDir = opendir(".");
            _ConsoleDirectoryResponse(OpenDir, LOCATER);   
            if (strXsr(oprnd, LOCATER, " ") == 1) {
                // Pass 2, execute deletion of file    
                mvwprintw(object, cr+3, 2, "[/] Resource located, deleting..."); // Dont ask again
                if (remove(oprnd) == 0) {   // Safer use than system("rm -rf")
                    mvwprintw(object, cr+4, 2, "[/] Deleted successfully.");
                } else {
                    mvwprintw(object, cr+4, 2, "[X] Unable to delete the file. Check file permissions");
                }
                cr = cr + 4;
            } else {
                mvwprintw(object, cr+3, 2, "[!] Unable to locate item. Try again!");
                cr = cr + 3; 
            }
            
            
        } else if (strcmp (opr, "run") == 0) {    // Launches an executable file in working directory
            mvwprintw(object, cr+2, 2, "Name executable to RUN:");
            mvwgetstr(object, cr+2, 26, oprnd);
            // Pass 1, check existance of file to be executed
            OpenDir = opendir(".");
            _ConsoleDirectoryResponse(OpenDir, LOCATER);
            if (strXsr(oprnd, LOCATER, " ") == 1) {
                mvwprintw(object, cr+3, 2, "[S] Resource located, and executing...");
                // Since the the output of the other file is trival. curses will exit temporarily
                wrefresh(object);
                clear();
                endwin();
                strcpy(cmd, "./");
                strcat(cmd, oprnd);
                printf("%s\n", cmd);
                rt_status = system(cmd);  // Side-loaded application
                // Reconstruncting UI upon side-load completion
                initscr();
                cr = cr + 3;
            } else {
                mvwprintw(object, cr+3, 2, "[!] Unable to locate item. Try again!");
                cr = cr + 3; 
            }  
        } else if (strcmp (opr, "editfn") == 0) { // Edit file name
            // Pass 1, Locate and validate
            mvwprintw(object, cr+2, 2, "Enter File name to edit:");
            mvwgetstr(object, cr+2, 26, oprnd);
            OpenDir = opendir(".");
            _ConsoleDirectoryResponse(OpenDir, LOCATER);
            if (strXsr(oprnd, LOCATER, " ") == 1) {
                // File exists and is valid
                mvwprintw(object, cr+3, 2, "Enter a new name for file '%s'", oprnd);
                mvwprintw(object, cr+4, 2, ">");
                mvwgetstr(object, cr+4, 3, opr);

                // Pass 2, Lock file and change to oprnd            
                rt_status = rename(oprnd, opr);
                if (rt_status == 0) {
                    mvwprintw(object, cr+5, 2, "[/] The file name is edited successfully.");
                } else {
                    mvwprintw(object, cr+5, 2, "[X] The file name could not be edited");
                }
                wrefresh(object);
                cr = cr + 5;
            } else {
                mvwprintw(object, cr+3, 2, "[!] Unable to locate item. Try again!");
                cr = cr + 3;
            }
        } else {
            // Unrecognized or illegal command
            mvwprintw(object, cr+2, 2, "[X] Illegal Command entered, type 'help'");
            cr = cr + 1;  
            wrefresh(object);      
        }
        cr++; // Incrementing the cursor value now
        wrefresh(object); // Refresh to update ncurses content
        
        // Clearing window if reaching over cursor limit. LOST DATA?
        if (cr >= cursor) {
            wclear(object);
            refresh();
            TerminalScreen(object);
        }
        
    }
}
