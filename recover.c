#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Security condition
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open the memory card
    FILE *input_file = fopen(argv[1], "r");
    {
        // Checking input file
        if (input_file == NULL)
        {
            printf("File not open");
            return 1;
        }
    }

    // Store blocks of 512 bytes
    unsigned char buffer[512];

    // Count number of images
    int count = 0;

    // File pointer for recovered images
    FILE *output_file = NULL;

    // Allocate memory
    char *file_name = malloc(8 * sizeof(char));

    // Looping to read the blocks
    while (fread(buffer, sizeof(char), 512, input_file))
    {
        // Looking for the star of a .JPG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close file if it was found it
            if (count > 0)
            {
                fclose(output_file);
            }

            // Write the new .JPG file
            sprintf(file_name, "%03i.jpg", count);

            // Open output file
            output_file = fopen(file_name, "w");

            // Count images
            count++;
        }

        if (output_file != NULL)
        {
            fwrite(buffer, sizeof(char), 512, output_file);
        }
    }

    // Close files
    free(file_name);
    fclose(output_file);
    fclose(input_file);

    return 0;
}