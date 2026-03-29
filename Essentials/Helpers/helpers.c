/******************************************************************************
 *  Description     : The file contains the shuffle array.
 *  Author/s        : Agamata, Loraine Beatriz C.
 *                    Lapuz, Dale Lucian M.
 *  Section         : S12A & S22A
 *  Last Modified   : March 27, 2026
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/

#ifndef HELPERS_C // Include this to prevent redefinition error
#define HELPERS_C // Include this to prevent redefinition error

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "..\defs.h"
//#define Seed randomInt()
/******************************************************************************
 * NOTE: These functions are placed here in helpers_2.c to demonstrate code
 * modularization across multiple files. You may move them to different files
 * if it better fits your code organization.
 ******************************************************************************/

 /*
 * This function asks the user for a number and returns it as an int
 * A safer way to get int
 */
int numInput()
{
    char storage[5];
    int choice;

    printf("Enter choice: ");
    fgets(storage, sizeof(storage), stdin);
    storage[strcspn(storage, "\n")] = 0;

    choice = atoi(storage);
    return choice;
}

/*
* This function reads a string of text from the user and stores it in a variable
*/
void strInput(char buffer[], int size)
{
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

/**
 * Initializes the random number generator
 * @pre Should only be called once at the start of the program
 */
void initRandom()
{
  srand(time(0)); // Initialize the seed for the random number generator
}

/**
 * Generates and returns a random integer between 0 and 99
 * @return A random integer between 0 and 99
 * @pre initRandom() has been called prior to this function call
 */
int randomInt()
{
  return rand() % 100; // Generate a random number from 0 to 99
}

/**
 * Shuffles an array of any data type using the Fisher-Yates algorithm
 * @param array Pointer to the array to be shuffled
 * @param n Number of elements in the array
 * @param elem_size Size of each element in the array (use sizeof(data_type))
 * @param seed For setting the random order (providing thes same seed value
 *          will produce the same shuffle arrangement)
 */
void shuffle(void *array, size_t n, size_t elem_size, unsigned int seed)
{
  unsigned char *arr = (unsigned char *)array;
  srand(seed); // Set the seed for reproducibility

  for (size_t i = n - 1; i > 0; i--)
  {
    size_t j = rand() % (i + 1); // Random index from 0 to i

    // Swap elements
    unsigned char temp[elem_size];
    memcpy(temp, arr + i * elem_size, elem_size);
    memcpy(arr + i * elem_size, arr + j * elem_size, elem_size);
    memcpy(arr + j * elem_size, temp, elem_size);
  }
}

#endif // HELPERS_C; Include this to prevent redefinition error

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