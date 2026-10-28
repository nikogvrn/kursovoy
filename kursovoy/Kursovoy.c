#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>

double calculate_q(double x)
{
    if (x < 30.0) {
        return 3.0 * log(x - 30.0 + 2.0) + 10.0;
    }
    else if (x <= 55.0) {
        return 2.0 * (x - 42.5) + 48.0;
    }
    else {
        return 5.0 * sqrt(x - 55.0 + 1.0) + 58.0;
    }
}

int main(void)
{
    setlocale(LC_CTYPE, "RUS");

    double x;
    double q;

    printf("Введите расход x от 5 до 80 л/мин: ");

    if (scanf("%lf", &x) != 1) {
        printf("Ошибка: нужно ввести число.\n");
        return 1;
    }

    if (x < 5.0 || x > 80.0) {
        printf("Ошибка: x должен быть в диапазоне от 5 до 80.\n");
        return 1;
    }

    if (x <= 28.0) {
        printf("По заданной формуле расчёт невозможен: требуется x > 28.\n");
        return 1;
    }

    q = calculate_q(x);

    printf("x = %.2f\n", x);
    printf("Q(X) = %.2f\n", q);

    return 0;
}