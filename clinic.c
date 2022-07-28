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


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
//1. Display's the patient table header (table format)


void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
//2. Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
//3. Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
//4. Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
//5. main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
//6. Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
//7. Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN, 1);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}



// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
//8. Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
//9. (Copy your code from MS#2)

void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0, j = 0;

    displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);
        }
        if (patient[i].patientNumber == 0)
        {
            j++;
            if (j == max)
            {
                printf("*** No records found ***");
            }
        }
    }
    putchar('\n');
}

// Search for a patient record based on patient number or phone number
//10. (Copy your code from MS#2)

void searchPatientData(const struct Patient patient[], int max)
{
    int selection;
    do
    {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");

        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            searchPatientByPatientNumber(patient, max);
            
        }
        else if (selection == 2)
        {
            searchPatientByPhoneNumber(patient, max);
            
        }

    } while (selection);

    
}

// Add a new patient record to the patient array
//11. (Copy your code from MS#2)

void addPatient(struct Patient patient[], int max)
{
    int i = 0;
    int emptyIndex = -1, isFull = 0, retIndex = 0;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != '\0')
        {
            isFull++;
        }
        if (patient[i].patientNumber == '\0' && emptyIndex == -1)
        {
            emptyIndex = i;
        }
    }
    if (isFull == max)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else if (isFull < max && emptyIndex >= 0)
    {
        retIndex = nextPatientNumber(patient, max);
        patient[emptyIndex].patientNumber = retIndex;
        inputPatient(&patient[emptyIndex]);
        printf("*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array
//12. (Copy your code from MS#2)

void editPatient(struct Patient patient[], int max)
{
    int retIndex = 0;
    int retNum = 0;

    printf("Enter the patient number: ");
    scanf("%d", &retNum);

    retIndex = findPatientIndexByPatientNum(retNum, patient, max);

    if (retIndex != -1)
    {
        putchar('\n');
        menuPatientEdit(&patient[retIndex]);
    }
    else if (retIndex == -1)
    {
        putchar('\n');
        printf("ERROR: Patient record not found!\n");
    }
    //clearInputBuffer();
}

// Remove a patient record from the patient array
//13. (Copy your code from MS#2)

void removePatient(struct Patient patient[], int max)
{
    int retIndex = 0, retNum = 0;
    char yesOrNo = '?';


    printf("Enter the patient number: ");
    scanf("%d", &retNum);
    putchar('\n');

    retIndex = findPatientIndexByPatientNum(retNum, patient, max);

    if (retIndex > max || retIndex < 0)
    {
        printf("ERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }
    else
    {
        displayPatientData(&patient[retIndex], FMT_FORM);
        clearInputBuffer();
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        yesOrNo = inputCharOption("yn");
        if (yesOrNo == 'y')
        {
            patient[retIndex].patientNumber = 0;
            printf("Patient record has been removed!\n\n");
        }
        else if (yesOrNo == 'n')
        {
            printf("Operation aborted.\n\n");
        }
    }
    
 
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//14. View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data)
{
    int isAllRecords = 1, includeDateField = 1, counter = 0;

    numOfAppointments(data, &counter);
    
    displayScheduleTableHeader(&data->appointments->date, isAllRecords);

    sortDats(data, counter);

    matchAllPatients(data, counter, includeDateField);

    putchar('\n');

}

//15. View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data)
{
    
    int i, year, month, day, isAllRecords = 0, includeDateField = 0, counter = 0, temp = 0;

    numOfAppointments(data, &counter);

    printf("Year        : ");
    scanf("%d", &year);

    printf("Month (1-12): ");
    month = inputIntRange(1, 12);

    day = checkDaysRange(year, month);
    printf("\n");
   

    for (i = 0; i < counter ; i++)
    {
        if (year == data->appointments[i].date.year && month == data->appointments[i].date.month && day == data->appointments[i].date.day)
        {
            temp = i; 
        }
    }

    displayScheduleTableHeader(&data->appointments[temp].date, isAllRecords);
    
    matchPatientByDate(data, counter, includeDateField, year, month, day);
    
    putchar('\n');
    clearInputBuffer();

}

//16. Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient)
{
    int i = 0, counter, patientFound = 1, appointmentNotAvailabe = 0, timeNotCorrect = 0;
    struct Appointment temp =  {0} ;

    countAppointments(appointments, maxAppointments, &counter);

    if (counter < maxAppointments)
    {
        printf("Patient Number: ");
        scanf("%d", &temp.patientNumber);

        patientFound = findPatientIndexByPatientNum(temp.patientNumber, patients, maxPatient);

        if (patientFound == -1)   
        {
                printf("ERROR: We are fully booked, try some other time \n\n");
                clearInputBuffer();
        }
        else
        {
            do 
            {
                printf("Year        : ");
                scanf("%d", &temp.date.year);

                printf("Month (1-12): ");
                scanf("%d", &temp.date.month);

                temp.date.day = checkDaysRange(temp.date.year, temp.date.month);

                do
                {
                    printf("Hour (0-23)  : ");
                    scanf("%d", &temp.time.hour);
                    printf("Minute (0-59): ");
                    scanf("%d", &temp.time.min);

                    timeNotCorrect = 0;
                    
                    if ((temp.time.hour > CLOSE_TIME || temp.time.hour < OPEN_TIME) || (temp.time.min == MINUTE_INTERVAL && temp.time.hour == CLOSE_TIME) ||
                      (temp.time.min != MINUTE_INTERVAL && temp.time.min != MINUTE_VAL))
                    {
                        printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", OPEN_TIME, CLOSE_TIME, MINUTE_INTERVAL);
                        timeNotCorrect = 1;
                    }
                    else {
                        timeNotCorrect = 0;
                    }

                } while (timeNotCorrect);

                appointmentNotAvailabe = 0;

                for (i = 0; i < counter; i++)
                {

                    if (temp.date.year == appointments[i].date.year &&
                        temp.date.month == appointments[i].date.month &&
                        temp.date.day == appointments[i].date.day &&
                        temp.time.hour == appointments[i].time.hour &&
                        temp.time.min == appointments[i].time.min)
                    {
                        printf("\nERROR: Appointment timeslot is not available!\n\n");
                        appointmentNotAvailabe = 1;
                    }
                }
            } while (appointmentNotAvailabe);

            if (!appointmentNotAvailabe)
            {              
                appointments[counter] = temp;
                printf("\n*** Appointment scheduled! ***\n\n");
            }
        }
    }
    else
    {
        printf("*** Appointment scheduled is full! ***\n\n");
    }
    clearInputBuffer();   
}

//17. Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient)
{
    int i = 0, j = 0, counter = 0, patientNotFound = 1, removeIndex = 0, currentPatientsLength = 0;
    char yesOrNo = '?';
    struct Appointment temp = { 0 };

    countAppointments(appointments, maxAppointments, &counter);
    currentPatientsLength = countPatients(patients, maxPatient, &currentPatientsLength);
    

    printf("Patient Number: ");
    scanf("%d", &temp.patientNumber);

    // TODO:
    for (i = 0; i < currentPatientsLength; i++)
    {
        if (temp.patientNumber == patients[i].patientNumber)
        {
            patientNotFound = 0;

        }
    }

    if (patientNotFound != 0)
    {
        
        printf("ERROR: Patient record not found!\n\n");
        clearInputBuffer();
        return;
    }
    else
    {
        printf("Year        : ");
        scanf("%d", &temp.date.year);

        printf("Month (1-12): ");
        scanf("%d", &temp.date.month);

        temp.date.day = checkDaysRange(temp.date.year, temp.date.month);

        for (i = 0; i < counter; i++)
        {
            if ((temp.patientNumber == appointments[i].patientNumber) &&
                (temp.date.year == appointments[i].date.year) &&
                (temp.date.month == appointments[i].date.month) &&
                (temp.date.day == appointments[i].date.day))
            {
               
                for (j = 0; j < currentPatientsLength; j++)
                {
                    if (appointments[i].patientNumber == patients[j].patientNumber)
                    {
                        printf("\nName  : %s\n", patients[j].name);
                        printf("Number: 0%d\n", patients[j].patientNumber);
                        printf("Phone : ");
                        displayFormattedPhone(patients[j].phone.number);
                        printf(" (%s)\n", patients[j].phone.description);

                        removeIndex = i;
                    }

                }
            }
        }          
    }

    printf("Are you sure you want to remove this appointment (y,n): ");
    clearInputBuffer();
    yesOrNo = inputCharOption("yn");

    if (yesOrNo == 'y' || yesOrNo == 'Y')
    {
        appointments[removeIndex].date.day = 0;
        appointments[removeIndex].date.month = 0;
        appointments[removeIndex].date.year = 0;
        appointments[removeIndex].patientNumber = 0;
        appointments[removeIndex].time.hour = 0;
        appointments[removeIndex].time.min = 0;

        printf("\nAppointment record has been removed!\n\n");

    }
    else if (yesOrNo == 'n')
    {
        printf("\nOperation aborted.\n\n");
    }
    //clearInputBuffer();
}
        


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

//18. Search and display patient record by patient number (form)
// (Copy your code from MS#2)

void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int retIndex = -1, patientNum = 0;


    printf("Search by patient number: ");
    scanf("%d", &patientNum);

    retIndex = findPatientIndexByPatientNum(patientNum, patient, max);

    if (retIndex != -1)
    {
        putchar('\n');
        displayPatientData(&patient[retIndex], FMT_FORM);
        putchar('\n');
    }
    else if (retIndex == -1)
    {
        printf("\n*** No records found ***\n\n");
    }
    clearInputBuffer();
    suspend();
}
//19. Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)

void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i = 0, j = 0;
    char retNum[255] = { '\0' };
    int match[255] = { '\0' };

    printf("Search by phone number: ");
    scanf("%s", retNum);

    for (i = 0; i < max; i++)
    {
        match[i] = strcmp(retNum, patient[i].phone.number);
    }
    putchar('\n');
    displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {
        if (match[i] == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
        }
        else
        {
            j++;
        }
    }
    putchar('\n');
    if (j == max)
    {
        printf("*** No records found ***\n\n");
    }
    clearInputBuffer();
    suspend();
}
//20. Get the next highest patient number
// (Copy your code from MS#2)

int nextPatientNumber(const struct Patient patient[], int max)
{
    int i = 0;
    int largest = 0;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > largest)
        {
            largest = patient[i].patientNumber;
        }
    }

    largest++;

    return largest;
}
//21. Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)

int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int i = 0, match = -1;

    for (i = 0; i < max; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            match = i;
        }
    }
    return match;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//22. Get user input for a new patient record
