#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Создает новую таблицу
 * 
 * Инициализирует таблицу с минимальным количеством элементов.
 * Устанавливает пустые значения для всех элементов.
 * 
 * @param t Указатель на таблицу для инициализации
 */
void create(Table *t) {
    t->size = 0;
    
    // Инициализация с минимальным количеством элементов
    for (int i = 0; i < MIN_SIZE; i++) {
        t->data[i].key[0] = '\0';
        t->data[i].value[0] = '\0';
    }
    
    // Установка минимального размера
    t->size = MIN_SIZE;
}

/**
 * @brief Освобождает ресурсы, занятые таблицей
 * 
 * Сбрасывает размер таблицы в 0.
 * 
 * @param t Указатель на таблицу для уничтожения
 */
void destroy(Table *t) {
    t->size = 0;
}

/**
 * @brief Добавляет новый элемент в таблицу
 * 
 * Добавляет пару ключ-значение в таблицу, если есть свободное место.
 * Обеспечивает безопасное копирование строк с ограничением длины.
 * 
 * @param t Указатель на таблицу
 * @param key Ключ для добавления (строка не более 6 символов)
 * @param value Значение для добавления
 */
void add(Table *t, const char *key, const char *value) {
    if (t->size < MAX_SIZE) {
        // Обеспечение, что ключ не длиннее KEY_SIZE-1
        strncpy(t->data[t->size].key, key, KEY_SIZE-1);
        t->data[t->size].key[KEY_SIZE-1] = '\0';
        
        // Копирование значения и добавление терминатора
        strncpy(t->data[t->size].value, value, 255);
        t->data[t->size].value[255] = '\0';
        
        t->size++;
    } else {
        printf("Table is full, cannot add more elements\n");
    }
}

/**
 * @brief Функция для сортировки и слияния двух отсортированных подмассивов
 * 
 * Функция сортирует и объединяет два подмассива в один отсортированный массив.
 * Это ключевая часть алгоритма "Простое двухпоточное слияние".
 * 
 * @param t Указатель на таблицу
 * @param temp Временный массив для хранения результата слияния
 * @param left Индекс начала первого подмассива
 * @param mid Индекс конца первого подмассива
 * @param right Индекс конца второго подмассива
 */
/**
 * @brief Проверяет, является ли строка числом
 * 
 * @param str Строка для проверки
 * @return 1 если строка - число, 0 в противном случае
 */
