#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool checkHead(uint8_t buffer[512]);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    //Open the memory card
    FILE *card = fopen(argv[1], "r");

    char filename[10];

    //Create a buffer for a block of data
    uint8_t buffer[512];
    int count = 0;
    FILE *img = NULL;
    bool found = false;

    //While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
       // Create JPEGs from the data
       if(checkHead(buffer))
       {
        found = true;
        if (count == 0)
        {
            sprintf(filename, "%03i.jpg",count);
            img = fopen(filename, "w");
            fwrite(&buffer, 1, 512, img);
            count++;
        }
        else
        {
            //found = false;
            fclose(img);
            sprintf(filename, "%03i.jpg",count);
            img = fopen(filename, "w");
            fwrite(&buffer, 1, 512, img);
            count++;
        }
       }
       else
       {
        if (found)
        {
            fwrite(&buffer, 1, 512, img);
        }
       }
    }
    fclose(img);
    fclose(card);
    return 0;
}

bool checkHead(uint8_t buffer[512]) {
    if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3]& 0xf0) == 0xe0)
    {
        return true;
    }
    else {
        return false;
    }
}
