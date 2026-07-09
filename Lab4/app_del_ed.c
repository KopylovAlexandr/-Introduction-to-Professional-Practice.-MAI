#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ADD_INPUT "Please enter by spaces: \n \n"\
    "1. The train number \n"\
    "2. Train type \n"\
    "3. Departure time \n"\
    "4. Number of carriages (up to 15) \n"\
    "5. Carriage type \n"\
    "6. Number of available seats \n"\

// Глобальные переменные для времени отправки
static double min; 
static int hour;

struct train //Структура для одной записи о поезде
{
    int number_train;
    char type_train[20];
    double time_deport;
    int count_carriage;
    char type_carriage[20];
    int count_free_place;
};

int is_alpha_str(char *s) { //Проверяет является переменная строкой из букв
    if (s[0] == '\0') return 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (isalpha((unsigned char)s[i])){
            return 0; // найден не-буквенный символ
        }
    }
    return 1;
}

void int_bubble_sort_up(int arr[], int n){
    int flag, t;
    for (int i = 0; i < n-1; i++){
        flag = 0;
        for (int j = 0; j < n-i-1; j++){
            if (arr[j] > arr[j+1]){
                t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
                flag = 1;
            } 
        }
        if (!flag) break;
    }
}

void int_bubble_sort_down(int arr[], int n){
    int flag, t;
    for (int i = 0; i < n-1; i++){
        flag = 0;
        for (int j = 0; j < n-i-1; j++){
            if (arr[j] < arr[j+1]){
                t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
                flag = 1;
            } 
        }
        if (!flag) break;
    }
}

void double_bubble_sort_up(double arr[], int n){
    double t;
    int flag;
    for (int i = 0; i < n-1; i++){
        flag = 0;
        for (int j = 0; j < n-i-1; j++){
            if (arr[j] > arr[j+1]){
                t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
                flag = 1;
            } 
        }
        if (!flag) break;
    }
}

void double_bubble_sort_down(double arr[], int n){
    double t;
    int flag;
    for (int i = 0; i < n-1; i++){
        flag = 0;
        for (int j = 0; j < n-i-1; j++){
            if (arr[j] < arr[j+1]){
                t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
                flag = 1;
            } 
        }
        if (!flag) break;
    }
}


int add_post(){ //Формирование структуры и запись в базу данных, возвращает структуру
    struct train s;
    struct train *p = &s;
    int nt, cc, cfp;
    double td;
    char tt[20];
    char tc[20];
    FILE *f = fopen("f.bin", "ab+"); //Открытие файла для базы данных
    printf(ADD_INPUT);
    if (scanf("%d %s %lf %d %s %d", &nt, tt, &td, &cc, tc, &cfp) != 6){
        return 0;
    }
    if (is_alpha_str(tt) || is_alpha_str(tc)){
        printf("Incorrect input! \n");
        return 0;
    }
    if (cc > 15){ // Проверка на число вагонов
        printf("Too many carriages! \n");
        return 0;
    }

    //Выделяем отдельно часы и минуты
    hour = (int)td;
    min = (int)(td-hour)*10;

    if ((hour >= 24) || (min >= 60)){
        printf("Incorrect time format! \n");
        return 0;
    }

    // Записываем данные в структуру
    p->number_train = nt;
    strcpy(p->type_train, tt);
    p->time_deport = td;
    p->count_carriage = cc;
    strcpy(p->type_carriage, tc);
    p->count_free_place = cfp;

    // Проверяем на совпадение номеров
    struct train d;
    while (fread(&d, sizeof(struct train), 1, f) == 1){
        if (d.number_train == s.number_train){
            printf("This number is already taken! \n");
            return 0;
        }
    }

    // Записываем в файл
    fwrite(p, sizeof(struct train), 1, f);
    fclose(f);
    return 1;
}

int delete_post(int target){ // Удаление конкретной записи
    FILE *f = fopen("f.bin", "rb");
    FILE *r = fopen("r.bin", "wb");
    struct train t;
    // short flag = 0;
    while (fread(&t, sizeof(struct train), 1, f) == 1) {
        if (t.number_train == target){
            // flag = 1;
            continue;
        }
        fwrite(&t, sizeof(struct train), 1, r);
    }
    fclose(f);
    fclose(r);

    remove("f.bin");
    rename("r.bin", "f.bin");

    return 1;
}

