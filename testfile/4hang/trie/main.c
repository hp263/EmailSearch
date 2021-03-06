#include<stdio.h>
#include<string.h>
#include<time.h>
#include "trie.h"



int main(int argc, char *argv[])
{
	
	clock_t start = clock(),end;
	if(argc<2) {
	    fprintf(stderr, "ERROR: No word file specified\n");
	    return EXIT_FAILURE;
	}
	/*printf("set ambition files\n");*/
	FILE *fpEmailPool = fopen(argv[1],"r");
	if(fpEmailPool==NULL)
		printf("file1 missing.\n");
	FILE *fpCheckedEmail = fopen(argv[2],"r");
	if(fpCheckedEmail==NULL)
		printf("file2 missing\n");
	FILE *fpResult = fopen(argv[3],"w");
	if(fpResult==NULL)
		printf("file3 missing.\n");
	//printf("Counting!!!!!\n");
	trieCheck(fpEmailPool,fpCheckedEmail,fpResult);
	
	fclose(fpResult);
	fclose(fpCheckedEmail);
	fclose(fpEmailPool);
        end = clock();
	printf("%f\n",(double)(end-start)/CLOCKS_PER_SEC);
        //printf("The total consumtion of time is %d min %d second.\n",Min,Sec);
	return 0;
}	