// (Copy your code from MS#2)

void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 2, NAME_LEN,1);

    putchar('\n');

    inputPhoneData(&patient->phone);
}

//23. Get user input for phone contact information
// (Copy your code from MS#2)

void inputPhoneData(struct Phone* phone)
{
    int selection;

    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(0, 4);
    putchar('\n');
    switch (selection)
    {
    case 1:
        strcpy(phone->description, "CELL");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN,0);
        putchar('\n');
        break;
    case 2:
        strcpy(phone->description, "HOME");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN, 0);
        putchar('\n');
        break;
    case 3:
        strcpy(phone->description, "WORK");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN,0);
        putchar('\n');
        break;
    case 4:
        strcpy(phone->description, "TBD");
        strcpy(phone->number, " ");
        break;
    }
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

//24. Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    const char* DATA_IN = "%d|%[^|]|%[^|]|%[^\n]";
    int counter = 0;
    FILE* infile;
    infile = fopen(datafile, "r");
    
    if (infile == NULL)
    {
        printf("Error reading the file");
        return 1;
    }
    
    while ((counter < max) && (fscanf(infile, DATA_IN, &patients[counter].patientNumber, patients[counter].name, patients[counter].phone.description, patients[counter].phone.number) !=  EOF))
        {      
            counter++;  
        }

    fclose(infile);

    return counter;
}