int search_int_posts(int section){
    FILE *f = fopen("f.bin", "rb");
    if (!f) {
        printf("Fail is not found.\n");
        return 0;
    }
    struct train t;

    switch (section)
    {
    case 1:
        printf("Enter the train number \n");
        int target1;
        if (scanf("%d", &target1) == 0){
            printf("Error input! \n");
            return 0;
        }
        printf("N  | Number Train | Type Train | Time | Carriages | Type Carriage | Free Place\n");
        printf("-----------------------------------------------------------------------------\n");
        int i = 1;
        while (fread(&t, sizeof(struct train), 1, f) == 1){
            if (t.number_train == target1){
                printf("%-2d | %-13d| %-11s| %-6.2lf| %-10d| %-14s| %-10d\n", i,
            t.number_train, t.type_train, t.time_deport,
            t.count_carriage, t.type_carriage, t.count_free_place);
            i++;
            printf("-----------------------------------------------------------------------------\n");
            }
        }
        break;
    case 2:
        printf("Enter the number of carriages \n");
        int target2;
        if (scanf("%d", &target2) == 0){
            printf("Error input! \n");
            return 0;
        }
        printf("N  | Number Train | Type Train | Time | Carriages | Type Carriage | Free Place\n");
        printf("-----------------------------------------------------------------------------\n");
        int j = 1;
        while (fread(&t, sizeof(struct train), 1, f) == 1){
            if (t.count_carriage == target2){
                printf("%-2d | %-13d| %-11s| %-6.2lf| %-10d| %-14s| %-10d\n", j,
            t.number_train, t.type_train, t.time_deport,
            t.count_carriage, t.type_carriage, t.count_free_place);
            j++;
            printf("-----------------------------------------------------------------------------\n");
            }
        }
        break;
    case 3:
        printf("Enter the number of free place \n");
        int target3;
        if (scanf("%d", &target3) == 0){
            printf("Error input! \n");
            return 0;
        }
        printf("N  | Number Train | Type Train | Time | Carriages | Type Carriage | Free Place\n");
        printf("-----------------------------------------------------------------------------\n");
        int k = 1;
        while (fread(&t, sizeof(struct train), 1, f) == 1){
            if (t.count_free_place == target3){
                printf("%-2d | %-13d| %-11s| %-6.2lf| %-10d| %-14s| %-10d\n", k,
            t.number_train, t.type_train, t.time_deport,
            t.count_carriage, t.type_carriage, t.count_free_place);
            k++;
            printf("-----------------------------------------------------------------------------\n");
            }
        }
        break;
    default:
        break;
    }
    fclose(f);
    return 1;
}

int search_str_posts(int section){
    FILE *f = fopen("f.bin", "rb");
    if (!f) {
        printf("Fail is not found.\n");
        return 0;
    }
    struct train t;

    switch (section)
    {
    case 5:
        printf("Enter the train type \n");
        char target4[20];
        if (scanf("%s", target4) == 0){
            printf("Error input! \n");
            return 0;
        }
        printf("N  | Number Train | Type Train | Time | Carriages | Type Carriage | Free Place\n");
        printf("-----------------------------------------------------------------------------\n");
        int l = 1;
        while (fread(&t, sizeof(struct train), 1, f) == 1){
            if (!strcmp(target4, t.type_train)) {
                printf("%-2d | %-13d| %-11s| %-6.2lf| %-10d| %-14s| %-10d\n", l,
            t.number_train, t.type_train, t.time_deport,
            t.count_carriage, t.type_carriage, t.count_free_place);
            l++;
            printf("-----------------------------------------------------------------------------\n");
            }
        }
        break;
    case 6:
        printf("Enter the type of carriage \n");
        char target5[20];
        if (scanf("%s", target5) == 0){
            printf("Error input! \n");
            return 0;
        }
        printf("N  | Number Train | Type Train | Time | Carriages | Type Carriage | Free Place\n");
        printf("-----------------------------------------------------------------------------\n");
        int m = 1;
        while (fread(&t, sizeof(struct train), 1, f) == 1){
            if (!strcmp(target5, t.type_carriage)) {
                printf("%-2d | %-13d| %-11s| %-6.2lf| %-10d| %-14s| %-10d\n", m,
            t.number_train, t.type_train, t.time_deport,
            t.count_carriage, t.type_carriage, t.count_free_place);
            m++;
            printf("-----------------------------------------------------------------------------\n");
            }
        }
        break;
    default:
        break;
    }
    fclose(f);
    return 1;
}

