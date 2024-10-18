#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415
#define MAX_INTERATION 1000
#define MIN_EPSILON 0.000000001


double BinPow(double a, int n) {
    double res = 1;
    while (n != 0) {
        if (n & 1)
            res = res * a;
        a = a * a;
        n >>= 1;
    }
    return res;
}

double factorial(int n) {
    double res = 1.0;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

// (1.1) е через lim
double ELimit(double epsilon) {
    double e = 10000000.0;
    int n = 1;
    while (n <= MAX_INTERATION) {
        double term = BinPow(1.0 + 1.0 / n, n);
        if (fabs(term - e) < epsilon) {
            return e;
        }
        e = term;
        n++;
    }
    fprintf(stderr, "ELimit ne soshelsya za %d iteracij \n", MAX_INTERATION);
    return e;
}

// 1.2) е через ряд
double ESeries(double epsilon) {
    double e = 0.0;
    double term = 1.0;
    int n = 0;
    while (n <= MAX_INTERATION) {
        if (n != 0){
            term /= n;
        }
        term /= 1;
        e += term;
        if (fabs(term) < epsilon) {
            return e;
        }
        n++;
    }
    fprintf(stderr, "ESeries ne soshelsya za %d iteracij \n", MAX_INTERATION);
    return e;
}

// (1.3) е через уравнение
double EEquation(double epsilon) {
    double x = 2.0;
    for (int i = 0; i < MAX_INTERATION; i++) {
        x = x - (log(x) - 1.0) / (1.0 / x);
        if (fabs(log(x) - 1.0) < epsilon) {
            return x;
        }
    }
    fprintf(stderr, "EEquation ne soshelsya za %d iteracij \n", MAX_INTERATION);
    return x;
}

// 2.1 Пи через lim
double PiLimit(double epsilon) {
    double pi = 4;
    int n = 1;

    while (n <= MAX_INTERATION) {
        double prev_pi = pi;
        pi *= 4.0 * ((n + 1) * n) / BinPow(2 * n + 1, 2);
        if (fabsl(pi - prev_pi) < epsilon) {
            return pi;
        }
        n++;
    }
    fprintf(stderr, "PiLimit ne soshelsya za %d iteracij \n", MAX_INTERATION);
    return pi;
}

// 2.2 Пи через ряд
double PiSeries(double epsilon) {
    double pi = 1.0;
    int n = 2;
    while (n <= MAX_INTERATION) {
        double term = ((n - 1) % 2 ? -1.0 : 1.0) / (2 * n - 1);
        pi += term;
        if (fabsl(term) < epsilon) {
            return pi * 4;
        }
        n++;
    }
    fprintf(stderr, "PiSeries ne soshelsya za %d iteracij \n", MAX_INTERATION);
    return pi * 4;
}

// 2.3 Пи через уравнение
double PiEquation(double epsilon) {
    double x = 3.0;
    for (int i = 0; i < MAX_INTERATION; i++) {
        x = x - (cos(x) + 1.0) / (-sin(x));

        if (fabsl(cos(x) + 1.0) < epsilon) {
            return x;

        }
    }
    fprintf(stderr, "PiEquation ne soshelsya za %d iteracij \n", MAX_INTERATION);
    return x;
}

// 3.1 ln  чкрез lim
double Ln2Limit(double epsilon) {
    double ln2 = 100000.0;
    double term;
    int n = 1;
    while (n <= MAX_INTERATION) {
        term = n * (pow(2, 1.0 / n) - 1);
        if (fabsl(term - ln2) < epsilon) {
            return ln2;
        }
        ln2 = term;
        n++;
    }
    fprintf(stderr, "Ln2Limit ne soshelsya za %d iteracij \n", MAX_INTERATION);
    return ln2;
}
 
// 3.2 ln2 через hzl
double Ln2Series(double epsilon) {
    double ln2 = 0.0;
    int sign = 1;
    int n = 1;
    while (n <= MAX_INTERATION) {
        double term = 1.0 / n;
        ln2 += sign * term;
        sign = -sign;
        if (fabsl(term) < epsilon) {
            return ln2;
        }
            n++;
    }
    fprintf(stderr, "Ln2Series ne soshelsya za %d iteracij \n", MAX_INTERATION);
    return ln2;
}

// 3.3 ln через уравнение
double Ln2Equation(double epsilon) {
    double x = 1.0;
    for (int i = 0; i < MAX_INTERATION; i++) {
        x = x - (exp(x) - 2.0) / exp(x);
        if (fabsl(exp(x) - 2.0) < epsilon) {
            return x;
        }
    }
    fprintf(stderr, "Ln2Equation ne soshelsya za %d iteracij \n", MAX_INTERATION);
    return x;
}

// 4.1 sqrt2 -> lim
double Sqrt2Limit(double epsilon) {
    double sqrt2 = -0.5;
    double next = sqrt2 - (sqrt2 * sqrt2) / 2 + 1;

    for (int i = 0; i < MAX_INTERATION; i++) {
        if (fabsl(sqrt2 - next) < epsilon) {
            return next;
        }
        sqrt2 = next;
        next = sqrt2 - (sqrt2 * sqrt2) / 2 + 1;
    }
    fprintf(stderr, "Sqrt2Limit ne soshelsya za %d iteracij \n", MAX_INTERATION);
    return next;
}

// 4.2 sqrt -> ряд
double Sqrt2Series(double epsilon) {
    double sqrt2 = 1.0;
    double term;
    int n = 2;
    while (n <= MAX_INTERATION) {
        term = pow(2, pow(2, -n));
        sqrt2 *= term;
        if (fabsl(term - 1) < epsilon) {
            return sqrt2;
        }
        n++;
    }
    fprintf(stderr, "Sqrt2Series ne soshelsya za %d iteracij \n", MAX_INTERATION);
    return sqrt2;
}

// 4.3 sqrt2 -> уравнение
double Sqrt2Equation(double epsilon) {
    double x = 1.0;
    for (int i = 0; i < MAX_INTERATION; i++) {
        double prev_x = x;
        x -= (x * x - 2.0) / (2 * x);
        if (fabs(x - prev_x) < epsilon) {
            return x;
        }
    }
    fprintf(stderr, "Sqrt2Equation ne soshelsya za %d iteracij \n", MAX_INTERATION);
    return x;
}

// 5.1 gam -> lim
double GammaLimit(double epsilon) {
    double gamma = -100;
    double prev_gamma;
    int m = 1;
    double fact_m = 2;
    while (m < MAX_INTERATION) {
        double sum = 0.0;
        double fact_k = 1;
        for (int k = 2; k <= m; k++) {
            fact_k *= k;
            double binomial = fact_m / (fact_k * factorial(m - k));
            sum += binomial * (k % 2 ? -1.0 : 1.0) * log(fact_k) / k;
        }
        prev_gamma = gamma;
        gamma = sum;

        if (fabs(gamma - prev_gamma) < epsilon) {
            return gamma;
        }
        m++;
        fact_m *= m;
    }
    fprintf(stderr, "GammaLimit ne soshelsya za %d iteracij \n", MAX_INTERATION);
    return gamma;
}

// 5.2 gam -> ряд
double GammaSeries(double epsilon) {
    double gamma = 0.0;
    double term;
    int k = 2;

    while (k < MAX_INTERATION) {
        term = (1.0 / pow(floor(sqrt(k)), 2)) - (1.0 / k);
        gamma += term;
        if (fabsl(term) < epsilon && term != 0) {
            return gamma - PI * PI / 6.0;
         }

        k++;
    }
    fprintf(stderr, "GammaSeries ne soshelsya za %d iteracij \n", MAX_INTERATION);
    return gamma - PI * PI / 6.0;
}

bool IsPrime(int n) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

double ProdResult(int t) {
    double product = 1.0;
    for (int p = 2; p <= t; p++) {
        if (IsPrime(p)) {
            product *= (double)(p - 1) / p;
        }
    }
    return product;
}

// 5.3 gam -> уравнение
double GammaEquation(double epsilon) {
    double t = 2.0;
    double prev_x = 0.0;

    for (int i = 0; i < MAX_INTERATION; i++) {
        double product = ProdResult((int)t);

        double current_x = log(t) * product;
        if (fabs(current_x - prev_x) < epsilon) {
            return current_x;
        }
        prev_x = current_x;
        t += 1;
    }
    fprintf(stderr, "GammaEquation ne soshelsya za %d iteracij \n", MAX_INTERATION);
    return prev_x;
}

double MyStrtod(const char* str, char** end) {
    double result;
    while (isspace((unsigned char)*str)) {
        str++;
    }
    if (*str == '-') {
        fprintf(stderr, "Error: znachenie epsilon dolzhno byt' strogo bol'she 0.\n");
        return -1;
    } else if (*str == '+') {
        str++;
    }

       // Извлекаем целую часть числа
    double integer_part = 0.0;
    while (isdigit((unsigned char)*str)) {
        integer_part = integer_part * 10 + (*str - '0');
        str++;
    }

    // Извлекаем дробную часть числа
    double fraction_part = 0.0;
    if (*str == '.') {
        str++;
        double divisor = 10.0;

        while (isdigit((unsigned char)*str)) {
            fraction_part += (*str - '0') / divisor;
            divisor *= 10;
            str++;
        }
    }

    // Формируем результат с учетом знака
    result = integer_part + fraction_part;


    // Устанавливаем конечный указатель
    if (end) {
        *end = (char*)str;
    }
    return result;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Your programm must start with: %s <epsilon>", argv[0]);
        return 1;
    }

    char* end;
    double epsilon = MyStrtod(argv[1], &end);
    if (*end != '\0') {
        printf( "Incorrect epsilon.\n");
        return 1;
    }
    if (epsilon < MIN_EPSILON) {
        fprintf(stderr, "Error: установите epsilon >= %e\n", MIN_EPSILON);
        return -1; // Возвращаем ошибочный код или значение
    }

    printf("e Const\n");
    printf("\tlimit: %f\n", ELimit(epsilon));
    printf("\trow: %f\n", ESeries(epsilon));
    printf("\tequation: %f\n", EEquation(epsilon));
    printf("pi Const\n");
    printf("\tlimit: %f\n", PiLimit(epsilon));
    printf("\trow: %f\n", PiSeries(epsilon));
    printf("\tequation: %f\n", PiEquation(epsilon));
    printf("ln of 2\n");
    printf("\tlimit: %f\n", Ln2Limit(epsilon));
    printf("\trow: %f\n", Ln2Series(epsilon));
    printf("\tequation: %f\n", Ln2Equation(epsilon));
    printf("sqrt of 2\n");
    printf("\tlimit: %f\n", Sqrt2Limit(epsilon));
    printf("\trow: %f\n", Sqrt2Series(epsilon));
    printf("\tequation: %f\n", Sqrt2Equation(epsilon));
    printf("Gamma\n");
    printf("\tlimit: %f\n", GammaLimit(epsilon));
    printf("\trow: %f\n", GammaSeries(epsilon));
    printf("\tequation: %f\n", GammaEquation(epsilon));
    return 0;
}
