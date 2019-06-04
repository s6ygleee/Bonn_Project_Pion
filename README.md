# Project_Pion

Calcualte Pion+ two point function correlator


## Main-codes

contraction.c : Main calculation function which save the pion two point correlator with time values data as txt file
  
read_lime_spinor.c : read data from source file and update in point array, using lime library

read_binary_spinor_data.c : reading binary data from source file

read_lime_spinor.h : Header file for using read_lime_spinor


## Functional-codes

single2double.c : change data storage type from float to double

big_endian.c : change small endian data to big endian data

byte_swap_assign.c : swap the data oder of the data set

byte_swap_assign_single2double.c : swap the data oder of the data set and change out put data type to double
