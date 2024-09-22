#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


typedef struct users {
    int id;
    char password[15];
    char role[15];
    struct users *next;
} users;


typedef struct complains {
    int id;
    char motive[100];
    char description[500];
    char category[15];
    char status[10];
    char date[30];
    char note[100];
    char usrname[20];
    struct complains *next;
} complains;


/*
void func_create_node_only(users **head) {

    // alocate memory for the new node.
    users *tmp = (users *)malloc(sizeof(users));
    if (!tmp) {
        printf("Memory allocation for the new node has failed!");
        return;
    }
    // initializing elements of the node.
    tmp->id = 0;
    tmp->password[0] = '\0';  // Properly initialize strings
    tmp->role[0] = '\0'; 
    tmp->next = NULL;
    
    // tmp->id = 0;
    // //strcpy(tmp->password, "");
    // strcpy(tmp->role, "");
    // tmp->next = NULL;

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

*/

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


void func_assign_val_to_nodes(users **p, int idd, char pass[], char rol[]) {// func_create_assign_val_to_nodes

    // Memory allocation for the new node/user.
    users *ptr = (users *)malloc(sizeof(users));
    if (!ptr) {
        printf("Memory allocation for the new node has failed!");
        return;
    }

    // node elements initialization with the given data
    ptr->id = idd;
    strcpy(ptr->password, pass);
    strcpy(ptr->role, rol);
    ptr->next = NULL;

    if (*p != NULL) {
        users *t;// a pointer to traverse the linked list. in case there are more than one node in the list
        t = *p;
        while (t->next != NULL) {
            t = t->next;
        }
        t->next = ptr;

    } else {// In case there is no node in the list 
        *p = ptr;
    }
}


int func_pass_check_exist(users *p, char pass[]) {

    while (p->next != NULL) {
        if (0 == strcmp(p->password, pass)) return 1; // strcmp retuns 0 on match
        p = p->next;
    }

    // In case there is one node in the linked list.
    return strcmp(p->password, pass) == 0? 1: -1;
}


void func_display_users(users *head) {

    //if (head != NULL) { //the linked list in not empty
        users *p = head;
        while (p != NULL) {// why not p->next != NULL
            printf("\n\n%d\n\n", p->id);
            printf("\n\n%s\n\n", p->password);
            printf("\n\n%s\n\n", p->role);
            p = p->next;
        }
//} else {

  //  }
}

int func_role_checker(users *pt, int id_box) {
    
    while (pt != NULL) {
        if (pt->id == id_box) {
            if (strcmp(pt->role, "admin") == 0) return 0;
            else if (strcmp(pt->role, "agent") == 0) return 1;
            else return 2; //normal user == client.
        }
        pt = pt->next;
    }
    return -1;//to avoid errors we must retun an int any way
}

void func_manag_users_roles(users *p_head) {

    //Print users list
    users *traverse_ptr = p_head;
    int i = 0;
    int search_id = 0;
    int exist = 1;
    while (traverse_ptr != NULL) {
        printf("\tId  %d: %d\n\n", ++i, traverse_ptr->id);
        traverse_ptr = traverse_ptr->next;
    }

    traverse_ptr = p_head;// to gert back to the first node
    printf("\t\tPlease enter a user id to switch the role to agent: \n");
    scanf("%d", &search_id);
    if (search_id != 0) {
        while (traverse_ptr != NULL) {
            if (traverse_ptr->id == search_id) {
                strcpy(traverse_ptr->role, "agent");
                printf("The user with id %d is now %s\n\n", traverse_ptr->id, traverse_ptr->role);
                exist = 1;
                break;
            }
            traverse_ptr = traverse_ptr->next;
        }
    }
    if (search_id != 0 && exist == 0) {
        printf("\tId not Found.\n");
    }

}


void func_add_complains(complains **p) {

    char usrname[20];
    char des[500];
    char categor[15];
    char moti[100];
    time_t now;

    // Memory allocation for the new node/complain.
    complains *ptr = (complains *)malloc(sizeof(complains));
    if (!ptr) {
        printf("Memory allocation for the new node has failed!");// Handle in the callign func
        return;
    }

    // <<<<<<<<<<<<<<<<<node elements initialization by default>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

     // Seed the random number generator with the current time
    srand(time(0));

    // Generate a random ID between 1000 and 99999 (5-digit ID)
    int complaintID = rand() % 90000 + 10000;

 
    ptr->id = complaintID;//*************************************************************** */
    
    strcpy(ptr->status, "Waiting");
    strcpy(ptr->note, "no note for the moment");

    struct tm *local;
    time(&now); // Get the current time
    local = localtime(&now); // Convert to local time
    strftime(ptr->date, sizeof(ptr->date), "%d-%m-%Y %H:%M:%S", local);

    ptr->next = NULL;
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<, ask thye user to enter data


    if (*p != NULL) {
        complains *t; // a pointer to traverse the linked list. in case there are more than one node in the list
        t = *p;
        while (t->next != NULL) {
            t = t->next;
        }
        t->next = ptr;

    } else {// In case there is no node in the list 
        *p = ptr;
    }
}


