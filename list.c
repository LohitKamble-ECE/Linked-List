/**
 * Generic Singly Linked List Implementation
 * Author: Lohit Kamble
 * Data  : Nov 2 2020
 * Time  : 15:53
 * System: Linux
 */
#include "list.h"

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define is_zero(n) (n) == 0 ? 1 : 0

/**
 * Allocated the memory for new node.
 * a. Return the address if memory allocated successfully.
 * b. Return NULL if it unable to do so.
 */
static node *create_node(node *next, void *data, size_t size) {
  node *new_node = NULL;
  if ((new_node = (node *)malloc(sizeof(node)))) {
    // Memory is allocated. Good to go.
    if ((new_node->data = (void *)malloc(size))) {
      // Memory is allocated. Good to go.
      memcpy(new_node->data, data, size);
      new_node->next = next;
      return new_node;
    } else {
      // Memory did not allocated for data member of the node.
      // Handling the memory leak.
      free(new_node);
      new_node = NULL;
      fprintf(stderr, "ERROR:(" __FILE__ ":%d): %s...\n", __LINE__,
              strerror(errno));
    }
  } else {
    // Memory did not allocated for node itself.
    fprintf(stderr, "ERROR:(" __FILE__ ":%d): %s...\n", __LINE__,
            strerror(errno));
  }
  return new_node;
}

/**
 * Construct the list before any operation can perform on it.
 * a. Construct the list if is not constructed already.
 * b. Allocate the memory for the new list.
 * c. Initializes its member.
 * d. Return address of this new list if memory is successfully allocated.
 * e. Return NULL if it unable to do so.
 */
list *construct(list *this_list, void (*print)(const void *),
                int (*compare)(const void *, const void *)) {
  if (!this_list) {
    // List is not constructed. Go ahed and construct it.
    list *new_list = NULL;
    if ((new_list = (list *)malloc(sizeof(list)))) {
      // Memory is allocated. Go ahed.
      new_list->size = 0;
      new_list->head = NULL;
      new_list->tail = NULL;
      new_list->print = print;
      new_list->compare = compare;
      return new_list;
    } else {
      // Memory did not allocated for tte list.
      fprintf(stderr, "ERROR:(" __FILE__ ":%d): %s...\n", __LINE__,
              strerror(errno));
    }
  } else {
    // List is already constructed.
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): it looks like you have already constructed this list ...\n",
            __LINE__);
    fprintf(
        stderr,
        "ERROR:(" __FILE__
        ":%d): trying to construct it once again does not make any sense ...\n",
        __LINE__);
  }
  return this_list;
}

/**
 * Destruct the list so that no any operation can perform on it.
 * a. Remove all the node present in the list.
 * b. Deallocated the memory of each node in the list.
 * c. If it successfully able to deallocated all the node then deallocated the
 *    memory of list itself.
 * d. Return NULL if successfully able to destruct the list.
 * e. Return address of list which is passed to this function if it unable to
 *    do so.
 */
list *destruct(list *this_list) {
  if (this_list) {
    // List is constructed. Go ahed and destruct it.
    if (!remove_all(this_list)) {
      // Removed all the node present in the list.
      free(this_list);
      this_list = NULL;
    } else {
      // Did not removed all the node present in the list.
      // Or it may be empty list.
      fprintf(stderr,
              "ERROR(" __FILE__
              ":%d): unable to destruct the list for some reason ...\n",
              __LINE__);
    }
  } else {
    // List is not constructed.
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): it looks like you have not constructed this list yet ...\n",
            __LINE__);
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): trying to destruct it does not make any sense ...\n",
            __LINE__);
  }
  return this_list;
}

/** Insert the new node after the specified node present in the list.
 * a. If given node is valid node present in the list, then allocated the
 *    memory for new node, and insert it after the given node.
 * b. If given node is NULL, then append the new node at the end of the list.
 * c. If given node is neither valid node nor NULL, then no any operation can
 *    be performed on the list.
 * d. Return 0 if it is successfully able to insert the new node into the list.
 * e. Return -1 if it unable to do so.
 */
