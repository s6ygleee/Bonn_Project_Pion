#ifndef READ_LIME_SPINOR_H
#define READ_LIME_SPINOR_H
#include <lime.h>
int read_lime_spinor(double * const s, char const * const filename, const int position);
int read_binary_spinor_data(double * const s, LimeReader * limereader, const int prec);
void * single2double(void * out_ptr, void * in_ptr, int nmemb);
int big_endian();
void * byte_swap_assign(void * out_ptr, void * in_ptr, int nmemb);
void * byte_swap_assign_single2double(void * out_ptr, void * in_ptr, int nmemb);
#endif // READ_LIME_SPINOR_H

