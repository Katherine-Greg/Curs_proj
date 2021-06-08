#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>


// Сhecks the entered integers
int valid_int(void)
{
    while (1)
    {
        int i, j, flag, gl_flag = 1;
        char str[200], NONE[10] = "\0", numb[100] = "0123456789", minus = '-';

        gets(str);

        if (!(strcmp(str, NONE)))
        {
            continue;
        }
		
        i = 0;

        if (str[0] == minus)
        {
            i = 1;
        }

        for (i = 0; str[i] != '\0'; i++)
        {
            flag = 0;

            for (j = 0; j < 10; j++)
            {

                if (str[i] == numb[j]) 
                {
                    flag = 1;
                }
            }

            if (flag == 0)
            {
                gl_flag = 0;
            }
        }

        if (gl_flag == 0)
        {
            printf("Invalid input. Input integer.\n");

            continue;
        }

        return atoi(str);
    }
}


// Sorts arrays with index memorization
// arr - an array for sorting, num - an array of indexes of corresponding elements
void sort(int *arr, int *num, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = (size - 1); j > i; j--)
        {
            if (arr[j - 1] > arr[j])
            {
                int a = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = a;

                int b = num[j - 1];
                num[j - 1] = num[j];
                num[j] = b;
            }
        }
    }
}


// Finds the maximum total score for each ticket
float max_grade(int *marks, int size, int tickets_amount)
{
    int sum = 0;
    float grade = 0;

    for (int i = 0; i < size; i++)
    {
        sum += marks[i];
    }  

    grade = sum / tickets_amount;

    return grade;
}


// Finds the maximum error for each ticket
// Max error is 20%
float max_error(float max_grade)
{
    return (0.2 * max_grade);
}


// Finds the number of all questions 
int total_amount_of_questions()
{
    
    char buffer[BSIZE];

    FILE *f;
    int total = 0; 
        
    f = fopen("questions.csv", "r");


    if (f == NULL)
    {
        return -1;
    }
    else 
    {
        while (fgets(buffer, BSIZE, f))
        {
            total++;
        }
    
        fclose(f);

        // Сross out the first line that contains the column names 
        total -= 1;

        return total;
    }
}


