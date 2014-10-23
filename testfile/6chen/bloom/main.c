#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char *argv[])
{
	clock_t start,end;
	start = clock();	
	FILE *fp_strpool, *fp_checkedmail, *fp_result;
	fp_strpool = fopen(argv[1],"r");
	fp_checkedmail = fopen(argv[2],"r");
	fp_result = fopen(argv[3],"w");

	hash_check(fp_strpool,fp_checkedmail,fp_result);
	//printf("Done!\n");
	//getchar();	
	fclose(fp_strpool);
	fclose(fp_checkedmail);	
	fclose(fp_result);
	end = clock();
	printf("%f\n",(double)(end-start)/CLOCKS_PER_SEC); 
	getchar();
}
