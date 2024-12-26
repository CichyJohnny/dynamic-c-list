#include <stdio.h>
#include "src/Tlist.h"


int main() {
    TList *list = createList(20);

    putItem(list, "H");
    putItem(list, "e");
    putItem(list, "l");
    putItem(list, "l");
    putItem(list, "o");

    for (int i = 0; i < list->count; i++)
        printf("%s ", (char*)list->items[i]);

    return 0;
}