#include<stdio.h>
#include<string.h>
#include<time.h>
#include"bloom.h"

int main(int argc, char *argv[])
{
	clock_t start=clock(),end;
	if(argc<2) {
		fprintf(stderr, "ERROR: No word file specified\n");
		return EXIT_FAILURE;
	}
	FILE*fp_strpool=fopen(argv[1],"r");
	FILE*fp_checkedstr=fopen(argv[2],"r");
	FILE*fp_result=fopen(argv[3],"w");
	
	int check_result=bloom_check(fp_strpool,fp_checkedstr,fp_result);
	
	fclose(fp_strpool);
	fclose(fp_checkedstr);
	fclose(fp_result);
	end = clock();
	printf("%f\n",(double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}
