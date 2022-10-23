/****************************************************************************
 *  (c) Nabeel Nayyar (2022)                                                *
 *     University of Texas                                                  *
 *     CSE 3320 | Operating Systems | OpenTerm v1.0                         *
 *                                                                          *
 *              < Supplementary Functions used by OpenTerm >                *
 ****************************************************************************/

#include "OpenTerm.h"


// Traverses the working directory and returns a pointer to a list of the 
//  contents of the directory pointed towards
// Not really how I intended it to be but rn it works
// Right now returns the cursor position tho
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
int ConsoleShiftDirectory(char *gtdir){
    int chre;
    chre = chdir(gtdir);
    
    if (chre < 0) {
        return 0;
    } else {
        return 1;
    }
}
