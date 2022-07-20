#include <stdio.h>  /* printf */
#include <unistd.h> /* sleep */
#include <stdlib.h> /* system */
#include <time.h>   /* clock */

#include "knights_tour.h"

#define X_POS 0
#define Y_POS 0

void TestAllFuncs();
void PrintArr(char *, int);
int TestWarnsdorff(unsigned char *);
void TestKnightTour(unsigned char *);
void PrettyPrinting(unsigned char *);

int main()
{
    TestAllFuncs();
    return (0);
}

void TestAllFuncs()
{
    int print_opt = 0;
    int status = 0;
    unsigned char path[70] = {0};
    unsigned char wpath[70] = {0};
    clock_t start = 0;
    clock_t between = 0;
    clock_t end = 0;
    system("clear");
    printf("~ START OF KNIGHTS TOUR TEST ~\n");
    printf("Checking if position [%d, %d] has a Knights Tour solution..\n", X_POS, Y_POS);
    start = clock();
    status = TestWarnsdorff(wpath);
    between = clock();
    TestKnightTour(path);
    end = clock();
    switch (status)
    {
    case TRUE:
        printf("Position [%d, %d] has a Knights Tour solution!\n", X_POS, Y_POS);
        printf(">>> Brute force runtime: %ldms\n", (end - between) / (CLOCKS_PER_SEC / 1000));
        printf(">>> Warnsdorff runtime:  %ldms\n", (between - start) / (CLOCKS_PER_SEC / 1000));
        printf("Which solution would you like to see?\n[1] Brute force\n[2] Warnsdorff\n[3] None\n");
        scanf("%d", &print_opt);
        switch (print_opt)
        {
        case (1):
            PrettyPrinting(path);
            break;
        case (2):
            PrettyPrinting(wpath);
            break;
        }
        break;
    case FALSE:
        printf("Position [%d, %d] doesnt have a Knights Tour solution!\n", X_POS, Y_POS);
        break;
    case TIMEOUT:
        printf("Position [%d, %d] Timed out!\n", X_POS, Y_POS);
        break;
    }
    printf("~ END OF KNIGHTS TOUR TEST ~\n");
}

int TestWarnsdorff(unsigned char *path)
{
    return (WarnsdorffKnightsTour(X_POS, Y_POS, path));
}

void TestKnightTour(unsigned char *path)
{
    KnightsTour(X_POS, Y_POS, path);
}

void PrettyPrinting(unsigned char *path)
{
    int i = 0;
    char print_buffer[70] = {0};
    printf("Printing Knights Tour..\n");
    for (; i < 64; i++)
    {
        print_buffer[path[i]] = (i + 1);
        sleep(1);
        system("clear");
        printf("       ~ step [%d] ~\n\n", (i + 1));
        PrintArr(print_buffer, (i + 1));
    }
}

void PrintArr(char *arr, int step)
{
    int i = 0;
    for (; i < 64; ++i)
    {
        for (i = 0; i < 64; i++)
        {
            if (arr[i] == 0)
            {
                printf("%3d", arr[i]);
            }
            else if (step == arr[i])
            {
                printf("\033[1;32m");
                printf("%3d", arr[i]);
                printf("\033[0m");
            }
            else
            {
                printf("\033[1;34m");
                printf("%3d", arr[i]);
                printf("\033[0m");
            }
            if ((i + 1) % 8 == 0)
            {
                printf("\n\n");
            }
        }
        printf("\n");
    }
}