#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include <sys/stat.h>

// global variable
int ECHO = 0;

// heler function here
// Print the given string if echoing is turned on
void echo(char *s){
  if(ECHO){
    printf("%s",s);
  }
}



int main(int argc, char *argv[]){

  //
  if(argc > 1 && strcmp("-echo",argv[1])==0) {
    ECHO=1;
  }
  int reading;
  char commands[128];
  bst_t tree;
  bst_init(&tree);
  printf("BST Demo\n");
  printf("Commands:\n");
  printf("  print:          shows contents of the tree in reverse sorted order\n");
  printf("  clear:          eliminates all elements from the tree\n");
  printf("  quit:           exit the program\n");
  printf("  add <name>:     inserts the given string into the tree, duplicates ignored\n");
  printf("  find <name>:    prints FOUND if the name is in the tree, NOT FOUND otherwise\n");
  printf("  preorder:       prints contents of the tree in pre-order which is how it will be saved\n");
  printf("  save <file>:    writes the contents of the tree in pre-order to the given file\n");
  printf("  load <file>:    clears the current tree and loads the one in the given file\n");


// loop to get the commands
  while(1) {
   printf("BST> ");

   // reading commands from users
   reading = fscanf(stdin,"%s",commands);
   if(reading == EOF){
     echo("\n");
     break;
   }
   echo(commands);
   // print commands
   if(strcmp("print", commands) == 0) {
     echo("\n");
     bst_print_revorder(&tree);
   }

   // clear commands
   else if(strcmp("clear", commands) == 0){
     echo("\n");
     bst_clear(&tree);
   }

   // quit commands
   else if(strcmp("quit", commands) == 0){
     echo("\n");
     break;
   }
   // preorder commands
   else if(strcmp("preorder", commands) == 0){
     echo("\n");
     bst_print_preorder(&tree);
   }

   // add commands
   else if(strcmp("add", commands) == 0) {
     // scan the name of the file you want to add;
     fscanf(stdin,"%s",commands);
     echo(" ");
     echo(commands);
     echo("\n");
     reading = bst_insert(&tree, commands);
   }

   // save commands
   else if(strcmp("save", commands) == 0) {
     // scan the name of the file you want to add;
     fscanf(stdin,"%s",commands);
     echo(" ");
     echo(commands);
     echo("\n");
     bst_save(&tree,commands);
   }


   // load commands
   else if(strcmp("load", commands) == 0) {
     // scan the name of the file you want to add;
     fscanf(stdin,"%s",commands);
     echo(" ");
     echo(commands);
     echo("\n");
     reading = bst_load(&tree, commands);
     if(reading) {
       printf("load failed\n");
      }
    }


   // find commands
   else if(strcmp("find", commands) == 0) {
     // scan the name of the file you want to add;
     fscanf(stdin,"%s",commands);
     echo(" ");
     echo(commands);
     echo("\n");
     if( bst_find(&tree, commands)) {
        printf("FOUND\n");
     }
     else {
       printf("NOT FOUND\n");
     }
   }

   // invalid commands cases
   else {
     echo("\n");
     printf("Unknown command '%s'\n", commands);
   }

  }

  // clean the bst tree
  bst_clear(&tree);
  return 0;
}
