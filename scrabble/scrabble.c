#include<stdio.h>
#include<cs50.h>
#include <ctype.h>
#include <string.h>

int checkScore(string s);

int main(void)
{
    int score[] = {0,0};
    string choice[2];
    for(int i = 0; i<2; i++) {
        string s = get_string("player %d : ", i + 1);
        for(int j = 0; j< strlen(s); j++) {
            s[j] = toupper(s[j]);
        }
        choice[i] = s;
        score[i] = checkScore(choice[i]);
    }
    if (score[0] > score[1]) {
        printf("Player 1 wins!\n");
    }
    else if (score[0] < score[1]) {
        printf("Player 2 wins!\n");
    }
    else {
        printf("Tie!\n");
    }
}

int checkScore(string s){
    int score = 0;
    char word[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    int point[] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
    for(int i = 0; i<strlen(s); i++){
        for(int j=0; j<26; j++){
            if (s[i] == word[j]) {
                score += point[j];
            }
        }
    }
    return score;
}

