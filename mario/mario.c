#include<cs50.h>
#include<stdio.h>

void space(int a);
void brick(int b);
void draw(int n);

int main(void){
    int n;
    //check input
    do {
    n = get_int("Enter the height of the pyramids (should be between 1-8): ");
    }

    while (n<1||n>8);
    draw(n);
}

void space(int n) {
    for(int i=0; i<n; i++) {
        printf(" ");
    }
}

void brick(int n){
    for(int i = 0; i < n; i++){
        printf("#");
    }
}

void draw(int n){
    for (int i = 0; i < n; i++) {
        //left side
        space(n - i - 1);
        // In ra ký tự '#' ở giữa (với 2 dấu cách)
        brick(i+1);
        space(2);
        brick(i+1);
        printf("\n");
    }
}
