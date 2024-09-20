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



void func_create_node_only(users **head) {

    // alocate memory for the new node. 
    users *tmp = (users *)malloc(sizeof(users));
    if (!tmp) {
        printf("Memory allocation for the new node has failed!");
        return NULL;
    }

    // initializing elements of the node
    tmp->id = 0;
    strcpy(tmp->password, "\0");
    strcpy(tmp->role, "\0");
    tmp->next = NULL;
    // assigning newly made node to head
    *head = tmp;
}


int func_id_check(users *p, int id_value_entered) {

    while (p->next != NULL) {
        if (p->id == id_value_entered) return 1;
        p = p->next;
    }

    return p->id == id_value_entered: 1; -1;
}


int main() {
    int option;
    int id_found;
    int id_box;
    int pass_found;    
    int num_of_attempts;
    users *ptr_head; // the head of the linked list

    // initializing variables
    option = 0;
    id_found = 0;
    id_box = 0;
    pass_found = 0;
    num_of_attempts = 3;
    ptr_head = NULL;

    // The first menu display
    printf("\tPlease Enter a valid number option from the list bellow:\n");
    printf("\t\t1-> Sign up.\n");
    printf("\t\t2-> Sign in.\n");
    printf("\t\t3-> Exit.\n\n");
    printf("\t\tEnter your option here: ");
    
    // Take the input from the user
    scanf("%d", &option);

    printf("\n\n\n");

    switch (option) {
        case (1):
            func_create_node_only(&ptr_head);
            if (!ptr_head) return -1;
            do {
                printf("\t\tPlease enter a number id: ");
                scanf("%d", &id_box);
                printf("\n\n\n");
                id_found = func_id_check(ptr_head, id_box);
                if (id_found == 1)  printf("\t\tId is already taken Please try again!");
            } while (id_found == 1);
    }
    return 0;
} 