#include <stdio.h>

#include "list.h"
void print_int(const void *);
int compare_int(const void *, const void *);
int main(void) {
  LIST p = NULL;
  // Constructing the list.
  p = construct(p, print_int, compare_int);
  // Inserting the new node at the end of the list.
  for (int i = 1; i <= 25; ++i) {
    insert_after(p, NULL, &i, sizeof(int));
  }
  // Displaying the content of the list.
  display(p);
  // Finding out where head is pointing.
  node *ptr;
  if ((ptr = get_begin(p))) {
    printf("head is pointing to data member: %d\n", *(int *)get_data(ptr));
  } else {
    printf("list is empty.\n");
  }
  // Finding out where tail is pointing.
  if ((ptr = get_end(p))) {
    printf("tail is pointing to data member: %d\n", *(int *)get_data(ptr));
  } else {
    printf("list is empty.\n");
  }
  // Deleting the node particular node.
  int d = 15;
  printf("Removing the data %d form the list\n", d);
  ptr = find_the_key(p, &d);
  remove_current(p, ptr);
  display(p);
  node *data;
  // Finding the key at particular index.
  d = 17;
  printf("Finding the key at particular index %d\n", d);
  if ((data = find_at_index(p, d))) {
    printf("data at %d is %d\n", d, *(int *)get_data(data));
  } else {
    printf("index not present in the list.\n");
  }
  // Removing all the node present in the list.
  printf("Removing all the node present in the list.\n");
  remove_all(p);
  display(p);
  // Destructing the list.
  printf("Destructing the entire list.\n");
  p = destruct(p);
  display(p);
  return 0;
}
void print_int(const void *p) {
  printf("%d ", *(int *)p);
  return;
}
int compare_int(const void *a, const void *b) { return *(int *)a - *(int *)b; }