int insert_after(list *this_list, node *this_node, void *data, size_t size) {
  if (this_list) {
    // List is constructed. Go ahed.
    if (this_list->head) {
      // List is not empty Go ahed.
      if (this_node && this_node != this_list->tail) {
        // Inserting new node after the specified node.
        node *curr = this_list->head;
        while (curr != this_node) {
          if (!curr->next) {
            // It looks like I have traverse the entire list but unable to find
            // the given node after which I have to insert the new node.
            // I better abort this operation since the given node is not valid
            // node or I can say it is not present in the list.
            return -1;
          } else {
            // Keep going till we are at given node.
            curr = curr->next;
          }
        }
        // Finally I have found the given node.
        node *new_node = NULL;
        if ((new_node = create_node(curr->next, data, size))) {
          // Memory is allocated for the new node.
          curr->next = new_node;
        } else {
          // Oops! Memory did not allocated.
          return -1;
        }
      } else {
        // Appending the new node at the end of the list.
        node *curr = this_list->head;
        while (curr->next) {
          curr = curr->next;
        }
        // Finaly I have found the end node of the list.
        node *new_node = NULL;
        if ((new_node = create_node(curr->next, data, size))) {
          // Memory is allocated for the new node.
          curr->next = new_node;
          // Making tail points to the is new end node of the list.
          this_list->tail = new_node;
        } else {
          // Oops! Memory did not allocated.
          return -1;
        }
      }
    } else {
      // List is empty. Creating its first node.
      node *new_node = NULL;
      if ((new_node = create_node(this_list->head, data, size))) {
        // Memory is allocated for the new node.
        // Making head and tail points to the new node since it is the first
        // and also last not of the list.
        this_list->head = new_node;
        this_list->tail = new_node;
      } else {
        // Oops! Memory did not allocated.
        return -1;
      }
    }
    // Accumulating the size of the list.
    ++this_list->size;
    return 0;
  } else {
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): it looks like you have not constructed this list yet ...\n",
            __LINE__);
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): trying to insert node into it does not make any sense...\n",
            __LINE__);
  }
  return -1;
}

/**
 * Insert the new node after the given node in the list.
 * a. If given node is valid node present in the list, insert the new node
 *    after it.
 * b. If given node is NULL, prepend the new node at the beginning of the list.
 * c. If given node is neither valid node nor NULL, then no operation perform
 *    on it.
 * d. Return 0 if it successfully able to insert the node into the list.
 * e. Return -1 if it unable to do so.
 */
int insert_before(list *this_list, node *this_node, void *data, size_t size) {
  if (this_list) {
    // List is constructed. Go ahed.
    if (this_list->head != NULL && this_node != this_list->head &&
        this_node != NULL) {
      // Inserting new node at given specified node.
      node *curr = this_list->head;
      while (curr->next != this_node) {
        if (!curr->next) {
          // It looks like I have traverse the entire list but unable to find
          // the given node in the list.
          // I better abort this operation since the given node is not a valid
          // node present in the list.
          return -1;
        } else {
          // Keep going till we are at the given node.
          curr = curr->next;
        }
      }
      // Finally I have found the the node before which I have to insert the
      // new node.
      node *new_node = NULL;
      if ((new_node = create_node(curr->next, data, size))) {
        // Memory is allocated.
        curr->next = new_node;
      } else {
        // Oops! Memory is not allocated.
        return -1;
      }
    } else {
      // Insert the new node at the beginning of the list.
      node *new_node = NULL;
      if ((new_node = create_node(this_list->head, data, size))) {
        // Memory is allocated.
        // Making the head points to this new first node of the list.
        this_list->head = new_node;
        if (this_list->size == 0) {
          // Making the tail points to this new node, since it is first and
          // only node present in the list.
          this_list->tail = new_node;
        }
      } else {
        // Oops! Memory did not allocated.
        return -1;
      }
    }
    // Accumulating the size of the list.
    ++this_list->size;
    return 0;
  } else {
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): it looks like you have not constructed this list yet ...\n",
            __LINE__);
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): trying to insert node into it does not make any sense ...\n",
            __LINE__);
  }
  return -1;
}

/**
 * Remove the current element from the list.
 * a. Deallocate the memory of the given node if it is the part of the given
 *    list.
 * b. Return 0 if it successfully able to remove the node from the list.
 * c. Return -1 if it unable to do so.
 */
