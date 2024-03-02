#include<cs50.h>
#include<stdio.h>

int numberOfDigitCheck(long long int n);

int luhnsAlgorithm(long long int n);

void checkCards(long long int n, int m);

int main(void) {
    long long int Credit_number;
    int m;
    Credit_number = get_long("Enter your credit number: ");
    m = numberOfDigitCheck(Credit_number);
    if (luhnsAlgorithm(Credit_number) % 10 == 0) {
        checkCards(Credit_number,m);
        printf("\n");
    }
    else {
        printf("INVALID");
        printf("\n");
    }
}

int numberOfDigitCheck(long long int n){
    int count=0;
    if (n == 0) {
        count = 1;
    }
    else {
        while (n != 0) {
            count++;
            n /= 10;
        }
    }
    return count;
}

int luhnsAlgorithm(long long int n){
    int sum_last = 0;
    int sum_second = 0;
    int digit_position = 1;
    while (n>0){
        int digit =n % 10;
        n/=10;
        if (digit_position % 2 == 0) {
            long long int double_value = digit * 2;
            long long int result = double_value % 10;
            sum_second += result + double_value/10;
        }
        else {
            sum_last += digit;
        }
        digit_position++;
    }
    int sum = sum_last + sum_second;
    return sum;
}

void checkCards(long long int n, int m){
    while (n >= 100) {
        n /= 10;
    }
    if(n==37&& m==15) {
        printf("AMEX");
    }
    else if(n==30&& m==14){
        printf("Diners Club");
    }
    else if(n==60&& m==16){
        printf("Discover");
    }
    else if(n==35&& m==16){
        printf("JCB");
    }
    else if((n==22||n==51||n==52)&& m==16){
        printf("MASTERCARD");
    }
    else if((n==22|| n== 55 || n == 51)&& m==16){
        printf("MASTERCARD");
    }
    else if((n==41|| n== 40 || n == 42 || n==49)&&(m==16||m==13)){
        printf("VISA");
    }
    else {
        printf("INVALID");
    }
}


