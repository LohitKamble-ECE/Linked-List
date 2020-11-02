#include <stdio.h>

#include "list.h"
void print_int(const void *);
int compare_int(const void *, const void *);
int main(void) {
  LIST p = NULL;
  p = construct(p, print_int, compare_int);
  printf("size of the list is : %zu\n", get_size(p));
  for (int i = 1; i <= 25; ++i) {
    insert_after(p, NULL, &i, sizeof(int));
  }
  printf("size of the list is : %zu\n", get_size(p));
  display(p);
  void *data;
  if ((data = get_data(get_begin(p)))) {
    printf("starting node: %d\n", *(int *)data);
  }
  if ((data = get_data(get_end(p)))) {
    printf("end node     : %d\n", *(int *)data);
  }
  remove_all(p);
  printf("Size of the list is : %zu\n", get_size(p));
  if (is_empty(p)) {
    printf("list is empty.\n");
  } else {
    printf("no its not.\n");
  }
  return 0;
}
void print_int(const void *p) {
  printf("%d ", *(int *)p);
  return;
}
int compare_int(const void *a, const void *b) { return *(int *)a - *(int *)b; }
