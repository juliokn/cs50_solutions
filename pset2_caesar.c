//implement a program that encrypts messagens using Caesar's cipher
//you start it by typing "./caesar [key]" on terminal, [key] being a int number

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)       //the user have to type "./caesar [just this one something]", or it doesnt work
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    string check = argv[1]; //transport argv[1] to a string named "check" so we can check if each char of "check" is a number
    
    int test = strlen(check); //gets length of key (still as a string, now as "check")

    for (int j = 0; j < test ; j++) //goes through every char in "check"; j cant be equal to test (the length) because then it would print the terminating null byte (the "\0" that ends a string)
    {
        if (isdigit(check[j]) == 0) //if char is not a digit, the program ends here
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    
    int key = atoi(argv[1]);  //atoi = function that converts a string to a int, from stdlib library; argc (the key) -> argv[1]
            
    string word = get_string("plaintext: ");                     //gets plaintext
            
    int length = strlen(word);                       //gets length of plaintext
            
    printf("ciphertext: ");
        
    for (int i = 0; i < length; i++) //i cant be equal to length because then it would print the terminating null byte (the "\0" that ends a string)
    {
        if ((word[i] >= 97 && word[i] <= 122)) //small letters
        {
            printf("%c", (((word[i] - 97 + key) % 26) + 97)); //tirar a dif entre a letra e o 'a' na tabela ascii, saber onde ele tá no alfabeto, e depois botar de novo na tabela ascii
        }
        else if ((word[i] >= 65 && word[i] <= 90)) //capital letters
        {
            printf("%c", (((word[i] - 65 + key) % 26) + 65)); //tirar a dif entre a letra e o 'A' na tabela ascii, saber onde ele tá no alfabeto, e depois bota de novo na tabela ascii
        }
        else
        {
            printf("%c", word[i]);
        }
    }
    printf("\n");
    return 0;
    
}
