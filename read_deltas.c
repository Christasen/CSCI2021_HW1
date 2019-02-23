#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deltas.h"
#include <sys/stat.h>

// Reads integers in text delta format from the file named by fname
// and returns an array of them. The first integer in the file gives
// the starting point and subsequent integers are changes from the
// previous total.
//
// Opens the file with fopen() and scans through its contents using
// fscanf() counting how many text integers exist in it.  Then
// allocates an array of appropriate size using malloc(). Uses
// rewind() to go back to the beginning of the file then reads
// integers into the allocated array. Closes the file after reading
// all ints.  Returns a pointer to the allocated array.
//
// The argument len is a pointer to an integer which is set to the
// length of the array that is allocated by the function.
//
// If the file cannot be opened with fopen() or if there are no
// integers in the file, sets len to -1 and returns NULL.
int *read_text_deltas(char *fname, int *len) {
  int sum = 0;
  int i;
  FILE* fin = fopen(fname, "r");
  *len = 0;
  // error handler here
  if (fin == NULL) {
       printf("File does not exist\t");
       *len = -1;
       return NULL;
     }
  // scan the whole file here
  while(fscanf(fin, "%d", &i)!= EOF){
   *len = *len + 1;
  }

  // error handler here;
  if (*len == 0) {
       printf("There are not int in the file\t");
       *len = -1;
       fclose(fin); // should close the file here
       return NULL;
     }
  // crearting array here
  int *darr = malloc((*len)*sizeof(int));
  rewind(fin);   // take the cursor to the beginning of the file
  for(int i=0; i< *len; i++){  // struct array
    fscanf(fin,"%d\n", &darr[i]);
    }
  fclose(fin); // close input file

  // updating array element here
  sum = darr[0];
  for(int i = 1; i < *len; i++){
      sum = sum + darr[i];
      darr[i] = sum;
    }

  // for(int i = 0; i<cnt; i++){
  //   fprintf(stdout,"%d %d \n",                 // use open stdout to print
  //           i, darr[i]);
  // }
  // free(darr);                                    // free memory
  return darr;
}


// Reads integers in binary delta format from the file named by fname
// and returns an array of them.  The first integer in the file gives
// the starting point and subsequent integers are changes from the
// previous total.
//
// Integers in the file are in binary format so the size of the file
// in bytes indicates the quantity of integers. Uses the stat() system
// call to determine the file size in bytes which then allows an array
// of appropriate size to be allocated. DOES NOT scan through the file
// to count its size as this is not needed.
//
// Opens the file with fopen() and uses repeated calls to fread() to
// read binary integers into the allocated array. Does delta
// computations as integers are read. Closes the file after reading
// all ints.
//
// The argument len is a pointer to an integer which is set to
// the length of the array that is allocated by the function.
//
// If the file cannot be opened with fopen() or file is smaller than
// the size of 1 int, sets len to -1 and returns NULL.

int *read_int_deltas(char *fname, int *len){
  int index;
  int sum = 0;
  FILE* fin = fopen(fname, "r");
  // error handler here
  if (fin == NULL) {
     printf("File does not exist\t");
     *len = -1;
     return NULL;
  }

// get the size of the file in bytes;
  struct stat buf;
  int boolean = stat(fname, &buf);
  int size = buf.st_size;    // total size of file in bytes
  if(size < sizeof(int) || boolean == -1){        // if something went wrong or bail if file is too small
     *len = -1;
     printf("something wrong here\t");
     fclose(fin); // should close the file here
     return NULL;
   }
  // index in the array;
  index = (size / 4);
  // declare the array here
  int *darr = malloc(size);
  *len = 0;
  // reading stuff here
  for(int i= 0; i < index; i++){
    fread(&darr[i], sizeof(int), 1, fin);
    *len += 1;
  }
  fclose(fin);

  // calculating array here
  sum = darr[0];
  for(int j = 1; j < index; j++){
      sum = sum + darr[j];
      darr[j] = sum;
    }

  return darr;


// allocating array;

}
