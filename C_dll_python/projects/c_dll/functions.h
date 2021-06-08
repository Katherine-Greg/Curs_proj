#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define DllExport __declspec(dllexport)

struct tasks
{
    char *question;
    int type;
    int difficult;
    int mark;
}tickets[300]; 

// Set the maximum buffer size for working with the file
#define BSIZE 10000

DllExport int  valid_int(void);
DllExport int total_amount_of_questions(void);
DllExport int check_and_find_amount(int users_amount, int total_amount);
DllExport int file(int tickets_amount, int amount_of_quest_in_one);
DllExport int creating_file(int rows, int tickets_amount, int amount_of_quest_in_one);
DllExport int total_results(int *mark, int rows, int tickets_amount, int ind);

#endif
