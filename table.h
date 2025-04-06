#ifndef TABLE_H
#define TABLE_H

#define MAX_SIZE 100

typedef struct {
    int key;
    char value[256];
} Entry;

typedef struct {
    Entry data[MAX_SIZE];
    int size;
} Table;

void create(Table *t);
void destroy(Table *t);
void add(Table *t, int key, const char *value);
char* search(Table *t, int key);
void print(Table *t);
void shaker_sort(Table *t);

#endif