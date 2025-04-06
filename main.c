#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  
    printf("Available commands:\n");
    printf("add key value - add new element (max 6 chars)\n");
    printf("search key - find element\n");
    printf("print - show table\n");
    printf("exit - quit program\n\n");
    
    char command[256];
    char key[KEY_SIZE];
    char value[256];
    
    while (1) {
        printf("Enter command: ");
        // Сброс буфера вывода для корректной работы при перенаправлении ввода
        fflush(stdout);
        
        // Проверка на достижение конца файла
        if (scanf("%s", command) == EOF) {
            break;
        }
        
        if (compare(command, "add") == 0) {
            scanf("%6s %255s", key, value);
            add(&table, key, value);
        } 
        else if (compare(command, "search") == 0) {
            scanf("%6s", key);
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
