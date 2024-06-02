#include <stdio.h>
#include <cs50.h>


void print_p (int length);

int main (void)
{
    int height;
    // User introduce a postive integer
    do
    {
        height = get_int ("Enter the size of the pyramid: ");
    }
    while (height  < 1 || height  > 8);

    // Call the fuction print_p
    print_p (height);

}

//Fuction that prints # for a given number and blank space
void print_p (int length)
{
    for (int i = 0; i < length; i ++)
    {

        for (int j = 0; j < length; j ++)
        {
            if (i + j < length - 1)
            {
                printf (" ");
            }
            else
            {
                printf ("#");
            }
        }
        printf ("\n");
    }
}
