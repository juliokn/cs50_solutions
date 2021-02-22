//implement a program that computes the approximate grade level needed to comprehend some text

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int cntlet(string counter);  //function to count letters
int cntwords(string counter);  //function to count words
int cntsent(string counter);  //function to count sentences
int main(void)
{
    string text = get_string("Text: "); //text input
    
    float letters = cntlet(text);  //call to function (counting letters)
    
    float words = cntwords(text);  //call to function (counting words)
    
    float sentences = cntsent(text);  //call to function (counting sentences)
    
    printf("Number of letters: %.0f\n", letters);
    printf("Number of words: %.0f\n", words);
    printf("Number of sentences: %.0f\n", sentences);
    
    float averlet = ((letters / words) * 100);
    float aversen = ((sentences / words) * 100);
    float index = 0.0588 * averlet - 0.296 * aversen - 15.8;
    
    if (round(index) <= 0)
    {
        printf("Before Grade 1\n");
    }
    else if (round(index) > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }
    
    //coleman-liau index: 0.0588 * (letters per 100 words) - 0.296 * (average number of sentences per 100 words) - 15.8

}

int cntlet(string counter)  //function to count letters
{
    int k = strlen(counter);
    int j = strlen(counter);
    for (int i = 0; i <= j ; i++)
    {
        if (counter[i] >= 33 && counter[i] <= 64)
        {
            k--;
        }
        if (counter[i] >= 91 && counter[i] <= 96)
        {
            k--;
        } 
        if (counter[i] >= 123 && counter[i] <= 126)
        {
            k--;
        } 
        if (counter[i] == ' ')
        {
            k--;
        } 
    }
    return k;
        
}
    
int cntwords(string counter)  //function to count words
{
    int x = strlen(counter);
    int space = 1;
    for (int i = 0; i <= x ; i++)
    {
        if (counter[i] == ' ')
        {
            space++;
        }
    }
    return space;
}

int cntsent(string counter)  //function to count sentences
{
    int y = strlen(counter);
    int dots = 0;
    for (int i = 0; i <= y ; i++)
    {
        if ((counter[i] == '.') || (counter[i] == '?') || (counter[i] == '!'))
        {
            dots++;
        }
    }
    return dots;
}