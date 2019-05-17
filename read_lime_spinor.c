#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<lime.h>
#include<string.h>
#include "read_lime_spinor.h"


int read_lime_spinor(double * const s, char const * const filename, const int position)
{
  FILE * ifs;
  int status=0, getpos=-1;
  n_uint64_t bytes;
  char * header_type;
  LimeReader * limereader;
  n_uint64_t prec = 32;
  int T=40, LX=16, LY=16, LZ=16;

  if((ifs = fopen(filename, "r")) == (FILE*)NULL) 
  {
    fprintf(stderr, "[read_lime_spinor] Error opening file %s\n", filename);
    return(-1);
  }

  
  limereader = limeCreateReader( ifs );


  if( limereader == (LimeReader *)NULL ) 
  {
    fprintf(stderr, "[read_lime_spinor] Unable to open LimeReader\n");
    return(-1);
  }
  
  while( (status = limeReaderNextRecord(limereader)) != LIME_EOF ) 
  {
    if(status != LIME_SUCCESS ) 
    {
      fprintf(stderr, "[read_lime_spinor] limeReaderNextRecord returned error with status = %d!\n", status);
      status = LIME_EOF;
      break;
    }
    header_type = limeReaderType(limereader);
    if(strcmp("scidac-binary-data",header_type) == 0) getpos++;
    if(getpos == position)	    break;
  }

  bytes = limeReaderBytes(limereader);

  
  if(bytes == (LX)*(LY)*(LZ)*T*(uint64_t)(24*sizeof(double))) prec = 64;
  else if(bytes == (LX)*(LY)*(LZ)*T*(uint64_t)(24*sizeof(float))) prec = 32;
  else 
  {
    fprintf(stderr, "[read_lime_spinor] wrong length in eospinor: bytes = %llu, not %llu. Aborting read!\n", 
	    bytes, (LX)*(LY)*(LZ)*T*(uint64_t)(24*sizeof(double)));
    return(-1);
  }
  
  status = read_binary_spinor_data(s, limereader, prec);

  limeDestroyReader(limereader);
  fclose(ifs);
  return(0);
}




