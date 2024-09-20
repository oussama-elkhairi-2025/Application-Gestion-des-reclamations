#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct users {
    int id;
    char password[15];
    char role[15];
    struct users *next;
} users;

users* func_create_node(users *p) {

    // alocate memory for a new node.
    users *tmp = (users *)malloc(sizeof(users));
    if (!tmp) {
        printf("Memory allocation has failed!");
        return NULL;
    }
    

}

int main() {
    int option;
    int id_found;  
    int pass_found;    
    int num_of_attempts;
    users *ptr_head;

    // initializing variables
    option = 0;
    id_found = 0;
    pass_found = 0;
    num_of_attempts = 3;
    ptr_head = NULL;

    // The first menu display
    printf("\tPlease Enter a valid number option from the list bellow:\n");
    printf("\t\t1-> Sign up.\n");
    printf("\t\t2-> Sign in.\n");
    printf("\t\t3-> Exit.\n\n");
    printf("\t\tEnter your option here:   ");
    
    // Take the input from the user
    scanf("%d", &option);

    printf("\n\n\n");

    switch (option) {
        case (1):
            if (!(ptr_head = func_create_add_node(ptr_head))) return -1;

    }
    return 0;
}