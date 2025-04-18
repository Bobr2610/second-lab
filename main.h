#ifndef MAIN_H
#define MAIN_H

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
int compare(char *s1, char *s2);

#endif