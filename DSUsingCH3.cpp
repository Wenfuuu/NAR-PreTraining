#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int menu(){
    int input = 0;
    while(input < 1 || input > 4){
        system("cls");
        printf("1. View Book List\n");
        printf("2. Add Book\n");
        printf("3. Remove Book\n");
        printf("4. Exit\n");
        printf(">> ");
        scanf("%d", &input); getchar();
    }
    return input;
}

void swap(char a[], char b[]){
    char temp[100];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortAscend(char id[][10], char name[][20], char title[][100], int price[], int size){
    for(int i = 0; i < size-1; i++){
        for(int j = 0; j < size-i-1; j++){
            if(strcmp(name[j], name[j+1]) > 0){
                swap(id[j], id[j+1]);
                swap(name[j], name[j+1]);
                swap(title[j], title[j+1]);
                swap(&price[j], &price[j+1]);
            }else if(strcmp(name[j], name[j+1]) == 0){
                if(price[j] > price[j+1]){
                    swap(id[j], id[j+1]);
                    swap(name[j], name[j+1]);
                    swap(title[j], title[j+1]);
                    swap(&price[j], &price[j+1]);
                }
            }
        }
    }
}

void sortDescend(char id[][10], char name[][20], char title[][100], int price[], int size){
    for(int i = 0; i < size-1; i++){
        for(int j = 0; j < size-i-1; j++){
            if(strcmp(name[j], name[j+1]) < 0){
                swap(id[j], id[j+1]);
                swap(name[j], name[j+1]);
                swap(title[j], title[j+1]);
                swap(&price[j], &price[j+1]);
            }else if(strcmp(name[j], name[j+1]) == 0){
                if(price[j] < price[j+1]){
                    swap(id[j], id[j+1]);
                    swap(name[j], name[j+1]);
                    swap(title[j], title[j+1]);
                    swap(&price[j], &price[j+1]);
                }
            }
        }
    }
}

void addBook(char id[], char name[], char title[], int price){
    FILE *fptr = fopen("data.txt", "a");

    fprintf(fptr, "%s#%s#%s#%d\n", id, name, title, price);

    fclose(fptr);
}

int searchId(char id[][10], char inputId[], int size){
    for(int i = 0; i < size; i++){
        if(strcmp(id[i], inputId) == 0){
            return i;
        }
    }
    return -1;
}

void deleteBook(char id[][10], char name[][20], char title[][100], int price[], int idx, int size){
    for(int i = idx; i < size-1; i++){
        strcpy(id[i], id[i+1]);
        strcpy(name[i], name[i+1]);
        strcpy(title[i], title[i+1]);
        price[i] = price[i+1];
    }
}

void updateFile(char id[][10], char name[][20], char title[][100], int price[], int size){
    FILE *fptr = fopen("data.txt", "w");

    for(int i = 0; i < size; i++){
        fprintf(fptr, "%s#%s#%s#%d\n", id[i], name[i], title[i], price[i]);
    }

    fclose(fptr);
}

int main(){
    
    srand(time(0));
    FILE *fp = fopen("data.txt", "r");

    char id[1000][10];
    char name[1000][20];
    char title[1000][100];
    int price[1000];
    char sort[100];
    int idx;

    while(true){
        rewind(fp);
        idx = 0;
        sort[0] = '0';
        while(!feof(fp)){
            fscanf(fp, "%[^#]#%[^#]#%[^#]#%d\n", id[idx], name[idx], title[idx], &price[idx]);
            idx++;
        }
        int input = 0;
        input = menu();
        // fseek(fp, 0, SEEK_END);
        // int size = ftell(fp);
        switch(input){
        case 1:
            system("cls");
            if(id[0][0] == '\0') {
                printf("Book list is currently empty...\n");
		        printf("Press enter to go back...\n");
            }else{
                while(strcmp(sort, "9") != 0){
                    system("cls");
                    if(strcmp(sort, "0") == 0){
                        sortAscend(id, name, title, price, idx);
                    }else{
                        sortDescend(id, name, title, price, idx);
                    }
                    printf("\nSorted by Author & Price\n\n");
                    for(int i = 0; i < 93; i++){
                        printf("=");
                    }
                    printf("\n");
                    printf("| %-10s | %-20s | %-35s | %-15s |\n", "ID", "Author", "Title", "Price");
                    for(int i = 0; i < 93; i++){
                        printf("=");
                    }
                    printf("\n");
                    for(int i = 0; i < idx; i++){
                        printf("| %-10s | %20s | %35s | %15d |\n", id[i], name[i], title[i], price[i]);
                    }
                    for(int i = 0; i < 93; i++){
                        printf("=");
                    }
                    printf("\n");
                    if(strcmp(sort, "0") == 0){
                        printf("\n%91s\n", "Sort: ASCENDING");
                    }else{
                        printf("\n%91s\n", "Sort: DESCENDING");
                    }
                    printf("[0]: Ascending\n");
                    printf("[1]: Descending\n");
                    printf("[9]: Back\n\n");
                    printf(">> ");
                    scanf("%s", sort);
                }
            }
            getchar();
        break;
        case 2:
            system("cls");
            char ids[10];
            sprintf(ids, "%s%d%d%d", "BOOK", rand()%10, rand()%10, rand()%10);
            char names[100];
            char titles[100];
            int prices;
            do{
                printf("Input author's name [ >= 4 characters & <= 18 characters]: ");
                scanf("%s", names); getchar();
                if(strlen(names) < 4 || strlen(names) > 18){
                    printf("Author's name must be [ >= 4 characters & <= 18 characters]...\n\n");
                }
            }while(strlen(names) < 4 || strlen(names) > 18);
            do{
                printf("Input book's title [ must be filled ]: ");
                scanf("%[^\n]", titles); getchar();
                if(titles[0] == '\0'){
                    printf("Book's title must be filled...\n\n");
                }
            }while(titles[0] == '\0');
            do{
                printf("Input book's price [ >= 500 ]: ");
                scanf("%d", &prices); getchar();
                if(prices < 500){
                    printf("Book's price must be more or equals to 500...\n\n");
                }
            }while(prices < 500);
            addBook(ids, names, titles, prices);
            system("cls");
            printf("Newly added book's details:\n");
            printf("ID\t: %s\n", ids);
            printf("Author\t: %s\n", names);
            printf("Title\t: %s\n", titles);
            printf("Price\t: %d\n\n", prices);
            printf("Press enter to continue...\n");
            getchar();
        break;
        case 3:
            system("cls");
            char inputId[100];
            int exist;
            inputId[0] = '\0';
            exist = 0;
            if(id[0][0] == '\0') {
                printf("Book list is currently empty...\n");
		        printf("Press enter to go back...\n");
            }else{
                while(strcmp(inputId, "9") != 0){
                    system("cls");
                    rewind(fp);
                    idx = 0;
                    while(!feof(fp)){
                        fscanf(fp, "%[^#]#%[^#]#%[^#]#%d\n", id[idx], name[idx], title[idx], &price[idx]);
                        idx++;
                    }
                    sortAscend(id, name, title, price, idx);
                    printf("\nSorted by Author & Price [ASC]\n\n");
                    for(int i = 0; i < 93; i++){
                        printf("=");
                    }
                    printf("\n");
                    printf("| %-10s | %-20s | %-35s | %-15s |\n", "ID", "Author", "Title", "Price");
                    for(int i = 0; i < 93; i++){
                        printf("=");
                    }
                    printf("\n");
                    for(int i = 0; i < idx; i++){
                        printf("| %-10s | %20s | %35s | %15d |\n", id[i], name[i], title[i], price[i]);
                    }for(int i = 0; i < 93; i++){
                        printf("=");
                    }
                    printf("\n");
                    printf("\n[9]: Back\n");
                    printf("Remove Book [ e.g. BOOK452 ]: ");
                    scanf("%s", inputId); getchar();
                    if(strcmp(inputId, "9") != 0){
                        exist = searchId(id, inputId, idx);
                        if(exist < 0){
                            printf("Invalid Book ID...\n\n");
                            getchar();
                        }else{
                            deleteBook(id, name, title, price, exist, idx);
                            updateFile(id, name, title, price, idx-1);
                            // idx -= 1;
                        }
                    }
                }
            }
        break;
        case 4:
            system("cls");
            printf("     Breaking and Overcoming Challenges\n");
            printf("   Through Courage Hardwork and Persistence\n");
            printf("         ~~ Bluejackets 23-1 ~~\n");
            return 0;
        break;
        }
    }
    
    fclose(fp);

    return 0;
}