int search_time_posts(){
    FILE *f = fopen("f.bin", "rb");
    struct train t;
    short a;
    printf("You want to find: \n 1. The exact time \n 2. The range \n ");
    if (scanf("%hd", &a) == 0){
        printf("Error input! \n");
        return 0;
    }
    switch (a)
    {
    case 1:
        printf("Enter the time \n ");
        double target6;
        if (scanf("%lf", &target6) == 0){
            printf("Error input! \n");
            return 0;
        }
        printf("N  | Number Train | Type Train | Time | Carriages | Type Carriage | Free Place\n");
        printf("-----------------------------------------------------------------------------\n");
        int i = 1;
        while (fread(&t, sizeof(struct train), 1, f) == 1){
            if (t.time_deport == target6) {
                printf("%-2d | %-13d| %-11s| %-6.2lf| %-10d| %-14s| %-10d\n", i,
            t.number_train, t.type_train, t.time_deport,
            t.count_carriage, t.type_carriage, t.count_free_place);
            i++;
            printf("-----------------------------------------------------------------------------\n");
            }
        }
        break;
    case 2:
        printf("Enter the range \n");
        double a, b;
        if (scanf("%lf %lf", &a, &b) != 2){
            printf("Error input! \n");
            return 0;
        }
        printf("N  | Number Train | Type Train | Time | Carriages | Type Carriage | Free Place\n");
        printf("-----------------------------------------------------------------------------\n");
        int j = 1;
        while (fread(&t, sizeof(struct train), 1, f) == 1){
            if ((t.time_deport >= a) && (t.time_deport <= b)) {
                printf("%-2d | %-13d| %-11s| %-6.2lf| %-10d| %-14s| %-10d\n", j,
            t.number_train, t.type_train, t.time_deport,
            t.count_carriage, t.type_carriage, t.count_free_place);
            j++;
            printf("-----------------------------------------------------------------------------\n");
            }
        }
        break;
    
    default:
        break;
    }
    return 1;
}

int search_section(int mark){
    if (mark < 4){
        search_int_posts(mark);
    } else if (mark == 4){
        search_time_posts();
    } else {
        search_str_posts(mark);
    }
    return 1;
}