//25. Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:

int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    
    const char* DATA_IN = "%d,%d,%d,%d,%d,%d\n";
    int counter = 0;
    FILE* infile;
    infile = fopen(datafile, "r");
 

    if (datafile == NULL)
    {
        printf("Error reading the file");
        return 1;
    }
 
    while ( (counter < max) && (fscanf(infile, DATA_IN, &appoints[counter].patientNumber, &appoints[counter].date.year, &appoints[counter].date.month, &appoints[counter].date.day, &appoints[counter].time.hour, &appoints[counter].time.min) != EOF) )
    {
        counter++;
    }

    fclose(infile);

    return counter;
}

//26.  Bubble sort dates
////////////////////////////////

void sortDats(struct ClinicData* data, int counter)
{
    int i, j;
    // temp value
    struct Appointment b = { 0 };

    for ( i = 0; i < counter; i++)
    {
        for ( j = 0; j <= i; j++)
        {
            if (data->appointments[j].date.year > data->appointments[i].date.year)
            {
                b = data->appointments[j];

                data->appointments[j] = data->appointments[i];

                data->appointments[i] = b;
            }

            else
            {
                if (data->appointments[j].date.year == data->appointments[i].date.year)
                {
                    if (data->appointments[j].date.month > data->appointments[i].date.month)
                    {
                        b = data->appointments[j];

                        data->appointments[j] = data->appointments[i];

                        data->appointments[i] = b;
                       
                    }
                    else
                    {
                        if (data->appointments[j].date.month == data->appointments[i].date.month)
                        {
                            if (data->appointments[j].date.day > data->appointments[i].date.day)
                            {
                                b = data->appointments[j];

                                data->appointments[j] = data->appointments[i];

                                data->appointments[i] = b;
                                                           
                            }
                            else
                            {
                                if (data->appointments[j].date.day == data->appointments[i].date.day)
                                {
                                    if (data->appointments[j].time.hour
                                        > data->appointments[i].time.hour)
                                    {
                                        b = data->appointments[j];

                                        data->appointments[j] = data->appointments[i];

                                        data->appointments[i] = b;
                                    }
                                    else
                                    {
                                        if (data->appointments[j].time.hour
                                        == data->appointments[i].time.hour)
                                        {
                                            if (data->appointments[j].time.min
                                        > data->appointments[i].time.min)
                                            {
                                                b = data->appointments[j];

                                                data->appointments[j] = data->appointments[i];

                                                data->appointments[i] = b;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }                                                          
        }
    }
}

//27.  match patients to new sorted date

void matchAllPatients(struct ClinicData* data,int counter, int field)
{
    int i, j, currentPatientsLength = 0;

    currentPatientsLength = countPatients(data->patients, data->maxPatient, &currentPatientsLength);

    for (i = 0; i < counter; i++)
    {
        // another example
        //struct Patient* foundPatient = NULL;
        //foundPatient = findPatient(data->appointments[i].patientNumber, data->patients, );
        //displayScheduleData(foundPatient, &data->appointments[i], field);
    
        for (j = 0; j < currentPatientsLength; j++)
        {
            if (data->appointments[i].patientNumber == data->patients[j].patientNumber)
            {
                displayScheduleData(&data->patients[j], &data->appointments[i], field);
            }
        }
    }
}

//28.match all patients by date 

void matchPatientByDate(struct ClinicData* data, int counter, int field, int year, int month, int day)
{
    int i, j, currentPatientsLength = 0;

    currentPatientsLength = countPatients(data->patients, data->maxPatient, &currentPatientsLength);

    for (i = 0; i < counter; i++)
    {
        if ((data->appointments[i].date.year == year) && (data->appointments[i].date.month == month) && (data->appointments[i].date.day == day))
        {
            for (j = 0; j < currentPatientsLength; j++)
            {
                if (data->appointments[i].patientNumber == data->patients[j].patientNumber)
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], field);

                }
            }
        }
    }
}


//29. check leap year and max days of a month

int checkDaysRange(int year, int month)
{
    int day = 0, dayCorrect = 0, maxDay = 0;
    maxDay = getMaxDay(year, month);
    do
    {
        dayCorrect = 0;
        if (day == 0) {
            printf("Day (1-%d)  : ", maxDay);
        }
        scanf("%d", &day);

        if (day < 1 || day > maxDay) {
            printf("ERROR! Value must be between 1 and %d inclusive: ", maxDay);
            dayCorrect = 1;
        }
    } while (dayCorrect);

    return day;
}

int getMaxDay(int year, int month) {
    int maxDay = 0;
    if (month == 2)
    {
        if (((year % 4 == 0) && ((year % 400 == 0) || (year % 100 != 0))))
        {
            maxDay = 29;
        }
        else
        {
            maxDay = 28;
        }
    }
    else
    {
        if (((month <= 7 && month % 2 != 0) && (month != 2)) ||
            ((month >= 8 && month % 2 == 0) && (month != 2)))
        {
            maxDay = 31;
        }
        else if (((month <= 7 && month % 2 == 0) && (month != 2)) ||
            ((month >= 8 && month % 2 != 0) && (month != 2)))
        {
            maxDay = 30;
        }
    }
    return maxDay;
}

//
//30. counter, check the number of appointments

int numOfAppointments(struct ClinicData* data,int* counter)
{
    countAppointments(data->appointments, data->maxAppointments, counter);

    return 0;
}

int countAppointments(struct Appointment* appointments, int maxAppointments, int* counter)
{
    int i = 0, retNum = 0;

    for (i = 0; i < maxAppointments; i++)
    {
        if (appointments[i].date.day != 0)
        {
            retNum = i + 1;
        }
    }

    *counter = retNum;

    return retNum;
}

int countPatients(struct Patient* patients, int maxPatients, int* counter)
{
    int i = 0, retNum = 0;

    for (i = 0; i < maxPatients; i++)
    {
        if (patients[i].patientNumber != 0)
        {
            retNum = i + 1;
        }
    }

    *counter = retNum;

    return retNum;
}
    /*
struct Patient* findPatient(int patientNumber, struct Patient* patientArr, int lenght)
{
    int i = 0, k = 0;
    for (int i = 0; i < lenght; i++) {
        if (patientArr[i].patientNumber == patientNumber)
        {
            k = i;
            //return &(patientArr[k]);
        }
    }
    return &(patientArr[k]);
    
}
*/
