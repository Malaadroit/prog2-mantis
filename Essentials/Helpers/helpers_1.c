/******************************************************************************
 *  Description     : <short description of the file>
 *  Author/s        : <student1 full name (last name, first name)>
 *                    <student2 full name (last name, first name)>
 *  Section         : <your section>
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef HELPERS_1_C // Include this to prevent redefinition error
#define HELPERS_1_C // Include this to prevent redefinition error

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "..\defs.h"

/******************************************************************************
 * NOTE: These functions are placed here in helpers_1.c to demonstrate code
 * modularization across multiple files. You may move them to different files
 * if it better fits your code organization.
 ******************************************************************************/

/**
 * Displays the array of coordinates
 * @param points The array of coordinates to be displayed
 * @param arrSize The size of the array
 */
void displayCoodinates(Coordinate points[], int arrSize)
{
  // NOTE: This file includes defs.h, which provides access to the
  //       Coordinate structure definition.

  for (int i = 0; i < arrSize; i++)
    printf("(%d, %d)  ", points[i].x, points[i].y);

  printf("\n\n");
}



int numInput()
{
    char storage[5];
    int choice;

    printf("Enter choice: ");
    fgets(storage, sizeof(storage), stdin);

    choice = atoi(storage);
    return choice;
}

void strInput(char buffer[], int size)
{
    fgets(buffer, size, stdin);
}

#endif // HELPERS_1_C; Include this to prevent redefinition error
