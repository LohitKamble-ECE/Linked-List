#include <stdio.h>

#include "list.h"
void print_int(const void *);
int compare_int(const void *, const void *);
int main(void) {
  LIST p = NULL;
  // Constructing the list.
  p = construct(p, print_int, compare_int);
  if (is_empty(p)) {
    printf("list is empty...\n");
  } else {
    printf("list is not empty...\n");
  }
  // Inserting the new node at the end of the list.
  for (int i = 1; i <= 25; ++i) {
    insert_after(p, NULL, &i, sizeof(int));
  }
  if (is_empty(p)) {
    printf("list is empty...\n");
  } else {
    printf("list is not empty...\n");
  }
  printf("size of the list is %zu\n", get_size(p));
  // Displaying the content of the list.
  display(p);
  node *ptr = NULL;
  if ((ptr = get_begin(p))) {
    printf("the head is pointing to %d.\n", *(int *)get_data(ptr));
  }
  if ((ptr = get_end(p))) {
    printf("the head is pointing to %d.\n", *(int *)get_data(ptr));
  }
  int d = 1000;
  printf("adding %d at the begining of the list...\n", d);
  insert_before(p, NULL, &d, sizeof(int));
  display(p);
  d = 2000;
  insert_after(p, NULL, &d, sizeof(int));
  printf("adding %d at the end of the list ...\n", d);
  display(p);
  printf("removing the front node present in the list ...\n");
  remove_current(p, get_begin(p));
  printf("removing the last node present in the list ...\n");
  remove_current(p, get_end(p));
  display(p);
  d = 17;
  printf("removing the node whose data member is %d ... \n", d);
  if ((ptr = find_the_key(p, &d))) {
    remove_current(p, ptr);
  } else {
    printf("did not remove the node for some reason ...\n");
  }
  if ((ptr = find_at_index(p, 10))) {
    printf("Data present at index %d = %d ... \n", 10, *(int *)get_data(ptr));
  } else {
    printf("node is not present at the particular index ...\n");
  }
  display(p);
  printf("inserting 17 after the 16 ...\n");
  d = 16;
  if ((ptr = find_the_key(p, &d))) {
    if ((ptr = get_after(p, ptr))) {
      d = 17;
      insert_after(p, ptr, &d, sizeof(int));
    } else {
      printf("node is not present after the 16 ...\n");
    }
  } else {
    printf("did not found the node ...\n");
  }
  display(p);
  printf("reversing the list ...\n");
  reverse(p);
  display(p);
  printf("removing the entire list...\n");
  remove_all(p);
  display(p);
  printf("destroying the list ...\n");
  destruct(p);
  // display(p); // causes the error now.
  return 0;
}
void print_int(const void *p) {
  printf("%d ", *(int *)p);
  return;
}
int compare_int(const void *a, const void *b) { return *(int *)a - *(int *)b; }
