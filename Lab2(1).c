#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_NUMBER 100
#define ERROR1 "Too many numbers \n"
#define ERROR2 "You have entered incorrect characters \n"


int create_file(){// Создание файла для записи 
    FILE *f = fopen("f.bin", "wb");
    if (f == NULL) { // Проверка на правильность открытия/создания
        return 1;
    }
    return 0;
}

int get_data(double *arr){// Получение данных и формирование массива
    double a; // Временная переменная для записи данных в массив
    int i = 0; //Счетчик записанных в массив слов

    puts("Please enter no more than 100 real numbers");

    int flag = 1;
    while (i <= MAX_NUMBER && flag) {
        flag = scanf("%lf", &a) == 1;
        arr[i] = a;
        i++;
        int c = getchar(); // читаем следующий символ
        if (c == '\n') { // Если Enter, то завершаем считывание
            break;
        }
        if ((c != ' ' && c != '\t') && !isdigit(c)){ //Если какой-либо символ не цифра, ошибка
            printf(ERROR2);
            return 0;
        }
        if (!flag){ // Если не считалось значение, ошибка
            printf(ERROR2);
            return 0;
        }
    }
    return i;
}

int positive_counter(double *arr, size_t s){// Считывание положительных чисел
    int cnt = 0;
    for (unsigned int i = 0; i < s; i++){
        if (arr[i] >= 0){
            cnt++;
        }
    }
    return cnt;
}

double max_number(double *arr, int s){//Нахождение максимального числа
    double mx = -10000000000.0;
    for (int i = 0; i < s; i++){
        if (arr[i] >= mx){
            mx = arr[i];
        }
    }
    return mx;
}

int forming_arr2(double *arr2, int a, double mx){//Формирование вспомогательного массива
    for (int i = 0; i < a; i++){
        arr2[i] = mx;
    }
    return 0;
}

int forming_file(double *arr, int s, double *arr2, int a){//Формирование исходного файла
    FILE *f = fopen("f.bin", "ab");
    // if (f == NULL) { // Проверка на правильность открытия/создания
    //     return 1;
    // }
    fwrite(arr, sizeof(double), s, f); //Запись исходных данных
    fwrite(arr2, sizeof(double), a, f); //Дозапись по условию
    fclose(f);
    return 0;
}

int read_file(int a, int s){
    double final[a+s];
    FILE *f = fopen("f.bin", "rb");
    fread(final, sizeof(double), s+a, f);

    
    for (int i = 0; i < a+s; i++){
        printf("%.2lf\n", final[i]);
    }
    return 0;
}


int main(){
    double arr[MAX_NUMBER]; // Массив с числами
    create_file();
    size_t s = get_data(arr); // Количество элементов в массиве
    int a = positive_counter(arr, s); // Количество положительных чисел

    double arr2[a]; // Вспомогательный массив для максимального числа
    forming_arr2(arr2, a, max_number(arr, s));

    forming_file(arr, s, arr2, a);

    read_file(a, s);

    return 0;
}