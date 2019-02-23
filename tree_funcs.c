#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include <sys/stat.h>

// Initialize the given tree to have a null root and have size 0.
void bst_init(bst_t *tree) {
  tree->size = 0;
  tree->root = NULL;
}

// Part 1:
// Inserts given name into a binary search tree. Uses an ITERATIVE
// (loopy) approach to insertion which starts a pointer at the root of
// the tree and changes its location until the correct insertion point
// is located. Returns 1 if a new node is created and 0 if a duplicate
// name is found in the tree already in which case the name is not
// added.


int bst_insert(bst_t *tree, char name[]) {
  node_t *node = tree->root;
  // check whether it is an empty tree
  if ( node == NULL) {
    // creating a new node here;
    node_t *ptr = (node_t *) malloc(sizeof(node_t));

    // cant use equal directly here
    strcpy(ptr->name, name);
    // setting the node for new ptr
    ptr->right = NULL;
    ptr->left = NULL;
    // Initialize the root of the tree
    tree-> root = ptr;
    // increment the size of the tree
    tree-> size += 1;
    // creating the tree successfully
    return 1;
  }

  // if the tree is not empty, then use the loopy way to solve this problem
  while ( node != NULL) {
    // right case:
    if (strcmp(name, node->name) > 0) {
      // checing whether the right node is NULL
      if(node->right == NULL) {
        // creating a new node here;
        node_t *ptr = (node_t *) malloc(sizeof(node_t));

        // cant use equal directly here
        strcpy(ptr->name, name);
        // setting the node for new ptr
        ptr->right = NULL;
        ptr->left = NULL;
        //!!!!! here it should let the right node to ptr
        node->right = ptr;

        // increment the size
        tree->size += 1;
        return 1;
      }
      // if the node is not NULL, move the pointer
      else {
        node = node->right;
      }
    }
    // duplicated cases
    // if duplication exist, return 0
    else if (strcmp(name, node->name) == 0) {
      return 0;
    }
    // left case
    else {
      // checing whether the right node is NULL
      if(node->left == NULL) {
        // creating a new node here;
        node_t *ptr = (node_t *) malloc(sizeof(node_t));

        // cant use equal directly here
        strcpy(ptr->name, name);
        // setting the node for new ptr
        ptr->right = NULL;
        ptr->left = NULL;
        //!!!!! here it should let the left node to ptr
        node->left = ptr;

        // increases the size of the tree
        tree-> size += 1;
        return 1;
      }
      // if the node is not NULL, move the pointer
      else {
        node = node->left;
      }
    }
  }
  // handle other strange cases
  // return 0
  return 0;
}


// Determines whether name is present or not in the tree using binary
// search. Returns 1 if name is present and 0 otherwise. Uses an
// ITERATIVE (loopy) approach which starts a pointer at the root of
// the tree and changes it until the search name is found or
// determined to not be in the tree.
int bst_find(bst_t *tree, char name[]) {
  node_t *node = tree->root;
  // check whether it is an empty tree
  if ( node == NULL) {
    return 0;
  }
  // if the tree is not empty, then use the loopy way to solve this problem
  while ( node != NULL) {
    // find node
    // right cases
    if (strcmp(name, node->name) > 0) {
      if(node->right == NULL) {
        return 0;
        }
      node = node->right;
      }
    // duplication
    else if (strcmp(name, node->name) == 0) {
      return 1;

    }
     // left cases
    else {
      if(node->left == NULL) {
        return 0;
      }
      node = node->left;
    }
  }
  // handle strange inputs
  return 0;
}



// Eliminate all nodes in the tree setting its contents empty. Uses
// recursive node_remove_all() function to free memory for all nodes.
void bst_clear(bst_t *tree) {
  // If not null, call remove function
  if (tree->root != NULL) {
    node_remove_all(tree->root);
  }
    // reinitialize the tree;
    tree->size = 0;
    tree->root = NULL;
}

// Recursive helper function which visits all nodes in a tree and
// frees the memory associated with them. This requires a post-order
// traversal: visit left tree, visit right tree, then free the cur
// node.
void node_remove_all(node_t *cur) {
  // If not null, call remove function
  if (cur != NULL) {
    // visit left tree
    node_remove_all(cur->left);
    // visit right tree
    node_remove_all(cur->right);
    // free the memory location!
    free(cur);
  }
}

// Prints the elements of the tree in reverse order at differing
// levels of indentation which shows all elements and their structure
// in the tree. Visually the tree can be rotated clockwise to see its
// structure.
void bst_print_revorder(bst_t *tree) {

  // new here
  node_t *ptr = tree->root;
  if( ptr != NULL)
  {
    node_print_revorder(ptr, 0);
  }
}

// Recursive helper function which prints all elements in the tree
// rooted at cur in reverse order: traverses right subtree, prints cur
// node, traverses left tree. Parameter 'indent' indicates how far to
// indent (2 spaces per indent level).

void node_print_revorder(node_t *cur, int indent) {
  if (cur == NULL){
    return;
  }
  else {
    node_print_revorder(cur->right, indent+1);
    // indentation part
    // in each loop there will be two spaces
    for(int i = 0; i < indent; i++) {
      printf("  ");
    }
    printf("%s\n", cur->name);
    node_print_revorder(cur->left, indent+1);
  }
}

// Print all the data in the tree in pre-order with indentation
// corresponding to the depth of the tree. Makes use of
// node_write_preorder() for this.
void bst_print_preorder(bst_t *tree) {
  node_t *ptr = tree->root;
  node_write_preorder(ptr, stdout, 0);
}

// Saves the tree by opening the named file, writing the tree to it in
// pre-order with node_write_preorder(), then closing the file.
void bst_save(bst_t *tree, char *fname) {
  FILE *f = fopen(fname, "w");
  node_write_preorder(tree->root, f, 0);
  fclose(f);
}


// Recursive helper function which writes/prints the tree in pre-order
// to the given open file handle. The parameter depth gives how far to
// indent node data, 2 spaces per unit depth. Depth increases by 1 on
// each recursive call. The function prints the cur node data,
// traverses the left tree, then traverses the right tree.

void node_write_preorder(node_t *cur, FILE *out, int depth) {
  if (cur == NULL) {
    return;
  }
  else {
    for (int i = 0; i < depth; i++) {
      fprintf(out, "  ");
    }
    fprintf(out, "%s\n", cur->name);
    node_write_preorder(cur->left, out, depth+1);
    node_write_preorder(cur->right, out, depth+1);
  }
}

// Clears the given tree then loads new elements to it from the
// named. Repeated calls to bst_insert() are used to add strings read
// from the file.  If the tree is stored in pre-order in the file, its
// exact structure will be restored.  Returns 1 if the tree is loaded
// successfully and 0 if opening the named file fails in which case no
// changes should be made to the tree.
int bst_load(bst_t *tree, char *fname ) {
  //clear the tree first
  bst_clear(tree);
  FILE *f = fopen(fname, "r");
  // Not NUll cases
  if (f!= NULL) {
    char name[128];
    while(fscanf(f, "%s\n", name) != EOF) {
      bst_insert(tree, name);
    }
    fclose(f);
    return 0;
  }
  else {
    return 1;
  }
}
