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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

//1. Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

//2. Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

//3. check user input of int type and return the number while validate correct input

int inputInt()
{
    int value = 0;
    char newLine = 'x';

    do
    {
        scanf("%d%c", &value, &newLine);

        if (newLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (newLine != '\n');

    return value;
}

// 4. check user input of int type and return the number while validate input is greater
//   than 0.

int inputIntPositive()
{
    int value = -1;
    char newLine = 'x';
    do
    {
        scanf("%d%c", &value, &newLine);

        if (newLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        else if (value <= 0)
        {

            printf("ERROR! Value must be > 0: ");
        }
    } while (value <= 0 || newLine != '\n');

    return value;
}

//5. Get user input of int type and return the number while validate input is within
//   range.

int inputIntRange(int lowerBound, int upperBound)
{
    int value = 0;
    char newLine = 'x';

    do
    {
        scanf("%d%c", &value, &newLine);

        if (newLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        else if (value < lowerBound || value > upperBound)
        {

            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }
    } while (value < lowerBound || value > upperBound || (newLine != '\n'));

    return value;
}

//6. Get user input of char type and return the number while validate input to matching
//   characters in the string.
char inputCharOption(const char validChars[])
{
    char checkNewLine = '?';
    char retChar = '?';
    int i = 0, indexMatch = -1;
    do 
    {
        scanf("%c%c", &retChar, &checkNewLine);

        if (checkNewLine == '\n')
        {
            for (i = 0; validChars[i] != '\0'; i++)
            {

                if (retChar == validChars[i])
                {
                    indexMatch = 0;
                }

                else if  ((validChars[i] != retChar) && (indexMatch != 0))
                {
                    indexMatch = -1;
                    clearInputBuffer();
                    printf("ERROR: Character must be one of [%s]: ", validChars);
                }

            }
        }
        else
        {
            clearInputBuffer();
            printf("ERROR: Character must be one of [%s]: ", validChars);
        }
      
      
    } while (indexMatch);

    return retChar;
}



    



///7. obtain user input for a C string value with a length (number of
//characters) in the character range specified by the 2nd and 3rd arguments received(inclusive).

void inputCString(char retString[], int lowerBound, int upperBound, int flag)
{
    int size = 0;
    char ret[255] = { '\0' };

    do
    {
        scanf("%[^\n]", ret);

        size = strlen(ret);

        if (lowerBound == upperBound && size != upperBound)
        {
            clearInputBuffer();
            if (flag == 1)
            {
                printf("ERROR: String length must be no more than %d chars: ", upperBound);
            }
            else
            {
                printf("Invalid %d-digit number! Number: ", upperBound);
            }
            

        }
        else if (lowerBound < upperBound && (size > upperBound))
        {
            clearInputBuffer();
           

            if (flag == 1)
            {
                printf("ERROR: String length must be no more than %d chars: ", upperBound);
            }
            else
            {
                printf("Invalid %d-digit number! Number: ", upperBound);
            }
            

        }
        else if (lowerBound < upperBound && (size < lowerBound || size > upperBound))
        {
            clearInputBuffer();
           
            if (flag == 1)
            {
                printf("ERROR: String length must be no more than %d chars: ", upperBound);
            }
            else
            {
                printf("Invalid %d-digit number! Number: ", upperBound);
            }

        }

    } while (size > upperBound || size < lowerBound);

    clearInputBuffer();

    strcpy(retString, ret);
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////
//8. display an array of 10-character digits as a formatted phone number   

void  displayFormattedPhone(const char validPhoneNum[])
{
    char retPhoneNum[255] = { '\0' };
    int i = 0, charCheck = 0, size = 0, rightSize = 10;
    int keepLoop = 1; // flag

    do
    {
        if (validPhoneNum == NULL || validPhoneNum[size] == '\0')
        {
            keepLoop = 0;
            printf("(___)___-____");
        }
        else
        {

            strcpy(retPhoneNum, validPhoneNum);

            size = strlen(retPhoneNum);

            if (rightSize == (size))
            {
                for (i = 0; i < size; i++)
                {
                    if (retPhoneNum[i] < 48 || retPhoneNum[i] > 57) // not only digits in the string 
                    {
                        charCheck++;
                    }
                }

                if (!(charCheck))// print the phone number without digits.
                {

                    printf("(%.3s)%.3s-%.4s", retPhoneNum, retPhoneNum + 3, retPhoneNum + 6);
                    keepLoop = 0;
                }
                else
                {
                    charCheck = 0;
                }
            }
        }

    } while (keepLoop);
}
