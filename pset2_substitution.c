//implement a program that implements a substitution

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)       //chek if the the user typed a key
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1]; //gets key to check length

    int keylength = strlen(key); //gets length of key

    if ((keylength < 26) || (keylength > 26))        //key must contain 26 characters, no more, no less
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < keylength; i++)
    {
        if (isalpha(key[i]) == 0) //returns zero if characters is not alphabetical
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    for (int k = 0; k < keylength; k++)
    {
        for (int y = k + 1; y < keylength; y++)
        {
            if (key[k] == key[y]) //checks if key repeats itself
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }

    string word = get_string("plaintext: ");        //gets plaintext

    int wordlength = strlen(word); //gets length of plaintext

    printf("ciphertext: ");

    for (int j = 0; j < wordlength; j++)
    {
        if (isupper(word[j]) != 0) //check if char is uppercase
        {
            if (isalpha(word[j]) != 0) //if it is alphabetical, then cripto
            {
                int posupper = word[j] - 65; //posição do word[i] no alfabeto = pos
                char criptoup = key[posupper]; //cripto é a letra correspondente a posição pos na key
                printf("%c", toupper(criptoup)); //como word[i] é maiúscula, imprime a correspondente da key maiúscula
            }
            else
            {
                printf("%c", word[j]);
            }
        }
        if (isupper(word[j]) == 0) //check if char is lowercase
        {
            if (isalpha(word[j]) != 0) //if it is alphabetical, then cripto
            {
                int poslower = word[j] - 97; //posição do word[i] no alfabeto = pos
                char criptolow = key[poslower]; //cripto é a letra correspondente a posição pos na key
                printf("%c", tolower(criptolow)); //como word[i] é maiúscula, imprime a correspondente da key maiúscula
            }
            else
            {
                printf("%c", word[j]);
            }
        }
    }
    printf("\n");
    return 0;
}



