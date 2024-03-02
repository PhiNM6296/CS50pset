#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int checkSub(string s);
string toUppercase(string s);

int main(int argc, string argv[])
{
    // check argument (needs 1 argument)
    if (argc != 2)
    {
        printf("Usage: ./substitution key.\n");
        return 1;
    }
    // convert that string to upper case to process it easier
    string c = toUppercase(argv[1]);
    if (strlen(c) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (checkSub(c) == 1)
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }
    else if (checkSub(c) == 2)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }
    else
    {
        string text = get_string("plaintext: ");
        int n = strlen(text);
        char cipher[100] = {0};
        for(int i = 0; i<n; i++) {
            //If text is Uppercase letter:
            if(text[i] >= 'A' && text[i] <= 'Z') {
                cipher[i] = c[text[i] - 'A'];
            }
            //If text is Lowercase letter:
            else if(text[i] >= 'a' && text[i] <= 'z') {
                cipher[i] = c[toupper(text[i]) - 'A'] + 32;
            }
            //If text is anything else:
            else {
                cipher[i] = text[i];
            }
        }
        printf("ciphertext: ");
        for(int i =0;i<n;i++){
            printf("%c",cipher[i]);
        }
        printf("\n");
        return 0;
    }
}

int checkSub(string s)
{
    int count[26] = {0};

    for (int i = 0; i < 26; i++)
    {
        if (s[i] < 'A' || s[i] > 'Z')
        {
            return 1; // Not alphabetic
        }
        count[s[i] - 'A']++;
        if (count[s[i] - 'A'] > 1)
        {
            return 2; // Repeated characters
        }
    }
    return 0; // No issues found
}

string toUppercase(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        s[i] = toupper(s[i]);
    }
    return s;
}

