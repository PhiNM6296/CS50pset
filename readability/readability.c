#include<stdio.h>
#include<cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int countSentences(string s);

int countLetter(string s);

int countWords(string s);

int main(void){
    string s = get_string("Enter your text: ");
    int w = countWords(s);
    double L = (countLetter(s)*100)/w;
    double S = (countSentences(s)*100)/w;
    double index = 0.0588 * L - 0.296 * S - 15.8;
    int id = round(index);
    if(id < 1) {
        printf("Before Grade 1\n");
    }
    else if (id > 16) {
        printf("Grade 16+\n");
    }
    else {
        printf("Grade %d\n",id);
    }
}

int countWords(string s){
    int c = 0;
    for(int i =0, n = strlen(s); i<n; i++) {
        if(s[i] == ' ')
        {
            c++;
        }
    }
    int count = c + 1;
    return count;
}

int countSentences(string s){
    int count = 0;
    for(int i =0, n = strlen(s); i<n; i++) {
        if(s[i] == '.'||s[i] == '?' || s[i] == '!')
        {
            count++;
        }
    }
    return count;
}
int countLetter(string s){
    int count = 0;
    for(int i =0, n = strlen(s); i<n; i++) {
        if((s[i]>='A' && s[i]<='Z')||(s[i]>='a' && s[i]<='z') )
        {
            count++;
        }
    }
    return count;
}
