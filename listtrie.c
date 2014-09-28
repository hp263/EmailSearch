#include<limits.h>

#include "listtrie.h"

#define BUFFERSIZE 1024


NODELIST* node_find(NODELIST *l,char c) {
	while(l != NULL ){
		if( l->c == c) break;
		l = l->next;
	}
	return l;
}

TRIE* trie_create(){
	TRIE *p = (TRIE *)malloc(sizeof(TRIE));
	p->isEmail = false;
	p->list = NULL;
	return p;
}

void trie_destroy(TRIE **head) {
	NODELIST *p,*q;
	p = (*head)->list;
	while(p){
		trie_destroy(&(p->tnext));
		q = p;
		p = p->next;
		free(q);
	}
	free(*head);
}


int trie_add(TRIE **head,char *str) {
	TRIE *t = *head;
	while(str && *str != '\r' && *str !='\n'){
		NODELIST *l = node_find(t->list,*str);
		if(l){
			t = l->tnext;
		}else{
			NODELIST *p = t->list;
			NODELIST *q = p;
			while( p!= NULL) {
				q = p;
				p = p->next;
			}
			if(q){
				q->next = (NODELIST *)malloc(sizeof(NODELIST));
				q = q->next;
			}else{
				q = (NODELIST *)malloc(sizeof(NODELIST));
				t->list = q;
			}
			q->c = *str;
			q->next = NULL;
			q->tnext = (TRIE *)malloc(sizeof(TRIE));
			t = q->tnext;
			t->list = NULL;
		}
		str++;
	}
	t->isEmail = true;
	return 0;
}

int trie_check(TRIE **head,char *str) {
	TRIE *t = *head;
	while(t!=NULL && !t->isEmail && *str!='\r' && *str) {
		NODELIST *l = t->list;
		l = node_find(l,*str);
		if(!l){
			t = NULL;
			break;
		}
		t = l->tnext;
		str++;
	}

	if(t==NULL) {
		return 0;
	}else {
		return t->isEmail;
	} 

}

void trie(FILE *pool,FILE *check,FILE *result) {
	TRIE *head = trie_create();
	char line[BUFFERSIZE];
	int count=0;
	while(fgets(line,BUFFERSIZE,pool)) {
		trie_add(&head,line);
		if(!(++count%100000))	printf("%d\n",count);
/*		printf("%s",trie_check(&head,line)?"Yes":"No") ;*/
	}
	while(fgets(line,BUFFERSIZE,check)) {
		if(trie_check(&head,line)) {
			fprintf(result,"yes\n");
		}else {
			fprintf(result,"no\n");
		}
	}
	trie_destroy(&head);
}
