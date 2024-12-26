#include <stdio.h>
#include <stdlib.h>
#include "Tlist.h"


TList* createList(int size) {
    TList *list = (TList*)malloc(sizeof(TList));
    list->items = (void**)malloc(size * sizeof(void *));

    list->capacity = size;
    list->count = 0;
    list->head = 0;
    list->tail = 0;

    pthread_mutex_init(&list->lock, NULL);
    sem_init(&list->full, 0, size);
    sem_init(&list->empty, 0, 0);

    return list;
}


void putItem(TList* list, void *el) {
    sem_wait(&list->full);
    pthread_mutex_lock(&list->lock);

    list->items[list->tail] = el;
    list->tail = (list->tail + 1) % list->capacity;
    list->count++;

    pthread_mutex_unlock(&list->lock);
    sem_post(&list->empty);
}


void* getItem(TList* list) {
    sem_wait(&list->empty);
    pthread_mutex_lock(&list->lock);

    void *item = list->items[list->head];
    list->head = (list->head + 1) % list->capacity;
    list->count--;

    pthread_mutex_unlock(&list->lock);
    sem_post(&list->full);
    return item;
}


int removeItem(TList* list, void *el) {
    pthread_mutex_lock(&list->lock);

    int index = list->head;
    for (int i = 0; i < list->count; i++) {
        if (list->items[index] == el) {
            for (int j = i; j < list->count - 1; j++) {
                list->items[index] = list->items[(index + 1) % list->capacity];
                index = (index + 1) % list->capacity;
            }
            list->count--;
            pthread_mutex_unlock(&list->lock);
            return 1;
        }
        index = (index + 1) % list->capacity;
    }

    pthread_mutex_unlock(&list->lock);

    return 0;
}


int getCount(TList* list) {
    pthread_mutex_lock(&list->lock);

    int count = list->count;

    pthread_mutex_unlock(&list->lock);

    return count;
}


void setMaxSize(TList* list, int n) {
    pthread_mutex_lock(&list->lock);

    if (n < list->count) {
        list->capacity = list->count;
    } else {
        list->capacity = n;
    }

    pthread_mutex_unlock(&list->lock);
}


void appendItems(TList* list, TList* list2) {
    pthread_mutex_lock(&list->lock);
    pthread_mutex_lock(&list2->lock);

    while (list2->count > 0) {
        if (list->count < list->capacity) {
            list->items[list->tail] = list2->items[list2->head];
            list->tail = (list->tail + 1) % list->capacity;
            list2->head = (list2->head + 1) % list2->capacity;

            list->count++;
            list2->count--;
        } else {
            break;
        }
    }

    pthread_mutex_unlock(&list2->lock);
    pthread_mutex_unlock(&list->lock);
}


void destroyList(TList* list) {
    pthread_mutex_destroy(&list->lock);
    sem_destroy(&list->full);
    sem_destroy(&list->empty);

    free(list->items);
    free(list);
}


void showList(TList* list) {
    pthread_mutex_lock(&list->lock);

    int index = list->head;
    for (int i = 0; i < list->count; i++) {
        printf("%p ", list->items[index]);
        index = (index + 1) % list->capacity;
    }
    printf("\n");

    pthread_mutex_unlock(&list->lock);
}