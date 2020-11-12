#ifndef LIST_H
#define LIST_H
#include <stddef.h> /* size_t */
// Declaring structure for the individual node present in the list.
typedef struct __node {
  void *data;
  struct __node *next;
} node;
// Declaring structure for the list itself.
typedef struct __list {
  size_t size;
  node *head;
  node *tail;
  void (*print)(const void *);
  int (*compare)(const void *, const void *);
} list;
typedef list *LIST;
// Modify Interface.
list *construct(list *this_list, void (*print)(const void *),
                int (*compare)(const void *, const void *));
list *destruct(list *this_list);
int insert_after(list *this_list, node *this_node, void *data, size_t size);
int insert_before(list *this_list, node *this_node, void *data, size_t size);
int remove_current(list *this_list, node *this_node);
int remove_all(list *this_list);
void display(list *this_list);
int reverse(list *this_list);
// Access Interface.
int is_empty(list *this_list);
size_t get_size(list *this_list);
node *get_begin(list *this_list);
node *get_end(list *this_list);
void *get_data(node *this_node);
node *get_before(list *this_list, node *this_node);
node *get_after(list *this_list, node *this_node);
node *find_the_key(list *this_list, void *data);
node *find_at_index(list *this_list, size_t index);
#endif
