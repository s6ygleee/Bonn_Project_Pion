#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<lime.h>
#include<string.h>
#include "read_lime_spinor.h"


int main(void){

//variables
	FILE * in;
	FILE * out;
	FILE * ifs;
	char ifile[90];
     	int T=40, LX=16, LY=16, LZ=16;
    	double p, C[157][T];
    
	int status=0;
    	int t, x, y, z, i, k;
    	int v, q;
	int position;
    	double * s[12];
      
	int getpos=-1;
      	char * header_type;
      	LimeReader * limereader;
    


//memory allocation
	for(k=0; k<12 ; k++)
    	{
		s[k]=(double*)malloc(sizeof(double)*LX*LY*LZ*T*24);
    	}
	

//array initailizing
	for(v=0; v<157; v++)
    	{
		for(t=0; t<T; t++)
		{
			C[v][t]=0;
		}
	}


//sci-dac data position finding

	ifs = fopen("/hiskp4/bartek/inversions/quenched/wilson-b5.85_L16T40/mu0.005/source.0114.00.11.inverted","r");
	limereader = limeCreateReader(ifs);
    
	for(v=0; v<20; v++)
    	{
		getpos=-1;    
		if (ifs == NULL)
		{
			printf("Cannot open the file.\n");
			return 1;
		}
	
		if( limereader == (LimeReader *)NULL ) 
		{
			fprintf(stderr, "[read_lime_spinor] Unable to open LimeReader\n");
			return(-1);
		}
	
		while( (status = limeReaderNextRecord(limereader)) != LIME_EOF )
		{
			header_type = limeReaderType(limereader);
			if(strcmp("scidac-binary-data",header_type) == 0)
			{
				getpos++;
				printf("\nHere you go, \nCurrently getpos is %d and the scidac-binary-data position is %d\n\n", getpos, v);
			       	position=v;	
			}
		}
    	}
	limeDestroyReader(limereader);
	fclose(ifs);



	 	

//main function
for(v=0; v<157; v++)
{
    for(k=0; k<12 ; k++)
    {
	q=snprintf(ifile, 90, "/hiskp4/bartek/inversions/quenched/wilson-b5.85_L16T40/mu0.005/source.%04d.00.%02d.inverted", v+30, k);
	if(q>=90)
	{printf("Terminate the program. File name is too long\n");
	return 1;}

	status=read_lime_spinor(s[k], ifile, 0); //update data from source file to s[k]

	
	if(status < 0 && status != LIME_EOR)
	{	
		printf("read lime spinor status is not correct. %dth trial\n",k);
		return(-1);
	}


	for(t = 0; t < T; t++)
	{
		p=0;
		for(x = 0; x < LX; x++)
		{
			for(y = 0; y < LY; y++)
			{
				for(z = 0; z < LZ; z++)
				{
					for(i = 0; i< 24; i++)
					{ 
						p+=s[k][(t*LX*LY*LZ+x*LY*LZ+y*LZ+z)*24+i]*s[k][(t*LX*LY*LZ+x*LY*LZ+y*LZ+z)*24+i]; 
						//data storage linearlization
					}
				}
			}
		}

		C[v][t]+=p;

	}
    }
}






    

// print result
    for(v = 0; v < 157; v++)
    {
	for(t = 0; t < T; t++)
    	{
    		printf("Correlation function value at contraction %d, t=%2d is %f\n",v+30,t,C[v][t]);
    	}
    }





//save data on file
	out=fopen("mu0.005_correlation.txt","w");
    	for(v = 0; v < 157; v++)
	{
		for(t = 0; t < T; t++)
    		{
    		fprintf(out,"%2d	%10e\n",t,C[v][t]);
    		}
   	}
	fclose(out);



// closing
    for(v = 0; v < 157; v++)
    {
	for(t = 0; t < T; t++)
    	{
    		C[v][t]=0;
    	}
    }

    for(k=0; k<12 ; k++)
    {
	    	free(s[k]);
    }

    return 0;
}
