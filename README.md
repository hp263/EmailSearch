A big string search test
===========
we use `Bloomfilter` and `Trie` to find it in ten million emails.As input files isn't a regular email string,we use some function to filter that email address.<br>
This is first homework in bupt proggramming course.The program is used to search one hundred email addresses in ten million which is not case sensitive.If it appeared,print "yes",or print "no".

BloomFilter
--------
To achieve it ,I use BloomFilter algrithm.In order to build a index ,I use a 28M bit array to store the it.
BloomFilter has some files as follows:
* bloom.h
* bloom.c
* main.c
* hash.h
* hash.c

Trie
-----
Trie is a traditional ways,which use an array as the sub-trie point.This data struct like this:<br>
```c
struct trieTree{
	int isEmail;
	struct trieTree *next[63];
};
```
<br>
This structure and achieve it in trie.c and trie.h files.In this way,we can easily build a trie tree.Obviously,it costs a lot of memory.We test this program in our server,but it only build 5 million email address in 60 gigabytes.<br>
So we change it , we change the array into list.A lot of memory can be saved.We use the struct like this:<br>
```c
typedef struct sNodeList NODELIST;
typedef struct trieTree TRIE;

struct sNodeList {
	char cNode;
	TRIE *tnext;
	struct sNodeList *next;
};

struct trieTree{
	 int isEmail;
	 struct sNodeList *list;
};
```
In this way,we use 15.23 gigabytes memory.It also costs too large.So we changedour way to acheive compress trie tree.

Compressed Trie
------------
A traditional Trie tree store a char to indicate the letter in emails.But in compressed trie,we use a string to indicate email.It can save more memory,but also cost more time.This is a compressed trie insertion:

[![insert]](http://dsqiu.iteye.com/blog/1705697)
[insert]:https://github.com/qhsong/BloomFilter/blob/master/compressedtrie.jpg
For compressed trie node,it save a string which those emails have common head file.<br>
We use this struct to save it in clisttrie.c and clisttrie.h .
```c
	typedef struct sNodeList NODELIST;
	typedef struct trieTree TRIE;

	struct sNodeList {
	    char *cNode;
	    TRIE *tnext;
	    struct sNodeList *next;
	};



	struct trieTree{
	   int isEmail;
	   struct sNodeList *list;
	};
```
It use approximately 1.2 gigabytes memory.But is it the limit?Absolutely not.We change this tree to binary tree.It can save more memory.The struct like this:
```c
typedef struct trieTree TRIE;


struct trieTree{
	short int isEmail;
	char *str;
	TRIE *bro;
	TRIE *son;
};
```

It use 1 gigabytes to finish find the program.</br>

Finally
========
This is a first homework in bupt. Use github to save my code .I like it.<br>

[Visit my blog](http://sqh.me/)
