#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<lime.h>
#include<string.h>
#include "read_lime_spinor.h"


int read_binary_spinor_data(double * const s, LimeReader * limereader, const int prec){

  int status=0;
  n_uint64_t bytes, ix;
  double tmp[24];
  float tmp2[24];
  int words_bigendian;
  int t, x, y, z;
  int T=40, LX=16, LY=16, LZ=16;

  words_bigendian = big_endian();
  
  if(prec == 32) bytes = 24*sizeof(float);
  else bytes = 24*sizeof(double);
  for(t = 0; t < T; t++)
  {
	  for(x = 0; x < LX; x++)
      	  {
		  for(y = 0; y < LY; y++)
		  {
		  	  for(z = 0; z < LZ; z++)
		  	  {
				  ix = (t*LX*LY*LZ+x*LY*LZ+y*LZ+z)*(n_uint64_t)12;
				  if(prec == 32){	    status = limeReaderReadData(tmp2, &bytes, limereader);	  }
				  else{	    status = limeReaderReadData(tmp, &bytes, limereader);
			              }

				  if(!words_bigendian) 
				  {
			      		  if(prec == 32)
					  {	      byte_swap_assign_single2double(&s[2*ix], (float*)tmp2, 24);	    }
			      		  else 	    	{	      byte_swap_assign(&s[2*ix], tmp, 24);
						                    //  printf("%d\n",ix);
			                                              //printf("%d %e %e\n",ix,s[2*ix],s[2*ix+1]);
								      		  }
				  }
			
				  else 
				  {
			      		  if(prec == 32)  {	      single2double(&s[2*ix], (float*)tmp2, 24);	    }
			      		  else memcpy(&s[2*ix], tmp, bytes);
				  }
				  if(status < 0 && status != LIME_EOR) 	{	    return(-1);	  }
			  }
		  }
	  }
  }
  return(0); 
}



