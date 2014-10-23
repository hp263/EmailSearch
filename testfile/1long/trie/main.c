#include<stdio.h>
#include<time.h>

#include"trie.h"

int main(int argc, char *argv[])
{
/*
	FILE *fp;
	char line[1024];
	char *p;
	
	if(argc<2) {
		fprintf(stderr, "ERROR: No word file specified\n");
		return EXIT_FAILURE;
	}
*/
	clock_t end,start;
	start=clock();
	
	trie_check();

	end=clock();

	printf("%f\n",(double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}