int remove_current(list *this_list, node *this_node) {
  if (this_list) {
    // List is constructed. Go ahed.
    if (this_list->head) {
      // List is not empty. Go ahed.
      if (this_node == this_list->head || this_list->size == 1) {
        // Removing the first node of the list.
        node *to_be_deleted = this_list->head;
        this_list->head = this_list->head->next;
        if (this_list->size == 1) {
          // Making the tail points to the NULL since there is only no node
          // present in the list.
          this_list->tail = NULL;
        }
        free(to_be_deleted->data);
        free(to_be_deleted);
      } else if (this_node != NULL && this_node != this_list->tail) {
        // Removing node which does not at the beginning and last of the list.
        node *curr, *prev;
        curr = prev = this_list->head;
        while (curr != this_node) {
          if (!curr->next) {
            // It looks like I have traverse the entire list but unable to find
            // the given node in the list.
            // I better abort this operation since the given node is not a valid
            // node present in the list.
            return -1;
          } else {
            // Keep going.
            prev = curr;
            curr = curr->next;
          }
        }
        prev->next = prev->next->next;
        free(curr->data);
        free(curr);
      } else {
        // Removing the node which is at the end of the list.
        node *curr, *prev;
        curr = prev = this_list->head;
        while (curr->next) {
          // Keep going till we find the end not of the list.
          prev = curr;
          curr = curr->next;
        }
        prev->next = prev->next->next;
        // Making the tail points to newly last node of the list.
        this_list->tail = prev;
        free(curr->data);
        free(curr);
      }
      // Accumulating the size of the list.
      --this_list->size;
      return 0;
    } else {
      // List is empty. Cannot remove node from empty list.
      fprintf(stderr,
              "ERROR: cannot remove node from the list since is empty ...\n");
      return -1;
    }
  } else {
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): it looks like you have not constructed this list yet ...\n",
            __LINE__);
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): trying to remove node form it does not make any sense ...\n",
            __LINE__);
  }
  return -1;
}

/**
 * Remove all the element from the list.
 * a. Deallocated the merory of each node present in the list.
 * b. Return 0 if it able to so or -1 otherwise.
 */
int remove_all(list *this_list) {
  if (this_list) {
    // List is constructed. Go ahed.
    if (this_list->head) {
      // List is not empty.
      while (this_list->head) {
        // While there are still node present in the list.
        // Remove the currently last node.
        remove_current(this_list, NULL);
      }
      return 0;
    } else {
      // List is empty.
      fprintf(stderr,
              "ERROR: cannot remove all the element from the list since it is "
              "empty ...\n");
      return -1;
    }
  } else {
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): it looks like you have not constructed this list yet ...\n",
            __LINE__);
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): trying to remove node form it does not make any sense ...\n",
            __LINE__);
  }
  return -1;
}

/**
 * Display the content of the list.
 */
void display(list *this_list) {
  if (this_list) {
    // List is constructed. Go ahed.
    if (this_list->head) {
      // List is not empty.
      node *curr = this_list->head;
      while (curr) {
        (*this_list->print)(curr->data);
        curr = curr->next;
      }
      printf("\n");
    } else {
      fprintf(stderr, " list is empty ...\n");
    }
  } else {
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): it looks like you have not constructed this list yet ...\n",
            __LINE__);
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): trying to display its contain does not make any sense ...\n",
            __LINE__);
  }
}

/**
 * Find wheter list is empty or not.
 * Return 1 if list is empty or 0 otherwise.
 */
int is_empty(list *this_list) {
  if (this_list) {
    // List is constructed. Go ahed.
    if (!this_list->head) {
      // List is empty.
      return 1;
    } else {
      return 0;
    }
  } else {
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): it looks like you have not constructed this list yet ...\n",
            __LINE__);
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): trying to find whether it is empty or not does not make any "
            "sense ...\n",
            __LINE__);
  }
  return 0;
}

/**
 * Return the address of first node present in the list.
 */
node *get_begin(list *this_list) {
  if (this_list) {
    // List is constructed.
    if (this_list->head) {
      // List is not empty.
      return this_list->head;
    } else {
      fprintf(stderr, "ERROR: list is empty ...\n");
    }
  }
  return NULL;
}

/**
 * Return the address of last node present in the list.
 */
node *get_end(list *this_list) {
  if (this_list) {
    if (this_list->head) {
      return this_list->tail;
    } else {
      fprintf(stderr, "ERROR: list is empty ...\n");
    }
  }
  return NULL;
}

