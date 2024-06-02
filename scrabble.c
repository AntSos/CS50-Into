#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


//Functions prototype
int check_word (string word);

// Main Function
int main (void)
{
    //Input from bouth players
    string word_p1 = get_string ("Player 1: ");
    string word_p2 = get_string ("Player 2: ");

    int score_01 = check_word (word_p1);
    int score_02 = check_word (word_p2);

   if (score_01 == score_02)
   {
        printf ("Tie! Game\n");
   }

   else if (score_01 > score_02)
   {
        printf ("Player 1 Wins!\n");
   }

   else
   {
        printf ("Player 2 Wins!\n");
   }

}

// A function that recevies a string and check it´s score
int check_word (string word)
{   //Points for each letter
    int points[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int score = 0;
    int length = strlen (word);

    //Looping trhougth the word
    for (int i = 0; i < length; i ++)
    {
        if (islower (word [i]))
        {
            score += points [word [i] - 'a'];
        }

        else if (isupper (word [i]))
        {
            score += points [word [i] - 'A'];
        }

    }
    return score;

}
