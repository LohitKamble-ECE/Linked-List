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
  int i = reverse(p);
  if (!i) {
    printf("successfully reverse the list\n");
  } else {
    printf("unsuccessful reversing the list.\n");
  }
  printf("head = %d\n", *(int *)get_data(get_begin(p)));
  printf("end = %d\n", *(int *)get_data(get_end(p)));
  display(p);
  return 0;
}
void print_int(const void *p) {
  printf("%d ", *(int *)p);
  return;
}
int compare_int(const void *a, const void *b) { return *(int *)a - *(int *)b; }
