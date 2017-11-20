#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main(int argc, string argv[])
{
    //check if argument in command line was correct if not end
    if (argc != 2)
    {
        printf("you have input wrong argument for command line");
        return 1;
    }
    else
    {
        //check for alphabetic input if not end
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Key must be alphabetic chars only.");

                return 1;
            }
        }
    }
    //set variable for string
    string k = argv[1];
    //set variable for string length
    int kLen = strlen(k);
    //ask for input from user
    string s = GetString();
    
    for (int i = 0,j =0, l = strlen(s); i < l; i++)
    {
        int key = tolower(k[j%kLen]) - 'a';
        if (isupper(s[i]))
        {
            printf("%c", (s[i]-'A'+key)%26 + 'A');
            j++;
        }
        else if (islower(s[i]))
        {
            printf("%c", (s[i]-'a'+key)%26 + 'a');
            j++;
        }
        else
        {
            printf ("%c", s[i]);
        }
    }
    printf("\n");
    return 0;
    
}