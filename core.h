/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : Ben Akram
Student ID#: 158523217
Email      : bakram4@myseneca.ca
Section    : BTP100NAA BSD Program

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//3. check user input of int type and return the number while validate correct input

int inputInt();

//4. check user input of int type and return the number while validate input is greater 
//   than 0.

int inputIntPositive();

//5. Get user input of int type and return the number while validate input is within
//   range.

int inputIntRange(int lowerBound, int upperBound);

//6. Get user input of char type and return the number while validate input to matching
//   characters in the string.

char inputCharOption(const char validChars[]);

//7. obtain user input for a C string value with a length (number of
//characters) in the character range specified by the 2nd and 3rd arguments received(inclusive).

void inputCString(char terString[], int minValue, int maxVlaue, int flag);

//8. display an array of 10-character digits as a formatted phone
//   number

void  displayFormattedPhone(const char validPhoneNum[]);


// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H