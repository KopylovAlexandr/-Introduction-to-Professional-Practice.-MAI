#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define ERROR_IPT "Incorrect input"


int fact(int p){ //Факториал числа
    int res = 1;
    for (int i = 2; i <= p; i++){
        res *= i;
    }
    return res;
}

double rnd(double x, int places) {
    double a = pow(10.0, places);
    return round(x * a) / a;
}


double way1(double x, double a, int n){ //Определение с заданной точностью
    double res = 1;
    int i = 0;
    while (i <= 50){
        res += (double)((a-i)*pow(x, i+1))/(double)fact(i+1); 
        i++;
    }
    
    return rnd(res, n);
}

double way2(double x, double a, int n){ //Определение для заданного количества членов ряда
    double res = 1;
    for (int i = 0; i < n; i++){
        res += (double)((a-i)*pow(x, i+1))/(double)fact(i+1); 
    }
    return res;
}


int main(){
    double a; //Степень
    double x; //Переменная
    int q; //Выбор способа определения 
    int n; //Количество членов ряда или точнсть
    
    printf("Select: \n 1: Calculate with a given accuracy \n 2: Calculate for a given number of series members \n");
    if (scanf("%d", &q) == 0){
        printf(ERROR_IPT);
        return 1;
    }

    printf("Enter x \n");
    if (scanf("%lf", &x) == 0){
        printf(ERROR_IPT);
        return 1;
    }

    printf("Enter a \n");
    if (scanf("%lf", &a) == 0){
        printf(ERROR_IPT);
        return 1;
    }



    switch (q)
    {
    case 1:
        printf("Please enter the required precision");
        if (scanf("%d", &n) == 0){
            printf(ERROR_IPT);
            return 1;
        }
        printf("%lf", way1(x, a, n));
        break;
    case 2:
        printf("Enter the required number of series members");
        if (scanf("%d", &n) == 0){
            printf(ERROR_IPT);
            return 1;
        }
        printf("%lf", way2(x, a, n));
        break;
    default:
        printf(ERROR_IPT);
        return 0;
    }

    return 0;
}