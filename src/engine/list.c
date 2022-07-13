#include <stdlib.h>
#include <stdio.h>
#include <uthash/include/utlist.h>
#include <engine/list.h>

struct node
{
  void *data;
  struct node *next;
  struct node *prev;
};

struct list
{
  struct node *head;
};

static bool compare(struct node *first, struct node *second)
{
  return !(first->data == second->data);
}

static struct node *findByData(List *self, void *data)
{
  struct node *tail;
  struct node *node = calloc(1, sizeof(struct node));

  DL_FOREACH(self->head, tail);
  DL_SEARCH(self->head, tail, node, compare);

  return node;
}

List *List_Create(void)
{
  List *self = calloc(1, sizeof(List));

  return self;
}

void List_Destroy(List *self)
{
  struct node *node;
  struct node *temp;

  if (self)
  {
    DL_FOREACH_SAFE(self->head, node, temp)
    {
      DL_DELETE(self->head, node);
      free(node);
    }

    free(self);
  }
}

void *List_GetAt(List *self, int index)
{
  struct node *node = self->head;

  for (int i = 0; i < index; ++i)
  {
    node = node->next;
  }

  return node->data;
}

int List_Size(List *self)
{
  int count;
  struct node *tail;

  DL_COUNT(self->head, tail, count);

  return count;
}

void List_Append(List *self, void *item)
{
  struct node *node = calloc(1, sizeof(struct node));

  node->data = item;
  DL_APPEND(self->head, node);
}

void List_Prepend(List *self, void *item)
{
  struct node *node = calloc(1, sizeof(struct node));

  node->data = item;
  DL_PREPEND(self->head, node);
}

void List_Remove(List *self, void *item)
{
  struct node *node;
  struct node like = {
      .data = item};

  DL_SEARCH(self->head, node, &like, compare);
  DL_DELETE(self->head, node);
}

void List_ForEach(List *self, void (*it)(List *, int, void *))
{
  struct node *node;
  int index = 0;

  DL_FOREACH(self->head, node)
  {
    it(self, index++, node->data);
  }
}

void List_Sort(List *self, bool (*compareTo)(void *, void *))
{
  DL_SORT(self->head, compareTo);
}

char *List_ToString(List *self)
{
  struct node *node;
  int size = List_Size(self);
  int index = 0, count = 0;
  char *out = calloc(size * 128, 1);

  count = sprintf(out, "[List(%p)=", self);

  DL_FOREACH(self->head, node)
  {
    count += sprintf(out + count, "<[%d]%p>%s", index, node->data, (index != size - 1) ? "," : "");
    index++;
  }

  sprintf(out + count, "]");

  return out;
}

void *List_FindFirst(List *self, void *user, bool (*callback)(void *, void *))
{
  struct node *node;

  DL_FOREACH(self->head, node)
  {
    if (callback(node->data, user))
    {
      return node->data;
    }
  }

  return NULL;
}
