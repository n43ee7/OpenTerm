/****************************************************************************
 *  (c) Nabeel Nayyar (2022)                                                *
 *     University of Texas at Arlington                                     *
 *     CSE 3320 | Operating Systems | OpenTerm v1.0                         *
 *                                                                          *
 *              < Main Header file for OpenTerm >                           *
 ****************************************************************************/

#ifndef PRIMARY_HEADER_H
#define PRIMARY_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

// Subsystem check
#ifdef _WIN32
    #include <Windows.h> // Windows Subsystem Detected
#else
    #include <unistd.h> // Linux Subsystem Detected
#endif

// Defining pre-processor directives
#define DIR_LEN 2048    // Fixed directory length
#define CMD_LEN 500     // Fixed Terminal Command length 

#define WINDOW_R 21     // Terminal Window Verticle Length
#define WINDOW_L 73     // Terminal Window horizontal Length
#define WINDOW_Y 2      // Terminal Window Y from Top
#define WINDOW_X 3      // Terminal Window X from Left 

// Declaring the external functions in the header 
int ConsoleDirectoryResponse(DIR *OpenDir, WINDOW *object, int cursor);
int ConsoleShiftDirectory(char *gtdir);
void _ConsoleDirectoryResponse(DIR *OpenDir, char REG[DIR_LEN]);
int strXsr(char key[CMD_LEN], char str[DIR_LEN], char delim[2]);

#endif