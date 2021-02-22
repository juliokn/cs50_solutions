#include <stdio.h>
#include <cs50.h>
#include <math.h>

float get_positive_float(void);
int main(void)

{
    float change = get_positive_float(); //pega um float obrigatoriamente positivo

    int n;
    int total;
    int count = 0;

    total = round(change * 100); //transforma o float em integer pra possibilitar calculos, e arredonda usando round 
     
    while (total >= 25)  
    {
        total -= 25;
        count++;  //a cada loop soma um no count
    }

    while (total >= 10)
    {
        total -= 10;
        count++;
    }
    while (total >= 5)
    {
        total -= 5;
        count++;
    }
    while (total >= 1)
    {
        total -= 1;
        count++;
    }
    printf("%i\n", count); //imprime o total
}




float get_positive_float(void) // function pra pegar um float obrigatoriamente positivo
{
    float n; 
    do 
    {
        n = get_float("How much change is owed? \n");
    }
    while (n < 0);
    return (n);
}