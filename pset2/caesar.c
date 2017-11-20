#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
int main(int argc, string argv[])
{
    //check for argument in command line if not correct then end
    if (argc != 2)
    {
        printf("you are not following the format\n");
        return 1;
    }
    else
    {
        //convert argument into string
        int key = atoi(argv[1]);
        //read user input
        string s = GetString();
        for (int i = 0, l = strlen(s);i < l; i++)
        {
            //set variable for each character
            int c = s[i];
            //work with upper character
            if (isupper(c))
            {
                printf("%c",(c-65+key)%26+65 );
            }
            //work with lower character
            else if (islower(c))
            {
                printf("%c",(c-97+key)%26+97);
            }
            //copy input without processing
            else
            {
                printf("%c",c);
            }
            
        }
        printf("\n");
        return 0;
    }
}