/**
 * Return the pointer to the data present in the list.
 */
void *get_data(node *this_node) {
  if (this_node) {
    return this_node->data;
  } else {
    fprintf(stderr, "ERROR: null pointer dereferencing ...\n");
  }
  return NULL;
}

/**
 * Return the address of the node before the given node present in the list.
 * a. If given node is not present in the list then return NULL
 */
node *get_before(list *this_list, node *this_node) {
  if (this_list) {
    // List is constructed. Go ahed.
    if (this_list->head) {
      // List is not empty. Go ahed.
      node *curr = this_list->head;
      while (curr->next != this_node) {
        if (!curr->next) {
          // It looks like I have traverse the entire list but unable to find
          // the given node in the list.
          // I better abort this operation since the given node is not a valid
          // node present in the list.
          return NULL;
        } else {
          // Keep going.
          curr = curr->next;
        }
      }
      // Finally I have found the given node.
      return curr;
    } else {
      fprintf(stderr, "ERROR: list is empty ...\n");
    }
  } else {
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): it looks like you have not constructed this list yet ...\n",
            __LINE__);
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): trying to find address before any node present in the list "
            "does not make any sense ...\n",
            __LINE__);
  }
  return NULL;
}

/* Return the address after the given node present in the list.
 * a. If given node is not present in the list then return NULL
 */
node *get_after(list *this_list, node *this_node) {
  if (this_list) {
    // List is constructed. Go ahed.
    if (this_list->head) {
      // List is not empty. Go ahed.
      node *curr = this_list->head;
      while (curr != this_node) {
        if (!curr->next) {
          // It looks like I have traverse the entire list but unable to find
          // the given node in the list.
          // I better abort this operation since the given node is not a valid
          // node present in the list.
          return NULL;
        } else {
          // Keep going.
          curr = curr->next;
        }
      }
      // Finally I have found the given node.
      return curr->next;
    } else {
      fprintf(stderr, "ERROR: list is empty ...\n");
    }
  } else {
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): it looks like you have not constructed this list yet ...\n",
            __LINE__);
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): trying to find the address after the node present in the "
            "list does not make any sense ...\n",
            __LINE__);
  }
  return NULL;
}

/**
 * Find the address of node whose data member is equal to the given data.
 * a. If unable to find then return NULL
 */
node *find_the_key(list *this_list, void *data) {
  if (this_list) {
    // List is constructed. Go ahed.
    if (this_list->head) {
      // List is not empty. Go ahed.
      node *curr = this_list->head;
      while (curr) {
        int diff = (*this_list->compare)(curr->data, data);
        if (is_zero(diff)) {
          return curr;
        } else {
          curr = curr->next;
        }
      }
    } else {
      fprintf(stderr, "ERROR: list is empty ...\n");
    }
  } else {
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): it looks like you have not constructed this list yet ...\n",
            __LINE__);
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): trying to find the key does not make any sense ...\n",
            __LINE__);
  }
  return NULL;
}

/**
 * Find the address of node according to its index present in the list.
 */
node *find_at_index(list *this_list, size_t size) {
  if (this_list) {
    // List is constructed. Go ahed.
    if (this_list->head) {
      // List is not empty. Go ahed.
      node *curr = this_list->head;
      size_t index = 0;
      while (index < size) {
        if (!curr->next) {
          // It looks like I have traverse the entire list but unable to find
          // the given node in the list.
          // I better abort this operation since the given node is not a valid
          // node present in the list.
          return NULL;
        } else {
          curr = curr->next;
        }
      }
      return curr;
    } else {
      fprintf(stderr, "ERROR: list is empty ...\n");
    }
  } else {
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): it looks like you have not constructed this list yet ...\n",
            __LINE__);
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): trying to find address of node at particualar index does "
            "not make any sense...\n",
            __LINE__);
  }
  return NULL;
}

/**
 * Return the size of the list.
 */
size_t get_size(list *this_list) {
  if (this_list) {
    return this_list->size;
  } else {
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): it looks like you have not constructed this list yet ...\n",
            __LINE__);
    fprintf(stderr,
            "ERROR:(" __FILE__
            ":%d): trying to find its size does not make any sense...\n",
            __LINE__);
  }
  return -1;
}
