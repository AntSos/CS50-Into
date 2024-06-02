#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


//Prototype functions
int c_letters (string text);
int c_words (string text);
int c_sentences (string text);

// Main Function
int main (void)
{
    // Input from the user
    string text = get_string ("Text: ");

    int letters = c_letters (text);
    int words = c_words (text);
    int sentences = c_sentences (text);

// Calculate with Coleman-Liau formula

    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;

    int index = round (0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf ("Before Grade 1\n");
    }

    else if (index > 16)
    {
        printf ("Grade 16+\n");
    }

    else
    {
        printf ("Grade %i\n", index);
    }
}

int c_letters (string text)
{
    int letters = 0;
    int length = strlen (text);

    for (int i = 0; i < length; i ++)
    {
        if (isalpha(text [i]))
        {
            letters ++;
        }
    }
    return letters;
}


int c_words (string text)
{
    int words = 1;
    int length = strlen (text);

    for (int i = 0; i < length; i ++)
    {
        if (text[i] == ' ')
        {
            words ++;
        }
    }
    return words;

}

int c_sentences (string text)
{
    int sentences = 0;
    int length = strlen (text);

    for (int i = 0; i < length; i ++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences ++;
        }
    }
    return sentences;
}

