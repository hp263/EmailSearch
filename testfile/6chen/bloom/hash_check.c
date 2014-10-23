#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define LENGTH 500//邮箱字符串长度
#define CHECKNUM 100//待查邮箱个数
#define ARRLEN 1024*1024*4//申请数组的长度

struct node{
	short postnum;
	struct node *next;
	long offset;//记录偏移值
};//共32个字节
struct node *arr[ARRLEN] = {NULL};//22位
unsigned int i = 0;	
long offset = 0, postOffset = 0;
int yes = 0, no = 0;

int hash_check(FILE *fp_strpool, FILE *fp_checkedmail, FILE *fp_result)
{
	//printf("Initializing the index table......\n");
	char email[LENGTH];
	while(fgets(email,LENGTH,fp_strpool) != NULL)//创建搜索表
	{
		i++;
//if(i % 100000 == 0)
	//printf("%d%% \n",i/100000);//百分比提示信息		
		unsigned int code1;;		
		postOffset = ftell(fp_strpool);//这是下一个邮箱的offset，需保留
		code1 = getCode(email);//得到该邮箱的哈希码
		int pos = preBits(code1);		
		short value = postBits(code1);	
		//新建一个节点
		struct node *newNode = (struct node *)malloc(sizeof(struct node));
		newNode->postnum = value;
		newNode->next = NULL;
		newNode->offset = offset;
		//安插节点	
		if(arr[pos] == NULL)
			arr[pos] = newNode;
		else
		{
			struct node *p = arr[pos];
			while(p->next != NULL)
				p = p->next;
			p->next = newNode;
		}					

		offset = postOffset;
	}
//printf("Index table compelete.\n");
	//printf("Searching emails......\n");
	for(i = 0; i < CHECKNUM; i++)//开始匹配	
	{
		int flag = 0;
		char email[LENGTH];
		unsigned int code2;
		//得到一条邮箱，放入email中
		fgets(email,LENGTH,fp_checkedmail);
		code2 = getCode(email);
		int pos = preBits(code2);//得到应该映射到的位置
		
		if(arr[pos] == NULL)//如果这个位置是空，说明一定不存在
		{
			fprintf(fp_result,"no\n");
			//printf("The %dth email does not exist.\n",i + 1);
			no++;
			continue;
		}
		else//否则需要进一步确认哈希码是否相同，后半部分哈希码在节点中，所以应该遍历该位置的所有
		{
			struct node *p = arr[pos];
			short value = postBits(code2);
			while(p != NULL)
			{
				if(value == p->postnum) //如果相同，说明有可能是同一邮箱，所以根据offset取出邮箱字符串进行比较
				{
					char tmp[LENGTH];										
					//从文件中读取第p->line行的字符串
					fseek(fp_strpool,p->offset,0);
					fgets(tmp,LENGTH,fp_strpool);
					if(strcasecmp(email, tmp) == 0)//匹配成功
					{
						flag = 1;
						fprintf(fp_result,"yes\n");
						//printf("The %dth email's line is exist\n",i + 1);
						yes++;					
						break;
					}
				}
				p = p->next;//如果后半部分不相等，或者相等但是不匹配，就继续遍历
			}
			if(flag == 1)	continue;
			fprintf(fp_result,"no\n");
			//printf("The %dth email does not exist.\n",i + 1);
			no++;
		}
	}
	//printf("yes/no : %d/%d\n",yes, no);
}
