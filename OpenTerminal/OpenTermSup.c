/****************************************************************************
 *  (c) Nabeel Nayyar (2022)                                                *
 *     University of Texas at Arlington                                     *
 *     CSE 3320 | Operating Systems | OpenTerm v1.0                         *
 *                                                                          *
 *              < Supplementary Functions used by OpenTerm >                *
 ****************************************************************************/

#include "OpenTerm.h"


// Traverses the WD and returns cute looking stuff. I need
//    to take this away but rn its ok. I think
int ConsoleDirectoryResponse(DIR *OpenDir, WINDOW *object, int cursor){
    struct dirent *entrydir;
    int files = 0;
    if (OpenDir) {
        while ((entrydir = readdir(OpenDir)) != NULL) {
            mvwprintw(object, cursor, 2, "File %3d: %s", files, entrydir->d_name);
            cursor++; files++;
        }
    closedir(OpenDir);
    }

    return cursor;        
}

// Initiates a change in directory with exception handling
// Returns 1 for sucessfull and 0 for failed change
int ConsoleShiftDirectory(char *gtdir) {
    int chre;
    chre = chdir(gtdir);
    
    if (chre < 0) {
        return 0;
    } else {
        return 1;
    }
}

// ConsoleDirResponse Returns the List of the contents of the items in the
//   working directory.
void _ConsoleDirectoryResponse(DIR *OpenDir, char REG[DIR_LEN]) {
    struct dirent *entrydir;

    if (OpenDir) {
        while ((entrydir = readdir(OpenDir)) != NULL) {
            //printf("%s\n", entrydir->d_name);
            strcat(REG, entrydir->d_name);
            strcat(REG, " "); // Added buffer layer for search
        }
        closedir(OpenDir);
    }
}

// Searching key and dictionary
// 1 -> for valid | 0 -> for invalid constrain 
// Understanding system constrains while searching
//  INPUTS:          500                 2048
int strXsr(char key[CMD_LEN], char str[DIR_LEN], char delim[2]) {

    char *token;
    token = strtok(str, delim);
   
    while (token != NULL) {
        if (strcmp(key, token) == 0) {
            return 1;
        }
        token = strtok(NULL, delim);
    }
    return 0;
}