// Checks and finds the number of questions in one ticket
int check_and_find_amount(int users_amount, int total_amount)
{
    if (users_amount > 1)
    {

        if (total_amount > users_amount || total_amount % users_amount ==  0)
        {
            
            float a = total_amount / users_amount;

            return (int) a;

        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}


// Generates an array with question indexes
int random(int arr_size, int *parr, int range_min, int range_max) 
{
    int dup_flag;
    int rand_val, range_width = range_max - range_min + 1;
    
    
    if (range_width < 1 || arr_size < 0 || arr_size > range_width) 
    {
        return -2;
    }

    for (int i = 0; i < arr_size; i++) 
    {
        for (int i = 0; i >= 0; i++) 
        {
            rand_val = range_min + rand() % range_width;
            dup_flag = 0;
            for (int j = 0; j < i; j++) 
            {

                if (rand_val == parr[j])
                {  
                    dup_flag = 1; 
                    break; 
                }
            }
            if (!dup_flag)
            {
                break;
            } 
        }
        parr[i] = rand_val;
    }
    return 1;
}


// Сhecks the generated array 
int check_random(int *cur, int max, int min, int tickets_amount, int amount_of_quest_in_one, int num_pr, int num_teor)
{
    int n = 0, k = 0, flag = 0;

    if (num_teor == num_pr && amount_of_quest_in_one > 1)
    {
        for (int i = 0; i < tickets_amount; i++)
        {
            int count_pr = 0, count_tr = 0;
            int mrk = 0;
            
            // Counts mark in one ticket for checking
            for (int j = 0; j < amount_of_quest_in_one; j++)
            {
                mrk += tickets[cur[n]].mark;
                n++;
            }

            // Counts number of theoretical and practical assignments in one ticket for checking
            for (int j = 0; j < amount_of_quest_in_one; j++)
            {
                if (tickets[cur[k]].type == 1)
                {
                    count_tr += tickets[cur[k]].type;
                }
                else
                {
                    count_pr += tickets[cur[k]].type;
                }
                k++;
            }

            if (count_pr == count_tr)
            {
                if (mrk <= max)
                {
                    if (mrk < min)   
                    {
                        flag++;
                    }
                }    
                else
                {
                    flag++;
                }
            }    
            else 
            {
                flag++;
            } 
        }
    }
    else
    {
        for (int i = 0; i < tickets_amount; i++)
        {
            int mrk = 0;
            
            // Counts mark in one ticket for checking
            for (int j = 0; j < amount_of_quest_in_one; j++)
            {
                mrk += tickets[cur[n]].mark;
                n++;
            }
        
            if (mrk <= max)
            {
                if (mrk < min)  
                {
                    flag++;
                }
            }    
            else   
            {
                flag++;
            }
        }
    }
    
    if (flag == 0)
    {
        return 1;
    }
    else 
    {
        return 0;
    }              
}


// Finds factorial of number
int factorial(int count)
{
    int fact = 1;

    for (int i = 1; i <= count; i++)
    {
        fact = fact * i;
    }

    return fact;
}


// Finds error, total maximum and minimun marks with error 
int total_results(int *mark, int rows, int tickets_amount, int ind)
{
    float max_res = max_grade(mark, rows, tickets_amount);

    float max_err = max_error(max_res);

    if (ind == 1)
    {
        float total_mark = max_err + max_res;

        return (int) total_mark;
    }
    else if (ind == 2)
    {
        float min_res = max_res - max_err;

        return (int) min_res;
    }
    else
    {
        return max_err;
    }
}


// Collects information into an array of structures and counts number of rows
int file(int tickets_amount, int amount_of_quest_in_one)
{
    char buffer[BSIZE];

    FILE *f;

    char *field;
    int rows;

    f = fopen("questions.csv", "r");

    if (f == NULL)
    {
        return -1;
    }
    else 
    {   
        // Сollects information from the file into a structure
        rows = 0;

        while (fgets(buffer, BSIZE, f))
        {
            field = strtok(buffer, ",");
            
            // Strdup make copie field in quest.
            tickets[rows].question = strdup(field);
        
            field = strtok(NULL, ",");
            
            tickets[rows].type = atoi(field);
            
            
            field = strtok(NULL, ",");
            tickets[rows].difficult = atoi(field);
            
            field = strtok(NULL, ",");
            tickets[rows].mark = atoi(field);

            rows++;
        }
        
        fclose(f);
        
        // Сross out the first line that contains the column names        
        rows--;

        return rows;
    }
}


// For general information
// Finds array with marks and their indexes
int *marks(int rows, int ind)
{   
    int *mark, *pmark;
    
    mark = (int *)malloc(rows * sizeof(int));
    pmark = (int *)malloc(rows * sizeof(int));
        
    int j = 0;

    for (int i = 1; i <= rows; i++)    
    {
        mark[j] = tickets[i].mark;
        pmark[j] = i;

        j = i;
    }
    
    sort(mark, pmark, rows);

    if (ind == 1)
    {
        return mark;
    }
    else
    {
        return pmark;
    }
}


// Finds array with difficulties of all questions and their indexes
int *diffic(int rows, int ind)
{
    int *diff, *pdiff;

    diff = (int *)malloc(rows * sizeof(int));
    pdiff = (int *)malloc(rows * sizeof(int));
    
    int j = 0;

    for (int i = 1; i <= rows; i++)    
    {
        diff[j] = tickets[i].difficult;
        pdiff[j] = i;

        j = i;
    }

    sort(diff, pdiff, rows);

    if (ind == 1)
    {
        return diff;
    }
    else
    {
        return pdiff;
    }
}


// Finds array with types of all questions and their indexes
int *types(int rows, int ind)
{
    int *type, *ptype;

    type = (int *)malloc(rows * sizeof(int));
    ptype = (int *)malloc(rows * sizeof(int));
    
    int j = 0;

    for (int i = 1; i <= rows; i++)    
    {
        type[j] = tickets[i].type;
        ptype[j] = i;

        j = i;
    }

    sort(type, ptype, rows);


    if (ind == 1)
    {
        return type;
    }
    else
    {
        return ptype;
    }
}


// Counts number of theoretical and practical assignments 
int num_pr_teor(int rows, int *type, int ind)
{
    int num_pr = 0, num_teor = 0;

    for (int j = 0; j < rows; j++)
    {
        if (type[j] == 1)
        {
            num_teor++;
        }
        else 
        {
            num_pr++;
        }
    }

    if (ind == 1)
    {
        return num_teor;
    }
    else
    {
        return num_pr;
    }
}


// Finds and checks an array of indexes of the final combinations of elements
int *check_quest(int total_mark, int min_res, int tickets_amount, int amount_of_quest_in_one, int num_pr, int num_teor)
{
    // Number of questions from the general that are used for tickets
    int size = (amount_of_quest_in_one * tickets_amount);
    
    int *cur;

    cur = (int *)malloc(size * sizeof(int));
    
    int check_result, k;

    srand(time(NULL));
             
    k = random(size, cur, 1, size);

    if (k == -2)
    {
        return 0;
    }

    check_result = check_random(cur, total_mark, min_res, tickets_amount, amount_of_quest_in_one, num_pr, num_teor);

    int fail = 0;

    while (check_result == 0) 
    {
        k = random(size, cur, 1, size);

        if (k == -2)
        {
            return 0;
        }

        check_result = check_random(cur, total_mark, min_res, tickets_amount, amount_of_quest_in_one,  num_pr, num_teor);
            
        fail++;

        if (num_pr == num_teor)
        {
            if (fail > factorial(factorial(size)))
            {
                return 00;
            }
        }
    }
    return cur;
}


// Creating tickets
int creating_file(int rows, int tickets_amount, int amount_of_quest_in_one)
{
    FILE *new_f;
    int total_mark = total_results(marks(rows, 1), rows, tickets_amount, 1);
    int min_res = total_results(marks(rows, 1), rows, tickets_amount, 2);
    int num_pr = num_pr_teor(rows, types(rows, 4), 2), num_teor = num_pr_teor(rows, types(rows, 4), 1);
    int counter = 1;
    int *cur;

    cur = (int *)malloc((tickets_amount * amount_of_quest_in_one) * sizeof(int));
    cur = check_quest(total_mark, min_res, tickets_amount, amount_of_quest_in_one, num_pr, num_teor);

    if (cur == 0)
    {
        return -1;
    }
    else if (cur == 00)
    {
        return -2;
    }

    printf("\n Min grade: %.d", min_res);
    printf("\n Max grade: %.d", total_mark);

    new_f = fopen("tickets.txt", "w");

    int n = 0;

    for (int i = 0; i < tickets_amount; i++)
    {
        fprintf(new_f, "            Variant: %d", counter);
        fprintf(new_f, "\n");

        int mrk = 0, dff = 0;
            
        // Ticket grade Calculation
        int k = n;
        for (int j = 0; j < amount_of_quest_in_one; j++)
        {
            mrk += tickets[cur[k]].mark;
            k++;
        }

        // Calculating the difficulty of the ticket
        k = n;            
        for (int j = 0; j < amount_of_quest_in_one; j++)
        {
            dff += tickets[cur[k]].difficult;
            k++;
        }

        fprintf(new_f, "        Mark: %d\n        Difficult: %d\n", mrk, dff);
            
        int num = 1;
        for (int j = 0; j < amount_of_quest_in_one; j++)
        {
            fprintf(new_f, "%d. %s", num, tickets[cur[n]].question);
            fprintf(new_f, "\n");
            n++;
            num++;
        }

        fprintf(new_f, "\n\n\n");
        counter++;       
    }
    fclose(new_f);

    return 1;
}
