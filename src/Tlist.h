#ifndef TLIST_H
#define TLIST_H

#include <pthread.h>
#include <semaphore.h>


typedef struct {
    void **items;
    int capacity;
    int count;
    int head;
    int tail;
    pthread_mutex_t lock;
    sem_t full;
    sem_t empty;
} TList;

////////////////////////////////////////////////////////////
/// \brief Create and allocate memory for a new list.
///
/// \param size     Max capacity of the list.
///
////////////////////////////////////////////////////////////
TList* createList(int size);

////////////////////////////////////////////////////////////
/// \brief Append parsed element to the tail of the list.
///
/// \param list     pointer to a list on which we operate
/// \param el       pointer to an element to be added
///
////////////////////////////////////////////////////////////
void putItem(TList* list, void *el);

////////////////////////////////////////////////////////////
/// \brief Get and remove first (the oldest) element
///         from the list.
///
/// \param list     pointer to a list on which we operate
///
////////////////////////////////////////////////////////////
void* getItem(TList* list);

////////////////////////////////////////////////////////////
/// \brief Find and remove all instances of parsed element
///         from the list.
///
/// \param list     pointer to a list on which we operate
/// \param el       pointer to an element to be removed
///
/// \return         int 1 if element was removed, 0 otherwise
///
////////////////////////////////////////////////////////////
int removeItem(TList* list, void *el);

////////////////////////////////////////////////////////////
/// \brief Get count number of elements in the list.
///
/// \param list     pointer to a list on which we operate
///
/// \return         int count number of elements in the list
///
////////////////////////////////////////////////////////////
int getCount(TList* list);

////////////////////////////////////////////////////////////
/// \brief Set new maximum capacity of the list.
///
/// \param list     pointer to a list on which we operate
///
////////////////////////////////////////////////////////////
void setMaxSize(TList* list, int n);

////////////////////////////////////////////////////////////
/// \brief Append all elements from list2 to list1.
///
/// \param list     pointer to a list on which we operate
/// \param list2    pointer to a list from which we 
///                 take elements
///
////////////////////////////////////////////////////////////
void appendItems(TList* list, TList* list2);

////////////////////////////////////////////////////////////
/// \brief Destroy list, semaphores, mutex and free memory.
///
/// \param list     pointer to a list on which we operate
///
////////////////////////////////////////////////////////////
void destroyList(TList* list);

////////////////////////////////////////////////////////////
/// \brief print to console pointers of items in the list.
///
/// \param list     pointer to a list on which we operate
///                 representing chessboard
///
////////////////////////////////////////////////////////////
void showList(TList* list);

#endif