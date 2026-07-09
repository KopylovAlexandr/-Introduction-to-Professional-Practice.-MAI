#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_NUM   100
#define ERROR1 "Too many numbers \n"
#define ERROR2 "You have entered incorrect characters \n"
#define ERROR3 "File is empty"
#define ERROR4 "Need to create a file"


bool is_file_empty() { //Проверка на пустой файл
    FILE *f = fopen("f.txt", "r");
    if (!f) { //Проверка на наличие файла
        printf("ERROR");
        return -1; // ошибка открытия
    }
    if (fseek(f, 0, SEEK_END) != 0) { // Переместиться в конец
        fclose(f);
        return -1; // ошибка
    }
    long size = ftell(f); //Размер файла
    fclose(f);
    return (size == 0) ? false : true; // 0 — пустой, 1 — не пустой
}

int get_data(double *arr){// Получение количества элементов и их запись в массив
    FILE *f = fopen("f.txt", "r");
    if (!f){// Проверка на правильное открытие файла
        printf("ERROR");
        return -1;
    }
    double a; // Временная переменная
    int i = 0;
    int flag = 1;
    while (i < MAX_NUM && flag) {
        flag = fscanf(f, "%lf", &a);
        if (flag == EOF){
            fclose(f);
            break;
        }
        if (flag == 0){ // Если не считалось значение, ошибка
            printf(ERROR2);
            fclose(f);
            return 0;
        }
        arr[i] = a;
        i++;
    }
    fclose(f);
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

int forming_file(double *arr2, int a){// Формирование исходного файла
    FILE *f = fopen("f.txt", "a");
    for (int i = 0; i < a; i++){
        fprintf(f, " %lf", arr2[i]);
    }
    fclose(f);
    return 0;
}

int read_file(int s){
    FILE *f = fopen("f.txt", "r");
    double arr[s];
    double a;
    int i = 0;
    while (fscanf(f, "%lf", &a) == 1){
        arr[i] = a;
        i++;
    }
    for (int i = 0; i < s; i++){
        printf(" %.1lf", arr[i]);
    }
    return 0;
}

int main(){
    double arr[MAX_NUM];
    if (!is_file_empty()){
        printf(ERROR3);
    }
    size_t s = get_data(arr);

    int a = positive_counter(arr, s);

    double arr2[a];
    forming_arr2(arr2, a, max_number(arr, s));

    forming_file(arr2, a);

    read_file(s+a);

    return 0;
}