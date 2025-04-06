#ifndef TABLE_H
#define TABLE_H

#define MAX_SIZE 100
#define KEY_SIZE 7  // 6 chars + null terminator
#define MIN_SIZE 16 // Minimum number of elements

/**
 * @brief Структура для хранения пары ключ-значение
 * 
 * Хранит строковый ключ фиксированной длины и строковое значение.
 */
typedef struct {
    char key[KEY_SIZE];
    char value[256];
} Entry;

/**
 * @brief Структура таблицы
 * 
 * Содержит массив элементов типа Entry и текущий размер таблицы.
 */
typedef struct {
    Entry data[MAX_SIZE];
    int size;
} Table;

/**
 * @brief Создает новую таблицу
 * 
 * Инициализирует таблицу с минимальным количеством элементов.
 * 
 * @param t Указатель на таблицу для инициализации
 */
void create(Table *t);

/**
 * @brief Освобождает ресурсы, занятые таблицей
 * 
 * Сбрасывает размер таблицы в 0.
 * 
 * @param t Указатель на таблицу для уничтожения
 */
void destroy(Table *t);

/**
 * @brief Добавляет новый элемент в таблицу
 * 
 * Добавляет пару ключ-значение в таблицу, если есть свободное место.
 * 
 * @param t Указатель на таблицу
 * @param key Ключ для добавления (строка не более 6 символов)
 * @param value Значение для добавления
 */
void add(Table *t, const char *key, const char *value);

/**
 * @brief Ищет элемент в таблице по ключу
 * 
 * Сортирует таблицу и выполняет бинарный поиск по ключу.
 * 
 * @param t Указатель на таблицу
 * @param key Ключ для поиска
 * @return Указатель на найденное значение или NULL, если элемент не найден
 */
char* search(Table *t, const char *key);

/**
 * @brief Выводит содержимое таблицы
 * 
 * Печатает все непустые элементы таблицы в формате "ключ: значение".
 * 
 * @param t Указатель на таблицу для вывода
 */
void print(Table *t);

/**
 * @brief Сортирует таблицу методом "Простое двухпоточное слияние"
 * 
 * Выполняет сортировку таблицы по ключам с использованием алгоритма
 * сортировки слиянием.
 * 
 * @param t Указатель на таблицу для сортировки
 */
void merge_sort(Table *t);

#endif