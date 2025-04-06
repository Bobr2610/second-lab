#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create(Table *t) {
    t->size = 0;
}

void destroy(Table *t) {
    t->size = 0;
}

void add(Table *t, int key, const char *value) {
    if (t->size < MAX_SIZE) {
        t->data[t->size].key = key;
        strcpy(t->data[t->size].value, value);
        t->size++;
    }
}

void shaker_sort(Table *t) {
    int left = 0, right = t->size - 1;
    while (left < right) {
        for (int i = left; i < right; i++) {
            if (t->data[i].key > t->data[i + 1].key) {
                Entry temp = t->data[i];
                t->data[i] = t->data[i + 1];
                t->data[i + 1] = temp;
            }
        }
        right--;
        for (int i = right; i > left; i--) {
            if (t->data[i].key < t->data[i - 1].key) {
                Entry temp = t->data[i];
                t->data[i] = t->data[i - 1];
                t->data[i - 1] = temp;
            }
        }
        left++;
    }
}

char* search(Table *t, int key) {
    shaker_sort(t);
    int left = 0, right = t->size - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (t->data[mid].key == key) {
            return t->data[mid].value;
        } else if (t->data[mid].key < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return NULL;
}

void print(Table *t) {
    for (int i = 0; i < t->size; i++) {
        printf("%d: %s\n", t->data[i].key, t->data[i].value);
    }
}
