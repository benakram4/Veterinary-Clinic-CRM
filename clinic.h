
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
#ifndef CLINIC_H
#define CLINIC_H


//////////////////////////////////////
// Module macro's (usable by any file that includes this header)
//////////////////////////////////////

// Display formatting options (Provided to student)
// !!! DO NOT MODIFY THESE MACRO'S !!!
#define FMT_FORM 1
#define FMT_TABLE 2

// C Strings: array sizes
#define NAME_LEN 15
#define PHONE_DESC_LEN 4
#define PHONE_LEN 10


// MS#3 Additional macro's:
// ToDo:

#define OPEN_TIME 10
#define CLOSE_TIME 14
#define MINUTE_INTERVAL 30 
#define MINUTE_VAL 0


//////////////////////////////////////
// Structures
//////////////////////////////////////

// Data type: Phone
// (Copy your code from MS#2)

struct Phone
{
    char description[PHONE_DESC_LEN + 1];
    char number[PHONE_LEN + 1];

};

// Data type: Patient 
// (Copy your code from MS#2)

struct Patient
{
    int patientNumber;
    char name[NAME_LEN + 1];
    struct Phone phone;
};

// ------------------- MS#3 -------------------

// Data type: Time
// ToDo:
struct Time
{
    int hour;
    int min;
};

// Data type: Date
// ToDo:
struct Date
{
    int year;
    int month;
    int day;

};

// Data type: Appointment
// ToDo:
struct Appointment
{
    int patientNumber;
    struct Time time;
    struct Date date;
    
    
};


// ClinicData type: Provided to student
// !!! DO NOT MODIFY THIS DATA TYPE !!!
struct ClinicData
{
    struct Patient* patients;
    int maxPatient;
    struct Appointment* appointments;
    int maxAppointments;
};


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

//1. Display's the patient table header (table format)
void displayPatientTableHeader(void);

//2. Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt);

//3. Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords);

//4. Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField);


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

//5. Menu: Main
void menuMain(struct ClinicData* data);

//6. Menu: Patient Management
void menuPatient(struct Patient patient[], int max);

//7. Menu: Patient edit
void menuPatientEdit(struct Patient* patient);

//8. Menu: Appointment Management
void menuAppointment(struct ClinicData* data);

//9. Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt);

//10. Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max);

//11. Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max);

//12. Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max);

//13. Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max);


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//14. View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data);

//15. View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data);

//16. Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient);

//17. Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient);


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

//18. Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max);

//19. Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max);

//20. Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max);

//21. Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//22. Get user input for a new patient record
void inputPatient(struct Patient* patient);

//23. Get user input for phone contact information
void inputPhoneData(struct Phone* phone);




//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

//24. Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max);

//25. Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max);

//////////////////////////////////////
// Algorithms & Extra Functions
//////////////////////////////////////

//26. Bubble sort dates

void sortDats(struct ClinicData* data, int counter);

//27. match patients to new sorted date
void matchAllPatients(struct ClinicData* data,int counter ,int field);

//28. match all patients by date 

void matchPatientByDate(struct ClinicData* data, int counter, int field, int year, int month, int day);

//29. check leap year and max days of a month

int checkDaysRange(int year, int month);
int getMaxDay(int year, int month);

//30. counter, check the number of appointments

int numOfAppointments(struct ClinicData* data,int* counter);

int countAppointments(struct Appointment* appointments, int maxAppointments, int* counter);

//31. find patient
//struct Patient* findPatient(int patientNumber, struct Patient* patientArr, int counter);

int countPatients(struct Patient* patient, int maxPatients, int* lenght);

#endif // !CLINIC_H