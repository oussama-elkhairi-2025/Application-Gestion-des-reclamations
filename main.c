#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include <string.h>




typedef struct users {
    int id;
    char password[15];
    char role[15];
    struct users *next;
} users;


void func_create_node_only(users **head) {/* ********************************************** */

    // alocate memory for the new node.
    users *tmp = (users *)malloc(sizeof(users));
    if (!tmp) {
        printf("Memory allocation for the new node has failed!");
        return;
    }
    // initializing elements of the node.
    tmp->id = 0;
    strcpy(tmp->password, "\0");
    strcpy(tmp->role, "\0");
    tmp->next = NULL;

    if (*head != NULL) {   //if head is NULL, it is an empty list
        // check if there are nodes in the list
        // we need a ptr to traverse the list
        users *t = NULL;
        t = *head;
        while (t->next != NULL) {
            t = t->next;
        }
        t->next = tmp;
    } else {//if head is NULL, it is an empty list
        //Assigning the newly made node to head
        *head = tmp;
    }
    return;
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


int func_is_first_node(users *p) {

    int size;

    size = 1;
    while (p->next != NULL) {
        size++;
        p = p->next;
    }
    return size;
}


void func_assign_val_to_nodes(users **p, int idd, char pass[], char rol[]) {

    if (*p != NULL) {
        users *t;
        t = *p;
        while (t->next != NULL) {
            t = t->next;
        }
        t->id = idd;
        strcpy(t->password, pass);
        strcpy(t->role, rol);
    } else {
        *p = (users *)malloc(sizeof(users));
        (*p)->id = idd;
        strcpy((*p)->password, pass);
        strcpy((*p)->role, rol);
        (*p)->next = NULL;
    }
}


int func_pass_check_exist(users *p, char pass[]) {

    while (p->next != NULL) {
        if (1 == strcmp(p->password, pass)) return 1;
        p = p->next;
    }

    // In case there is one node in the linked list.
    return strcmp(p->password, pass) == 1? 1: -1;
}

int main() {

    int option;
    int id_found;
    int id_box;
    char pass_box[20];
    char role_box[10];
    int pass_valid;    
    int num_of_attempts;
    int is_first_node;
    users *ptr_head; // the head of the linked list


    // initializing variables
    option = 0;
    id_found = 0;
    id_box = 0;
    pass_valid = 0;
    pass_box[0] = '\0';
    role_box[0] = '\0';
    num_of_attempts = 3;
    ptr_head = NULL;
    is_first_node = 0;

    main_menu:
        // The first menu display
        printf("\t\tThis is FIRST MENU BABY \n\n\n");
        printf("\tPlease Enter a valid number option from the list bellow:\n");
        printf("\t\t1-> Sign up.\n");
        printf("\t\t2-> Sign in.\n");
        printf("\t\t3-> Exit.\n\n");
        printf("\t\tEnter your option here: ");

        // Take the input from the user
        scanf("%d", &option);
        /*
            why the getchar after thr scanf?
            scanf and getchar can be tricky to mix. scanf leaves the newline character in the input after reading an integer. 
            A following getchar will read that newline character.There's a few ways around this. One way is to use fgets and sscanf 
            instead of scanf to read in an entire line. Another way is to clear the input buffer after scanf.
        */

        getchar();
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

            // Code segment to define the user role 
            is_first_node = func_is_first_node(ptr_head); // or ptr_head == NULL
            if (is_first_node == 1) {// we are at the first node so we are  going to be the admin
                strcpy(role_box, "admin");
            } else {
                strcpy(role_box, "client");
            }
            func_assign_val_to_nodes(&ptr_head, id_box, pass_box, role_box);
        
            printf("\t\tYour account has been succefully created");
            printf("\n\n\n");

            goto main_menu;/****************************************************** */

        case (2):
            do {
                printf("\t\tPlease enter a number id: ");
                scanf("%d", &id_box);
                getchar();
                printf("\n\n\n");
                id_found = func_id_check(ptr_head, id_box);

                printf("\t\tPlease enter a valid password:  ");
                scanf("%[^\n]s", pass_box);
                getchar();
                printf("\n\n\n");
                pass_valid = func_pass_check_exist(ptr_head, pass_box);

                if (id_found == -1 || pass_valid == -1) {
                    if (num_of_attempts == 0) {
                        printf("\t\tYou cant log in for %d minute", 1);
                        printf("\n\n\n");
                        sleep(60000);
                        num_of_attempts = 3;
                        goto main_menu;// Create it. goto menu; || continue ****************************************
                    } else {
                        num_of_attempts--;
                    }
                    printf("\t\tUncorrect log in, Please try again");
                }
            } while ((id_found == -1 && pass_valid == -1));
            printf("\t\tWelcome back friend");
            
    }
    return 0;
} 







