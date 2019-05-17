cmake_minimum_required (VERSION 2.6)
project (c_code)


set(external_libraries)
set( LIME_HOME CACHE PATH "path to the c-lime library installation" )
if( LIME_HOME )
  link_directories(${LIME_HOME}/lib)
  include_directories(${LIME_HOME}/include)
  list(APPEND external_libraries "-llime")
else()
  message(FATAL_ERROR "LIME_HOME must be defined!" )
endif()

add_library(read_lime_spinor 
	read_lime_spinor.c 
	read_binary_spinor_data.c
	big_endian.c
	byte_swap_assign.c
	byte_swap_assign_single2double.c
	single2double.c)
add_executable(contraction contraction.c)
add_executable(lime_test lime_test.c)

target_link_libraries(contraction 
	read_lime_spinor 
	${external_libraries})
target_link_libraries(lime_test ${external_libraries})
