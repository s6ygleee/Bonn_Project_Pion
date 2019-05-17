#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<lime.h>
#include<string.h>
#include "read_lime_spinor.h"

void * single2double(void * out_ptr, void * in_ptr, int nmemb) {
  int i;
  float * float_ptr = (float*) in_ptr;
  double * double_ptr = (double*) out_ptr;

  for(i = 0; i < nmemb; i++) {
    (*double_ptr) = (double) (*float_ptr);

    float_ptr++;
    double_ptr++;
  }
  return(out_ptr);
}
