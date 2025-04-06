#include <stdio.h>
#include <stdlib.h>
#include "table.h"

// Function for string comparison
int compare(char *s1, char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2) return 1;
        s1++;
        s2++;
    }
    return *s1 == *s2 ? 0 : 1;
}

int main() {
    Table table;
    create(&table);
  
    printf("Available commands:\n");
    printf("add key value - add new element\n");
    printf("search key - find element\n");
    printf("print - show table\n");
    printf("exit - quit program\n\n");
    
    char command[256];
    int key;
    char value[256];
    
    while (1) {
        printf("Enter command: ");
        scanf("%s", command);
        
        if (compare(command, "add") == 0) {
            scanf("%d %s", &key, value);
            add(&table, key, value);
        } 
        else if (compare(command, "search") == 0) {
            scanf("%d", &key);
            char *result = search(&table, key);
            if (result) {
                printf("Found: %s\n", result);
            } else {
                printf("Not found\n");
            }
        } 
        else if (compare(command, "print") == 0) {
            print(&table);
        }
        else if (compare(command, "exit") == 0) {
            break;
        }
        else {
            printf("Unknown command\n");
        }
    }
    
    destroy(&table);
    return 0;
}
