#pragma once

#include <stdbool.h>

typedef struct list List;

List *List_Create(void);

void List_Destroy(List *self);

void List_Append(List *self, void *item);

void List_Prepend(List *self, void *item);

void List_Remove(List *self, void *item);

void List_ForEach(List *self, void (*it)(List *, int, void *));

void* List_GetAt(List *self, int index);

int List_Size(List *self);

void List_Sort(List *self, bool (*compareTo)(void *, void *));

char *List_ToString(List *self);
