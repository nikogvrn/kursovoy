#define _CRT_SECURE_NO_WARNINGS

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <iso646.h>

double calculate_q(double x);

int main(void)
{
    int had_input_error = 0;

    setlocale(LC_CTYPE, "RUS");

    printf("Состояние программы: ИНИЦИАЛИЗАЦИЯ.\n");
    printf("Настройте параметры контроля.\n");

    double q0 = 48.0;

    double allowed_deviation_percent = 10.0;

    double q_lower_limit;
    double q_upper_limit;
    q_lower_limit = q0 * (1.0 - allowed_deviation_percent / 100.0);
    q_upper_limit = q0 * (1.0 + allowed_deviation_percent / 100.0);

    const char* input_file_name = "input.txt";
    FILE* input_file = fopen(input_file_name, "r");

    const char* output_file_name = "results.txt";
    FILE* output_file = fopen(output_file_name, "w");

    printf("\nСостояние программы: РАБОТА.\n");
    printf("Границы Q: от %.2f до %.2f.\n\n", q_lower_limit, q_upper_limit);

    fprintf(output_file,
        "Параметры контроля: Q0 = %.2f, отклонение = %.2f%%, "
        "границы Q = [%.2f; %.2f].\n\n",
        q0, allowed_deviation_percent, q_lower_limit, q_upper_limit);

    double x;
    while (fscanf(input_file, "%lf", &x) == 1) {
        double q;
        const char* state;

        if (x < 5.0 or x > 80.0) {
            printf("Измерение пропущено: X должно быть в диапазоне 5–80.\n");
            fprintf(output_file,
                "Измерение пропущено: X должно быть в диапазоне 5–80.\n");
            had_input_error = 1;
            continue;
        }

        if (x <= 28.0) {
            printf("Измерение X = %.2f пропущено: формула не определена при X ≤ 28.\n",
                x);
            fprintf(output_file,
                "Измерение X = %.2f пропущено: формула не определена при X ≤ 28.\n",
                x);
            had_input_error = 1;
            continue;
        }

        q = calculate_q(x);

        if (q >= q_lower_limit and q <= q_upper_limit) {
            state = "НОРМА";
        }
        else {
            state = "ПРЕДУПРЕЖДЕНИЕ";
        }
        printf("Показание: X = %.2f, Q = %.2f, состояние: %s.\n",
            x, q, state);
        fprintf(output_file,
            "Показание: X = %.2f, Q = %.2f, состояние: %s.\n",
            x, q, state);
    }

    printf("Состояние программы: КОНЕЦ.");
    fprintf(output_file, "Состояние программы: КОНЕЦ.\n");

    fclose(input_file);
    fclose(output_file);

    if (had_input_error) {
        return 1;
    }
    else {
        return 0;
    }
}

double calculate_q(double x)
{
    if (x < 30.0) {
        return 3.0 * log(x - 28.0) + 10.0;
    }
    else if (x <= 55.0) {
        return 2.0 * (x - 42.5) + 48.0;
    }
    else {
        return 5.0 * sqrt(x - 54.0) + 58.0;
    }
}