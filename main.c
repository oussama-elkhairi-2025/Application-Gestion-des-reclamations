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
    return p->id == id_value_entered? 1: -1;
}





int func_pass_check(char pass[]) {

    int len;
    int lower_case;
    int upper_case;
    int num;
    int special_char;

    lower_case = 0;
    upper_case = 0;
    num = 0;
    special_char = 0;

    for (len = 0; pass[len] != '\0'; len++) {
        if (pass[len] >= 65 && pass[len] <= 90) {//uppercase
            upper_case = 1;
            continue;
        } else if (pass[len] >= 97 && pass[len] <=  122) {//lowercase
            lower_case = 1;
            continue;
        } else if (pass[len] >= 48 && pass[len] <=  57) {//num
            num = 1;
            continue;
        } else if ((pass[len] >= 32 && pass[len] <= 47) || (pass[len] >= 58 && pass[len] <= 64) || (pass[len] >= 91 && pass[len] <= 96) || (pass[len] >= 123 && pass[len] <= 126)) {//special char
            special_char = 1;
            continue;
        }
    }

    if ((len >= 8) && (lower_case == 1) && (upper_case == 1) && (num == 1) && (special_char == 1)) return 1;
    return -1;
}


int main() {

    int option;
    int id_found;
    int id_box;
    char pass_box[20];
    int pass_valid;    
    int num_of_attempts;
    users *ptr_head; // the head of the linked list


    // initializing variables
    option = 0;
    id_found = 0;
    id_box = 0;
    pass_valid = 0;
    pass_box[0] = '\0';
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
                getchar();
                printf("\n\n\n");
                id_found = func_id_check(ptr_head, id_box);
                if (id_found == 1)  printf("\t\tId is already taken Please try again!\n\n");
            } while (id_found == 1);
            // capturing the password.
            do {
                printf("\t\tPlease enter a valid password:  ");
                scanf("%[^\n]s", pass_box);
                getchar();
                printf("\n\n\n");
                pass_valid = func_pass_check(pass_box);
                if (pass_valid == -1) printf("\t\tThe Password is weak Please try again!\n\n");
            } while (pass_valid == -1);

    }
    return 0;
} 