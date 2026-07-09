#include <stdio.h>
#include <string.h>
#include <D:\ВУЗ\VPD\Lab4\app_del_ed.c> // Добавление, удаление и редактирование


#define MAIN_MENU \
    "Select an action: \n \n" \
    "1. Add a post \n " \
    "2. Delete entry \n " \
    "3. Search \n " \
    "4. Sort \n " \
    "5. Edit \n " \
    "6. Show current schedule \n"

#define SEARCH_AREA \
    "Select your search area: \n" \
    "1. Number train \n" \
    "2. Count carriages \n" \
    "3. Count free place \n" \
    "4. Time deport \n" \
    "5. Type train \n" \
    "6. Type carriages \n"

#define SORT_AREA \
    "Select your sort area: \n" \
    "1. Number train \n" \
    "2. Count carriages \n" \
    "3. Count free place \n" \
    "4. Time deport \n" \
    "5. Type train \n" \
    "6. Type carriages \n"


int menu(){
    int a;
    int q;
    printf(MAIN_MENU);
    if (scanf("%d", &a) == 0){
        printf("Error input!");
        return 0;
    }
    switch (a)
    {
    case 1:{
        if (add_post() == 0){
            printf("Error input!");
            return 0;
        }
        break;
    }
    case 2:
        printf("Enter train number \n");
        if (scanf("%d", &q) == 0){
            printf("Error input!");
            return 0;
        }
        delete_post(q);
        break;
    case 3:
        printf(SEARCH_AREA);
        if (scanf("%d", &q) == 0){
            printf("Error input!");
            return 0;
        }
        if ((q > 6) || (q < 0)){
            printf("Error input!");
            return 0;
        }
        search_section(q);
        break;
    case 4:
        printf(SORT_AREA);
        if (scanf("%d", &q) == 0){
            printf("Error input!");
            return 0;
        }
        if ((q > 6) || (q < 0)){
            printf("Error input!");
            return 0;
        }
        printf("Select a sorting method \n 1. Up \n 2. Down \n ");
        int v;
        if (scanf("%d", &v) == 0){
            printf("Error input!");
            return 0;
        }
        sort(q, v);
        break;
    case 5:
        printf("Enter train number \n");
        if (scanf("%d", &q) == 0){
            printf("Error input!");
            return 0;
        }
        edit_post(q);
        break;
    case 6:{
        read_posts();
        break;
    }
    default:
        printf("Error input!");
        break;
    }
    return 0;
}


int main(){
    menu();
    return 0;
}