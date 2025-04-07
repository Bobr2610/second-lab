#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Для isatty() на Unix/Linux
#include "table.h"

/**
 * @brief Функция для сравнения строк
 * 
 * Сравнивает две строки посимвольно и возвращает 0, если строки идентичны,
 * и 1, если строки различаются.
 * 
 * @param s1 Первая строка для сравнения
 * @param s2 Вторая строка для сравнения
 * @return 0, если строки идентичны, 1 в противном случае
 */
int compare(char *s1, char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2) return 1;
        s1++;
        s2++;
    }
    return *s1 == *s2 ? 0 : 1;
}

/**
 * @brief Основная функция программы
 * 
 * Создает таблицу и обрабатывает команды пользователя для работы с таблицей.
 * Поддерживает команды добавления, поиска, вывода и выхода.
 * 
 * @return 0 при успешном завершении
 */
int main() {
    Table table;
    create(&table);
    
    // Проверка, является ли stdin терминалом или файлом
    int is_interactive = isatty(fileno(stdin));
  
    printf("Available commands:\n");
    printf("add key value - add new element (max 6 chars)\n");
    printf("sort - sort table\n");
    printf("search key - find element\n");
    printf("print - show table\n");
    printf("exit - quit program\n\n");
    
    char command[256];
    char key[KEY_SIZE];
    char value[256];
    
    while (1) {
        // Выводить приглашение только в интерактивном режиме
        if (is_interactive) {
            printf("Enter command: ");
        }
        
        // Проверка, достигнут ли конец файла (EOF)
        if (scanf("%s", command) == EOF) {
            break;
        }
        
        // Вывести команду, если не в интерактивном режиме
        if (!is_interactive) {
            printf("Command: %s", command);
        }
        
        if (compare(command, "add") == 0) {
            scanf("%6s", key);
            
            // Read the rest of the line for value (including spaces)
            char buffer[256];
            scanf(" %[^\n]", buffer);
            
            if (!is_interactive) {
                printf(" %s %s\n", key, buffer);
            }
            add(&table, key, buffer);
        } 
        else if (compare(command, "search") == 0) {
            scanf("%6s", key);
            if (!is_interactive) {
                printf(" %s\n", key);
            }
            char *result = search(&table, key);
            if (result) {
                printf("Found: %s\n", result);
            } else {
                printf("Not found\n");
            }
        } 
        else if (compare(command, "print") == 0) {
            if (!is_interactive) {
                printf("\n");
            }
            print(&table);
        }
        else if (compare(command, "exit") == 0) {
            if (!is_interactive) {
                printf("\n");
            }
            break;
        }
        else if (compare(command, "sort") == 0) {
            if (!is_interactive) {
                printf("\n");
            }
            sort(&table);
        }
        else {
            if (!is_interactive) {
                printf("\n");
            }
            printf("Unknown command\n");
        }
    }
    
    destroy(&table);
    return 0;
}
