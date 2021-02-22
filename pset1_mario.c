//faz uma piramide (lado esquerdo e lado direito), com espaço no meio

#include <stdio.h>
#include <cs50.h>
#include <unistd.h>

int get_correct_int (void);
int main (void)

{
    int r;
    r = get_correct_int(); // r for rows
    int e = r-1; // e for empty (starts as r-1)
    int x = r-(r-1); // x por # (starts as 1)
    int d = r-(r-1); // same as x, for the right side (lado Direito)
    

    for (int i = 0; i < r; i++) //number r of
    {
        for (int j = 0; j < e; j++) // print a decreasing number of empty spaces starting as e=r-1 (left side)
        {
            printf(" ");
        }
    e--;
    for (int k = 0; k < x; k++) //print a increasing number of # starting as x=r-(r-1)=1 (left side)
            {
                printf ("#");
            }
    x++;
    printf("  ");
    for (int j = 0; j < d; j++) //print a increasing number of # starting as d=r-(r-1)=1 (right side)
        {
            printf("#");
        }
    d++;
    printf("\n");
    }
}

int get_correct_int(void) //to get a integer h between 1 and 8
{
    int n;
    do
    {
        n = get_int("Height: ");    
    }
    while (n < 1 || n > 8);
    return n;
    
}