void func_display_complains(complains *ptr_hd) {

    complains *p;

    p = ptr_hd;
    printf("\t\tAll complains are list bellow\n");
    while (p != NULL) {
        printf("\n\t\t\t%d\n", p->id);
        printf("\t\t\t%s\n", p->status);
        printf("\t\t\t%s\n", p->date);
        printf("\t\t\t%s\n", p->note);
        p = p->next;
    }
}

void func_admin_menu(users **ptr_head, complains **ptr_head_complains) {


    int opt;

    opt = 0;
    while (1) {
    printf("\t\tWelcome back admin!\n\n\n");
    printf("\tPlease Enter a valid number option from the list bellow:\n");
    printf("\t\t1-> Manage users roles.\n");
    printf("\t\t2-> add complains.\n");
    printf("\t\t3-> Display complains list.\n");
    printf("\t\t4-> Modify a complain.\n");
    printf("\t\t5-> Delete a complain.\n");
    printf("\t\t6-> Search for a complain.\n");
    printf("\t\t7-> Display complains by priority.\n");
    printf("\t\t8-> Okey bye\n");
    printf("\t\t9-> Display complains list.\n");
    printf("\t\t10-> Display complains list.\n");
    printf("\t\t11-> Display complains list.\n");
    printf("\t\t12-> Log out\n\n");
    printf("\t\tEnter your option here:     ");
    scanf("%d", &opt);

    if (opt == 12) return;

    switch (opt) {
        case (1):
            func_manag_users_roles(*ptr_head);
            break;
        case (2):
            func_add_complains(ptr_head_complains);
            break;
       case (3):
            func_display_complains(*ptr_head_complains);
            break;
     /*
        case (1):
            break;
        case (1):
            break;
        case (1):
            break;
        case (1):
            break;
        case (1):
            break;
        case (1):
            break;
        case (1):
            break;
        case (1):
            break;
        case (1):
            break;*/
        default:
            printf("\t\tPlease enter a valid option number.\n\n");        
    }
}
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
    int var_role;
    users *ptr_head; // the head of the linked list
    complains *ptr_head_complains;


    // initializing variables
    option = 0;
    id_found = 0;
    id_box = 0;
    pass_valid = 0;
    pass_box[0] = '\0';
    role_box[0] = '\0';
    num_of_attempts = 3;
    ptr_head = NULL;// y we have to set it to NULL??--------------------------------------------
    ptr_head_complains = NULL;
    is_first_node = 0;
    var_role = 0;




    // creating our first user the admin
    func_assign_val_to_nodes(&ptr_head, 0, "admin", "admin");
    if (!ptr_head) return -1;

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
        goto sw;

sw: 
    switch (option) {
        case (1):
            // we create the first node for the admin
            //func_create_node_only(&ptr_head);

            //func_assign_val_to_nodes(&ptr_head, 0, "admin", "admin");


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
                scanf("%[^\n]", pass_box);//s specifier removed
                getchar();
                printf("\n\n\n");
                pass_valid = func_pass_check(pass_box);
                if (pass_valid == -1) printf("\t\tThe Password is weak Please try again!\n\n");
            } while (pass_valid == -1);

            // Code segment to define the user role.
            //is_first_node = func_is_first_node(ptr_head); // or ptr_head == NULL
            // if (is_first_node == 1) {// we are at the first node so we are  going to be the admin
            //     strcpy(role_box, "admin");
            // } else {
            //     strcpy(role_box, "client");
            // }
            
            // we create another node for other users
            // func_create_node_only(&ptr_head);
            // if (!ptr_head) return -1;
            // func_assign_val_to_nodes(&ptr_head, id_box, pass_box, "client");
            
            func_assign_val_to_nodes(&ptr_head, id_box, pass_box, "client");
            if (!ptr_head) return -1;
        
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
                scanf(" %[^\n]", pass_box);
                getchar();
                printf("\n\n\n");
                pass_valid = func_pass_check_exist(ptr_head, pass_box);

                if (id_found == -1 || pass_valid == -1) {
                    if (num_of_attempts == 0) {
                        printf("\t\tYou cant log in for %d minute", 1);
                        printf("\n\n\n");
                        sleep(3);// becarefull where you run the prgram
                        num_of_attempts = 3;
                        goto main_menu;// Create it. goto menu; || continue ****************************************
                    } else {
                        num_of_attempts--;
                    }
                    printf("\t\tUncorrect log in, Please try again\n\n");
                }
            } while ((id_found == -1 || pass_valid == -1));// it is or not and operator.

            printf("\n\n\n\t\tWelcome back friend\n\n\n"); //+++++++++++++++++++++++++++++++++++++++++++++++++
            var_role = func_role_checker(ptr_head, id_box);
            switch(var_role) {
                case(0)://admin
                    func_admin_menu(&ptr_head, &ptr_head_complains);
                    goto main_menu;
            }
            break;
        case(3):
            // just for the test
            func_display_users(ptr_head);
            return 0;

        default:
            printf("\t\tPlease enter a valid option number\n\n\n");
            goto main_menu;
    }
    return 0;
}
