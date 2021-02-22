#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long credit = get_long("What's the number?\n"); //getting card number

    //LENGHT

    int lenght = 0; //int credit card lenght
    long clenght = credit; //para calcular o lenght

    while (clenght > 0)                              //CHECKING LENGHT
    {
        clenght = clenght / 10; //checa dígito por dígito (e se existe, soma+1 em lenght)
        lenght++; 
    }
    if (lenght != 13 && lenght != 15 && lenght != 16) //ONLY 13, 15 OR 16 DIGITS
    {
        printf("INVALID\n");
        return 0;                                   //LENGHT INVALID
    }

    //CHECKSUM

    long check1 = credit; //para calcular o checksum1
    long check2 = credit; //para calcular o checksum2
    int sum1 = 0; //first sum
    int sum2 = 0; //second sum
    int k; //variaveis k, a, b para calculos
    int a;
    int b;

    while (check1 > 0)                              //CHECKSUM 1ST SUM
    {
        k = (check1 / 10) % 10;
        if (k * 2 >= 10) //checa se o k*2 é igual ou maior que 10, para quebrar o numero em digitos
        {
            a = (k * 2) % 10;
            b = ((k * 2) / 10) % 10;
            sum1 = sum1 + a + b;
            k = 0;
            a = 0;
            b = 0;
            check1 = check1 / 100; //pula de dois em dois
        }
        else
        {
            sum1 = sum1 + (k * 2);
            k = 0;
            check1 = check1 / 100; //pula de dois em dois
    }

    while (check2 > 0)                              //CHECKSUM 2ND SUM
    {
        k = check2 % 10;
        sum2 = sum2 + k;
        k = 0;
        check2 = check2 / 100;
    }
    }
   
    if ((sum1 + sum2) % 10 != 0)                      //CHECKSUM FINAL SUM    
    {
        printf("INVALID\n");
        return 0;
    }

    long start = credit; //para calcular os primeiros numeros 
    
    while (start > 100)
    {
        start = start / 10;
    }

    if ((start / 10 == 3) && (start % 10 == 4 || start % 10 == 7))                          //CHECK CARD FLAG
    {
        printf("AMEX\n");
    }
    else if ((start / 10 == 5) && (start % 10 == 1 || start % 10 == 2 || start % 10 == 3 || start % 10 == 4 || start % 10 == 5))
    {
        printf("MASTERCARD\n");
    }
    else if (start / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

   

