#include <cs50.h>
#include <stdio.h>
#include <stdint.h>
// create a type of unsigned integers of length of 8 bits (1 byte)
typedef uint8_t BYTE;
int main(void)
{
    //open the file
    FILE* file = fopen("card.raw", "r");
    //check permission to open file
    if (file == NULL)
    {
        printf("Error opening the file \"ecard.raw\"...");
        return 1;
    }
    //prepare to write to new file
    FILE* jpeg = NULL;
    int count = 0;
    char name[8];
    BYTE buffer[512];
    //iritate over each byte of the raw file
    while (!feof(file))
    {
        //read each string of byte from the raw file
        fread(&buffer, sizeof(buffer), 1,file);
        //check if it is a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            //close previous opened file
            if (jpeg != NULL)
            {
                fclose(jpeg);
            }
            //name the jpeg file
            sprintf(name, "%03d.jpg",count);
            //increase count for name file
            count++;
            //open the jpeg file
            jpeg = fopen(name, "w");
            //write into jpeg file
            fwrite(&buffer, sizeof(buffer),1,jpeg);
            
        }
        //just write non-jpg file into temp
        else if (count > 0)
        {
            fwrite(&buffer, sizeof(buffer),1,jpeg);
        }
        
    }
    //close the raw file
    fclose(file);
    //close the last jpeg file
    fclose(jpeg);
}