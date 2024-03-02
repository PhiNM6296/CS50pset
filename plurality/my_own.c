#include<stdio.h>
#include<cs50.h>
#include <ctype.h>
#include<string.h>

typedef struct
{
    string name;
    int votes;
}
candidate;

void Result(candidate candidates[], int length);

int main(int argc, string argv[])
{
    if (argc > 9) {
        printf("Maximum number of candidate is 9\n");
        return 1;
    }

    candidate candidates[argc];
    for(int i = 0; i < argc; i++) {
        candidates[i].votes=0;
        candidates[i].name=argv[i];
    }

    int n = get_int("Number of voters: ");
    string s[n];

    for(int i = 0; i < n; i++){
        s[i] = get_string("Vote: ");
        int check = 0;

        for(int j = 0; j < argc; j++) {
            if(strcmp(candidates[j].name, s[i]) == 0) {
            candidates[j].votes++;
            check++;
            }
            }
            if (check == 0) {
                printf("Invalid vote\n");
            }
    }
    Result(candidates,argc);
}

void Result(candidate candidates[], int length){
    int max = candidates[0].votes;
    for (int i = 1; i< length; i++) {
        if (candidates[i].votes > max) {
            max = candidates[i].votes;
        }
    }
    for (int i = 1; i< length; i++) {
        if (candidates[i].votes == max) {
            printf("%s\n",candidates[i].name);
        }
    }
}