int int_sort(int mark, int v){
    FILE *f = fopen("f.bin", "rb+");
    FILE *p = fopen("p.bin", "wb");
    struct train t;

    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    int n = fileSize / sizeof(struct train);
    int *arr = malloc(n * sizeof(int));

    int i = 0, j = 0, k = 0;
    switch (mark)
    {
    case 1:
        while (fread(&t, sizeof(struct train), 1, f) == 1){
            arr[i] = t.number_train;
            i++;
        }
        switch (v){
        case 1:
            int_bubble_sort_up(arr, n);
            break;
        case 2:
            int_bubble_sort_down(arr, n);
            break;
        default:
            printf("Error input!");
            free(arr);
            return 0;
        }
        for (int i = 0; i < n; i++){
            fseek(f, 0, SEEK_SET);
            while (fread(&t, sizeof(struct train), 1, f) == 1){
                if (t.number_train == arr[i]){
                    fwrite(&t, sizeof(struct train), 1, p);
                }
            }
        }
        fclose(f);
        fclose(p);

        remove("f.bin");
        rename("p.bin", "f.bin");
        break;
    case 2:
        while (fread(&t, sizeof(struct train), 1, f) == 1){
            arr[j] = t.count_carriage;
            j++;
        }
        switch (v){
        case 1:
            int_bubble_sort_up(arr, n);
            break;
        case 2:
            int_bubble_sort_down(arr, n);
            break;
        default:
            printf("Error input!");
            free(arr);
            return 0;
        }
        for (int i = 0; i < n; i++){
            fseek(f, 0, SEEK_SET);
            while (fread(&t, sizeof(struct train), 1, f) == 1){
                if (t.count_carriage == arr[i]){
                    fwrite(&t, sizeof(struct train), 1, p);
                }
            }
        }
        fclose(f);
        fclose(p);

        remove("f.bin");
        rename("p.bin", "f.bin");
        break;
    case 3:
        while (fread(&t, sizeof(struct train), 1, f) == 1){
            arr[k] = t.count_free_place;
            k++;
        }
        switch (v){
        case 1:
            int_bubble_sort_up(arr, n);
            break;
        case 2:
            int_bubble_sort_down(arr, n);
            break;
        default:
            printf("Error input!");
            free(arr);
            return 0;
        }
        for (int i = 0; i < n; i++){
            fseek(f, 0, SEEK_SET);
            while (fread(&t, sizeof(struct train), 1, f) == 1){
                if (t.count_free_place == arr[i]){
                    fwrite(&t, sizeof(struct train), 1, p);
                }
            }
        }
        fclose(f);
        fclose(p);

        remove("f.bin");
        rename("p.bin", "f.bin");
        break;
    
    default:
        printf("Error input!");
        return 0;
    }

    free(arr);
    return 1;
}

int time_sort(int v){
    FILE *f = fopen("f.bin", "rb+");
    FILE *p = fopen("p.bin", "wb");
    struct train t;

    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    int n = fileSize / sizeof(struct train);
    double *arr = malloc(n * sizeof(double));
    int i = 0;
    while (fread(&t, sizeof(struct train), 1, f) == 1){
            arr[i] = t.time_deport;
            i++;
    }
    switch (v){
    case 1:
        double_bubble_sort_up(arr, n);
        break;
    case 2:
        double_bubble_sort_down(arr, n);
        break;
    default:
        printf("Error input!");
        free(arr);
        return 0;
    }
    for (int i = 0; i < n; i++){
        fseek(f, 0, SEEK_SET);
        while (fread(&t, sizeof(struct train), 1, f) == 1){
            if (t.time_deport== arr[i]){
                fwrite(&t, sizeof(struct train), 1, p);
            }
        }
    }
    fclose(f);
    fclose(p);

    remove("f.bin");
    rename("p.bin", "f.bin");
    free(arr);
    return 1;
}

int str_sort(int mark, int v){
    FILE *f = fopen("f.bin", "rb");
    FILE *p = fopen("p.bin", "wb");

    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    int n = fileSize / sizeof(struct train);
    struct train *arr = malloc(fileSize);
    fread(arr, sizeof(struct train), n, f);
    fclose(f);

    switch (mark)
    {
    case 5:
        switch (v)
        {
        case 1:
            for (int i = 0; i < n-1; i++){
                int flag = 0;
                for (int j = 0; j < n-i-1; j++){
                    if(strcmp(arr[j].type_train, arr[j+1].type_train) > 0){
                            struct train tmp = arr[j];
                            arr[j] = arr[j + 1];
                            arr[j + 1] = tmp;
                            flag = 1;
                    }
                }
                if (!flag) break;
            }
            break;
        case 2:
            for (int i = 0; i < n-1; i++){
                int flag = 0;
                for (int j = 0; j < n-i-1; j++){
                    if(strcmp(arr[j].type_train, arr[j+1].type_train) < 0){
                            struct train tmp = arr[j];
                            arr[j] = arr[j + 1];
                            arr[j + 1] = tmp;
                            flag = 1;
                    }
                }
                if (!flag) break;
            }
            break;
        
        default:
            printf("Error input!");
            free(arr);
            return 0;
        }
        break;
    case 6:
        switch (v)
        {
        case 1:
            for (int i = 0; i < n-1; i++){
                int flag = 0;
                for (int j = 0; j < n-i-1; j++){
                    if(strcmp(arr[j].type_carriage, arr[j+1].type_carriage) > 0){
                            struct train tmp = arr[j];
                            arr[j] = arr[j + 1];
                            arr[j + 1] = tmp;
                            flag = 1;
                    }
                }
                if (!flag) break;
            }
            break;
        case 2:
            for (int i = 0; i < n-1; i++){
                int flag = 0;
                for (int j = 0; j < n-i-1; j++){
                    if(strcmp(arr[j].type_carriage, arr[j+1].type_carriage) < 0){
                            struct train tmp = arr[j];
                            arr[j] = arr[j + 1];
                            arr[j + 1] = tmp;
                            flag = 1;
                    }
                }
                if (!flag) break;
            }
            break;
        default:
            printf("Error input!");
            free(arr);
            return 0;
        }

        break;
        
    default:
        printf("Error input!");
        free(arr);
        return 0;
    }

    fwrite(arr, sizeof(struct train), n, p);
    fclose(p);

    remove("f.bin");
    rename("p.bin", "f.bin");
    free(arr);
    return 1;
}

