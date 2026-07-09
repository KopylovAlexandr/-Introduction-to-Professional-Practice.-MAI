#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_WORD     30
#define MAX_LEN      10
#define ERROR   "ERROR: The format is incorrect. Correct format: NNN,NNNN,NN."
#define ERROR_2   "ERROR: The word you entered is too long, maximum 10."
#define ERROR_3  "ERROR: Too many words entered, maximum 30."


bool is_empty(const char *str)
{
    // Проверка на пустую строку
    return str == NULL || strlen(str) == 0;
}

bool invalid_str(const char *str)
{
    // Функция проверяет, если в строке лишние символы
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ',' && !isalnum(str[i])) {
            return true;
        }
    }
    return false;
}


int main(void){
    char str[MAX_WORD*11 + 50]; //Вводимая строка
    char *separ_str[MAX_WORD]; // Указатель на массив со словами 
    int counter[MAX_WORD] = {0}; //Массив с частотой слов


    // Проверка на правильность ввода в целом 
    if (scanf("%s", str) == 0){
        printf(ERROR);
        return 0;
    }

    size_t len_str = strlen(str); // Длина строки
    char last_char = str[len_str - 1]; //Последний символ

    // Проверка на наличие точки
    if (last_char != '.'){
        printf(ERROR);
    }
    str[len_str - 1] = '\0'; // Заменяем точку на конец строки


    //Проверка на посторонние символы
    if (invalid_str(str)) {
        printf(ERROR);
        return 0;
    }


    const char del[] = ",";
    int word_count = 0; //Счетчик
    char *token = strtok(str, del);

    // Запись слов в массив
    while (token != NULL && word_count < MAX_WORD) {
        if (strlen(token) > MAX_LEN) {
            // Проверка длины слова
            printf(ERROR_2);
            return 0;
        }
        
        separ_str[word_count] = token;
        word_count++;
        token = strtok(NULL, del);
    }


    if (word_count > MAX_WORD) {
        // Проверка на превышение слов
        printf(ERROR_3);
        return 0;
    }
    // Вывод слов
    // for (int i = 0; i < word_count; i++){
    //     printf("%s \n", separ_str[i]);
    // }
    
    // Проверка на уникальность
    for (int i = 0; i < word_count; i++) {
        int count = 0;
        for (int j = 0; j < word_count; j++) {
            if (strcmp(separ_str[i], separ_str[j]) == 0) {
                count++;
            }
        }
        counter[i] = count;
    }
    
    for (int i = 0; i < word_count; i++){
        if (counter[i] == 1){
            printf("%s ", separ_str[i]);
        }
    }

    return 0;
}
