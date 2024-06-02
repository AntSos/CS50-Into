#include <stdio.h>
#include <cs50.h>

// Define finctions
int c_quarters (int amount);
int c_dimes (int amount);
int c_nickels (int amount);
int c_pennies (int amount);

// Main Function
int main (void)
{
    int amount;
    // User introduce a postive integer
    do
    {
        amount = get_int ("Enter change owed: ");
    }
    while (amount  < 0);

    //Calculate quarters
    int quarters = c_quarters (amount);
    amount = amount - quarters * 25;

    //Calculate dimes
    int dimes = c_dimes (amount);
    amount = amount - dimes * 10;

    //Calculate nickels
    int nickels = c_nickels (amount);
    amount = amount - nickels * 5;

    //Calculate pennies
    int pennies = c_pennies (amount);
    amount = amount - pennies * 1;

    //Sum the 4 coins
    int cash = quarters + dimes + nickels + pennies;
    printf ("%i\n", cash);
}

//Fuctions

int c_quarters (int amount)
{
    int quarters = 0;

    while (amount >= 25)
    {
        amount = amount - 25;
        quarters ++;
    }
    return quarters;
}

int c_dimes (int amount)
{
    int dimes = 0;

    while (amount >= 10)
    {
        amount = amount - 10;
        dimes ++;
    }
    return dimes;
}

int c_nickels (int amount)
{
    int nickels = 0;

    while (amount >= 5)
    {
        amount = amount - 5;
        nickels ++;
    }
    return nickels;
}

int c_pennies (int amount)
{
    int pennies = 0;

    while (amount >= 1)
    {
        amount = amount - 1;
        pennies ++;
    }
    return pennies;
}