int is_numeric(const char *str) {
    // Пустая строка не является числом
    if (*str == '\0')
        return 0;
    
    // Проверяем каждый символ
    while (*str) {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

/**
 * @brief Сравнивает два ключа с учетом их типа (числовой или строковый)
 * 
 * @param key1 Первый ключ
 * @param key2 Второй ключ
 * @return Отрицательное число если key1 < key2, 0 если равны, положительное если key1 > key2
 */
int compare_keys(const char *key1, const char *key2) {
    // Проверяем, являются ли оба ключа числами
    int is_num1 = is_numeric(key1);
    int is_num2 = is_numeric(key2);
    
    // Если оба ключа - числа, сравниваем их как числа
    if (is_num1 && is_num2) {
        int num1 = atoi(key1);
        int num2 = atoi(key2);
        return num1 - num2;
    }
    
    // В противном случае используем лексикографическое сравнение
    return strcmp(key1, key2);
}

void merge(Table *t, Entry *temp, int left, int mid, int right) {
    int i = left;    // Индекс для левого подмассива
    int j = mid + 1; // Индекс для правого подмассива
    int k = left;    // Индекс для временного массива
    
    // Слияние двух подмассивов
    while (i <= mid && j <= right) {
        // Сравниваем ключи с учетом их типа (числовой или строковый)
        printf("Comparing keys: '%s' and '%s'\n", t->data[i].key, t->data[j].key);
        if (compare_keys(t->data[i].key, t->data[j].key) <= 0) {
            temp[k] = t->data[i];
            i++;
        } else {
            temp[k] = t->data[j];
            j++;
        }
        k++;
    }
    
    // Копирование оставшихся элементов из левого подмассива
    while (i <= mid) {
        temp[k] = t->data[i];
        i++;
        k++;
    }
    
    // Копирование оставшихся элементов из правого подмассива
    while (j <= right) {
        temp[k] = t->data[j];
        j++;
        k++;
    }
    
    // Копирование из временного массива обратно в исходный массив
    for (i = left; i <= right; i++) {
        t->data[i] = temp[i];
    }
}

/**
 * @brief Рекурсивная функция сортировки слиянием
 * 
 * Реализует алгоритм "Простое двухпоточное слияние" путем рекурсивного
 * разделения массива на две части, сортировки каждой части и последующего
 * слияния отсортированных частей.
 * 
 * @param t Указатель на таблицу
 * @param temp Временный массив для хранения промежуточных результатов
 * @param left Индекс начала сортируемого участка
 * @param right Индекс конца сортируемого участка
 */
void merge_sort_recursive(Table *t, Entry *temp, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        
        // Сортировка первой и второй половины
        merge_sort_recursive(t, temp, left, mid);
        merge_sort_recursive(t, temp, mid + 1, right);
        
        // Слияние отсортированных половин
        merge(t, temp, left, mid, right);
    }
}

/**
 * @brief Сортирует таблицу методом "Простое двухпоточное слияние"
 * 
 * Эта функция инициализирует временный массив и запускает рекурсивный
 * алгоритм сортировки слиянием. Алгоритм имеет сложность O(n log n)
 * и является стабильным (сохраняет относительный порядок равных элементов).
 * 
 * @param t Указатель на таблицу для сортировки
 */
void merge_sort(Table *t) {
    // Создаем временную таблицу для хранения только непустых элементов
    Table temp_table;
    create(&temp_table);
    temp_table.size = 0;
    
    // Копируем только непустые элементы в временную таблицу
    for (int i = 0; i < t->size; i++) {
        if (t->data[i].key[0] != '\0') {
            add(&temp_table, t->data[i].key, t->data[i].value);
        }
    }
    
    // Выделяем память для временного массива для сортировки
    Entry *temp = (Entry *)malloc(temp_table.size * sizeof(Entry));
    if (temp == NULL) {
        printf("Memory allocation error\n");
        return;
    }
    
    // Сортируем только непустые элементы
    merge_sort_recursive(&temp_table, temp, 0, temp_table.size - 1);
    
    // Копируем отсортированные элементы обратно в исходную таблицу
    t->size = 0;
    for (int i = 0; i < temp_table.size; i++) {
        add(t, temp_table.data[i].key, temp_table.data[i].value);
    }
    
    free(temp);
    destroy(&temp_table);
}

/**
 * @brief Ищет элемент в таблице по ключу
 * 
 * Сортирует таблицу методом слияния и выполняет бинарный поиск по ключу.
 * Бинарный поиск имеет сложность O(log n) и работает только на отсортированном массиве.
 * 
 * @param t Указатель на таблицу
 * @param key Ключ для поиска
 * @return Указатель на найденное значение или NULL, если элемент не найден
 */
char* search(Table *t, const char *key) {
    
    // Бинарный поиск
    int left = 0, right = t->size - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = compare_keys(t->data[mid].key, key);
        
        if (cmp == 0) {
            return t->data[mid].value;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return NULL;
}

/**
 * @brief Выводит содержимое отсортировнной таблицы
 * 
 * Печатает все непустые элементы таблицы в формате "ключ: значение".
 * 
 * @param t Указатель на таблицу для вывода
 */
void print(Table *t) {

    for (int i = 0; i < t->size; i++) {
        if (t->data[i].key[0] != '\0') {  // Вывод только непустых элементов
            printf("%s: %s\n", t->data[i].key, t->data[i].value);
        }
    }
}


/**
 * @brief Сортирует и выводит содержимое несортированной и отсортировнной таблицы
 * 
 * Печатает все непустые элементы таблицы в формате "ключ: значение".
 * 
 * @param t Указатель на таблицу для вывода
 */
void sort(Table *t) {
    
    printf("Before sorting:\n");
    print(t);  // Вывод неотсортированной таблицы
    // Сортировка таблицы
    merge_sort(t);
    printf("After sorting:\n");
    print(t);  // Вывод отсортированной таблицы
}
