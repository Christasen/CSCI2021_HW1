#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deltas.h"
#include <sys/stat.h>

// Prints a graph of the values in data which is an array of integers
// that has len elements. The max_height argument is the height in
// character rows that the maximum number data[] should be.  A sample
// graph is as follows:
//
// length: 50
// min: 13
// max: 996
// range: 983
// max_height: 10
// units_per_height: 98.30
//      +----+----+----+----+----+----+----+----+----+----
// 996 |                X
// 897 |       X        X X            X
// 799 |  X    X X   X  X X    X       X                X
// 701 |  XX   X X   X  XXX    X      XX   XXX    X   X XX
// 602 |  XX   X X  XX  XXX X  X      XX  XXXX    XX  X XX
// 504 |  XX   XXX  XX  XXX XX X      XXX XXXX XX XX  X XX
// 406 |  XX X XXX XXXX XXX XX X  XXX XXX XXXXXXXXXX  X XX
// 307 | XXX X XXX XXXXXXXXXXX X XXXX XXXXXXXXXXXXXXX X XX
// 209 | XXX XXXXXXXXXXXXXXXXX XXXXXX XXXXXXXXXXXXXXXXX XX
// 111 | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  13 |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//      +----+----+----+----+----+----+----+----+----+----
//      0    5    10   15   20   25   30   35   40   45
void print_graph(int *data, int len, int max_height) {
  // global variable declaration
  int max;
  int min;
  int range;
  double units_per_height;

  // finding max and min in the *data array
  min = data[len-1];
  max = data[len-1];
  for( int i = 0; i < len-1; i++) {
    // find min here
    if( data[i] < min) {
      min = data[i];
    }
    // find max here
    else if (data[i] > max) {
      max = data[i];
    }
  }
  // finding the range of the data set
  range = max - min;
  // finding the units per height
  units_per_height = (double)range/max_height;
  // printing the important messaage here:
  printf("length: %d\n", len);
  printf("min: %d\n", min);
  printf("max: %d\n", max);
  printf("range: %d\n", range);
  printf("max_height: %d\n", max_height);
  printf("units_per_height: %.2f\n", units_per_height);

  // setting the top axies
  printf("     ");
  // printing the top edge line here
  for( int i = 0; i < len ; i++) {
    if ( i%5 != 0) {
      printf("-");
    } else {
      printf("+");
    }
  }
  printf("\n");

  // drawing the tree here
  for ( int level = max_height; level >= 0; level--) {
    // calculating the cutting off value here
    int cutoff_value = min + level * units_per_height;
    printf("%3d |", cutoff_value);
    // setting X here
    for (int i = 0; i < len; i++) {
      if (data[i] < cutoff_value) {
        printf(" ");
      }
      else {
        printf("X");
      }
    }
    printf("\n");
  }

  // the bottom axis here
  printf("     ");
  // printing the top edge line here
  for( int i = 0; i < len ; i++) {
    if ( i%5 != 0) {
      printf("-");
    } else {
      printf("+");
    }
  }
  printf("\n");

  // setting the top axies
  printf("     ");
  // printing the number part
  for( int i = 0; i < len ; i+=5) {
      printf("%-5d", i);
  }

  
  printf("\n");

}
