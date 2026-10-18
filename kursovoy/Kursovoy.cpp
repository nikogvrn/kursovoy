#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>


double func(double x) {
    if (x < 30.0) {
        return 3.0 * log(x - 30.0 + 2.0) + 10.0;} //х не может быть меньше 28
    else if (x <= 55.0) {
        return 2.0 * (x - 42.5) + 48.0;}
    else {
        return 5.0 * sqrt(x- 55.0 + 1.0) + 58.0;}
}

int main(){
    setlocale(LC_CTYPE, "RUS");
    
    double x;
    scanf("%lf", &x);

    double Q = func(x);

    printf("X = %.2f\n", x);
    printf("Q(X) = %.2f\n", Q);

    return 0;
}