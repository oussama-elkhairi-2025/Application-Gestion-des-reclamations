
#include <stdio.h>

typedef struct users {
    int id;
    char password[50];
    char role[10];
} users;


int main() {
    int option;
    int id_found;       //id_valid
    int pass_found;     //pass_valid
    int num_of_attempts; 

    // The first menu display
    printf("\tPlease Enter a valid number option from the list bellow:\n");
    printf("\t\t1-> Sign up.\n");
    printf("\t\t2-> Sign in.\n");
    printf("\t\t3-> Exit.\n\n");
    printf("\t\tEnter your option here:   ");
    
    // Take the input
    scanf("%d", &option);
    printf("\n\n\n");

    switch (option) {
        case (1):
            
    }
    return 0;
}