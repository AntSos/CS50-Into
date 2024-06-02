#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>


// Main Function
int main (int argc, string argv [])
{
    if (argc != 2)
    {
        printf ("We need a key: ./caesar key\n");
        return 1;
    }

    for (int i = 0; i < strlen (argv [1]); i++)
    {
        if (!isdigit (argv [1][i]))
        {
            printf ("We need a key: ./caesar key\n");
            return 1;
        }
    }


    int key = atoi (argv [1]);
    string message = get_string ("Write your message: ");
    printf ("Ciphertext: ");

    for (int j = 0; j < strlen (message); j++)
    {
        if (isupper (message [j]))
        {
            printf ("%c", (((message [j] - 65) + key) % 26) + 65);
        }

        else if (islower (message [j]))
        {
            printf ("%c", (((message [j] - 97) + key) % 26) + 97);
        }

        else
        {
            printf ("%c", message [j]);
        }

    }
    printf ("\n");
}
