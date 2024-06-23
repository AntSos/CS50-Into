#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each row
    for (int i = 0; i < height; i++)
    {
        // Loop through each column
        for (int j = 0; j < width; j++)
        {
            // Convert pixels to float
            float Red = image[i][j].rgbtRed;
            float Green = image[i][j].rgbtGreen;
            float Blue = image[i][j].rgbtBlue;

            // Averange value
            int averange = round((Red + Green + Blue) / 3);
            // Asign averange value to every pixel
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = averange;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each row
    for (int i = 0; i < height; i++)
    {
        // Loop through each column
        for (int j = 0; j < width; j++)
        {
            // Convert pixels to float
            float org_Red = image[i][j].rgbtRed;
            float org_Green = image[i][j].rgbtGreen;
            float org_Blue = image[i][j].rgbtBlue;

            // Sepia values if exced 255
            int sepiaRed = round(0.393 * org_Red + 0.769 * org_Green + 0.189 * org_Blue);
            int sepiaGreen = round(0.349 * org_Red + 0.686 * org_Green + 0.168 * org_Blue);
            int sepiaBlue = round(0.272 * org_Red + 0.534 * org_Green + 0.131 * org_Blue);

            // Update every pixel value
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Update pixels values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each row
    for (int i = 0; i < height; i++)
    {
        // Loop through each column
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy the original image
    RGBTRIPLE temp[height][width];
    // Loop through each row
    for (int i = 0; i < height; i++)
    {
        // Loop through each column
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            int t_Red, t_Green, t_Blue;
            t_Red = t_Green = t_Blue = 0;

            float counter = 0.0;
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int curr_X = i + x;
                    int curr_Y = j + y;

                    // Check adjoining pixel
                    if (curr_X < 0 || curr_X > (height - 1) || curr_Y < 0 || curr_Y > (width - 1))
                    {
                        continue;
                    }

                    t_Red += image[curr_X][curr_Y].rgbtRed;
                    t_Green += image[curr_X][curr_Y].rgbtGreen;
                    t_Blue += image[curr_X][curr_Y].rgbtBlue;

                    counter++;
                }

                // Averange pixel
                temp[i][j].rgbtRed = round(t_Red / counter);
                temp[i][j].rgbtGreen = round(t_Green / counter);
                temp[i][j].rgbtBlue = round(t_Blue / counter);
            }
        }
    }

    // Copy bluer pixels into original image
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}