/* Programmed by: Thomas Tiam-Lee
Description: This is a set of functions to help with the user interface for the machine project.
Last modified: AUG-15-2020
*/

#include <stdio.h>
#include <stdlib.h>

// #ifdef INTERFACE_C
// #define INTERFACE_C
#ifdef _WIN32
#include <windows.h>
#endif

/* Constants for colors
for use with iSetColor */
const int I_COLOR_WHITE = 1;
const int I_COLOR_RED = 0;
const int I_COLOR_BLUE = 4;
const int I_COLOR_GREEN = 3;
const int I_COLOR_YELLOW = 2;
const int I_COLOR_CYAN = 5;
const int I_COLOR_PURPLE = 6;

// For Windows terminal
#ifdef _WIN32
/* This function moves the cursor to the given location on the
command line.
@param (int) x is the column index of the desired location
@param (int) y is the row index of the desired location
@return (void)
*/
void iMoveCursor(int x, int y)
{
  COORD p = {x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

/* This function clears a rectangular portion of the screen, and
moves the cursor to the top-left corner of the rectangle after
clearing.
@param (int) x is the column index of the top-left point of the rectangular portion.
@param (int) y is the row index of the top-left point of the rectangular portion.
@param (int) width is the width of the rectangle.
@param (int) height is the height of the rectangle.
@return (void)
*/
void iClear(int x, int y, int width, int height)
{
  int i, j;
  for (i = 0; i < height; i++)
  {
    iMoveCursor(x, y + i);
    for (j = 0; j < width; j++)
    {
      printf(" ");
    }
    printf("\n");
  }
  iMoveCursor(x, y);
}

/* This function hides the cursor.
@return (void)
*/
void iHideCursor()
{
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 100;
  info.bVisible = FALSE;
  SetConsoleCursorInfo(consoleHandle, &info);
}

/* This function shows the cursor.
@return (void)
*/
void iShowCursor()
{
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 100;
  info.bVisible = TRUE;
  SetConsoleCursorInfo(consoleHandle, &info);
}

/* This function sets the color of any output statement
such as printf.
@param (int) color is an integer representing the desired color (refer to available color constants above).
@return (void)
*/
void iSetColor(int color)
{
  WORD colorAttr;
  if (color == I_COLOR_WHITE)
  {
    colorAttr = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
  }
  else if (color == I_COLOR_RED)
  {
    colorAttr = FOREGROUND_RED | FOREGROUND_INTENSITY;
  }
  else if (color == I_COLOR_BLUE)
  {
    colorAttr = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
  }
  else if (color == I_COLOR_GREEN)
  {
    colorAttr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
  }
  else if (color == I_COLOR_YELLOW)
  {
    colorAttr = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
  }
  else if (color == I_COLOR_CYAN)
  {
    colorAttr = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
  }
  else if (color == I_COLOR_PURPLE)
  {
    colorAttr = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorAttr);
}
// For Linux and MacOS terminal
#else

/* This function sets the color of any output statement
such as printf.
@param (int) color is an integer representing the desired color (refer to available color constants above).
@return (void)
*/
void iSetColor(int color)
{
  if (color == I_COLOR_WHITE)
  {
    printf("\033[0m");
  }
  else if (color == I_COLOR_RED)
  {
    printf("\033[0;31m");
  }
  else if (color == I_COLOR_BLUE)
  {
    printf("\033[0;34m");
  }
  else if (color == I_COLOR_GREEN)
  {
    printf("\033[0;32m");
  }
  else if (color == I_COLOR_YELLOW)
  {
    printf("\033[0;33m");
  }
  else if (color == I_COLOR_CYAN)
  {
    printf("\033[0;36m");
  }
  else if (color == I_COLOR_PURPLE)
  {
    printf("\033[0;35m");
  }
}
#endif

/**
* This is to certify that this project is my/our own work, based on my/our personal
* efforts in studying and applying the concepts learned. I/We have constructed the
* functions and their respective algorithms and corresponding code by myself/ourselves.
* The program was run, tested, and debugged by my/our own efforts. I/We further certify
* that I/we have not copied in part or whole or otherwise plagiarized the work of other
* students and/or persons, nor did I employ the use of AI in any part of the deliverable.
*
* <Agamata, Loraine Beatriz C.> (12507121)
* <Lapuz, Dale Lucian M.> (12505919)
*/