int sort(int mark, int v){
    if (mark < 4){
        int_sort(mark, v);
    } else if (mark == 4){
        time_sort(v);
    } else {
        str_sort(mark, v);
    }
    return 1;
}

int edit_post(int target){
    FILE *f = fopen("f.bin", "rb+");

    struct train t;
    short flag = 0;
    while (fread(&t, sizeof(struct train), 1, f)){
        if (t.number_train == target){
            flag = 1;
            break;
        }
    }
    // Проверка на наличие редактируемой записи
    if (flag == 0){
        printf("Post is not found \n");
        return 0;
    }
    // Перемещаем курсор на начало записи, которую нужно изменить и запоминаем место
    long int pos = ftell(f);

    
    struct train s;
    struct train *p = &s;
    int nt, cc, cfp;
    double td;
    char tt[20];
    char tc[20];
    printf(ADD_INPUT);
    if (scanf("%d %s %lf %d %s %d", &nt, tt, &td, &cc, tc, &cfp) != 6){
        return 0;
    }
    if (is_alpha_str(tt) || is_alpha_str(tc)){
        printf("Incorrect input! \n");
        return 0;
    }
    if (cc > 15){ // Проверка на число вагонов
        printf("Too many carriages! \n");
        return 0;
    }

    //Выделяем отдельно часы и минуты
    hour = (int)td;
    min = (int)(td-hour)*10;

    if ((hour >= 24) || (min >= 60)){
        printf("Incorrect time format! \n");
        return 0;
    }

    // Записываем данные в структуру
    p->number_train = nt;
    strcpy(p->type_train, tt);
    p->time_deport = td;
    p->count_carriage = cc;
    strcpy(p->type_carriage, tc);
    p->count_free_place = cfp;

    // Проверяем на совпадение номеров
    struct train d;
    while (fread(&d, sizeof(struct train), 1, f) == 1){
        if (d.number_train == s.number_train){
            printf("This number is already taken! \n");
            return 0;
        }
    }

    // Перемещаемся к началу редактируемой записи
    fseek(f, pos - sizeof(struct train), SEEK_SET);
    // Записываем в файл
    fwrite(p, sizeof(struct train), 1, f);
    fclose(f);
    return 1;
}

int read_posts() {
    struct train s;
    FILE *f = fopen("f.bin", "rb");
    if (!f) {
        printf("Fail is not found.\n");
        return 0;
    }

    printf("N  | Number Train | Type Train | Time | Carriages | Type Carriage | Free Place\n");
    printf("-----------------------------------------------------------------------------\n");

    int i = 1;
    while (fread(&s, sizeof(struct train), 1, f) == 1) {
        printf("%-2d | %-13d| %-11s| %-6.2lf| %-10d| %-14s| %-10d\n", i,
            s.number_train, s.type_train, s.time_deport,
            s.count_carriage, s.type_carriage, s.count_free_place);
            i++;
            printf("-----------------------------------------------------------------------------\n");
    }

    fclose(f);
    return 0;
}