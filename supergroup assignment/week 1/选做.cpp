#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#define upkey 72
#define downkey 80
#define leftkey 75
#define rightkey 77
#define LEN sizeof(struct Node)
#define len sizeof(struct spiltList)
#define L 30
//����˼·����ÿ�����ֳܷ�ÿ������ʵ��
//�����ṹ��
struct Node{
	char data[20]={0};
	int num;
	struct Node *next;
};

struct spiltList{
	struct Node *odd;
	struct Node *even;
};
//��������
struct Node *creatList(){
	int n = 0;
	struct Node *head;
	struct Node *p1,*p2;
	head=NULL;
	p1=p2=(struct Node *) malloc(LEN);
	printf("�������ַ�����,�س�����\n");
	gets(p1->data);
	while(strlen(p1->data)!=0)
	{
		n++;
		if(n==1)
		{
			head=p1;
		}
		else{
			p2->next=p1;
		}
		p1->num=n;
		p2=p1;
		p1=(struct Node *)malloc(LEN);
		printf("�������ַ�����,�س�����\n");
		gets(p1->data);
	}
	p2->next=NULL;
	return head;
}

//��ӡ����
void printList(struct Node *head)
{
	struct Node *p;
	p=head;
	if(p==NULL)
	{
		printf("������");
	}
	while(p!=NULL)
	{
		printf("%s %d \n",p->data,p->num);
		p=p->next;
	}
}



//����ֲ�
struct spiltList *divide(struct Node *head){
	struct Node *odd;
	struct Node *even;
	struct spiltList *spiltList;
	struct Node *oddPoint;
	struct Node *evenPoint;
	struct Node *current;
	spiltList=(struct spiltList *)malloc(len);
	if(head==NULL)
	{
		spiltList->odd=NULL;
		spiltList->even=NULL;
		printf("�������޷����");	
		return spiltList;
	}
	if(head->next==NULL){
	spiltList->even=NULL;	
	spiltList->odd=head;
	odd=head;
	even=NULL;
	printList(odd);
	printList(even);			
	return spiltList;
	}
	odd=oddPoint=head;
	even=evenPoint=head->next;
	current=even->next;
	int n=3;
	while(current!=NULL){
		if(n%2==1){
			oddPoint->next=current;
			oddPoint=current;
		}
		else{
			evenPoint->next=current;
			evenPoint=current;
		}
		n++;
		current=current->next;
	}
	evenPoint->next=NULL;
	oddPoint->next=NULL;
	spiltList->odd=odd;
	spiltList->even=even;
	return spiltList;	
}

//��������ż����
struct Node *changeList(struct Node *head){
	if(head==NULL||head->next==NULL)
	{
		return head;
	}
	struct Node *newHead;
	struct Node *odd;
	struct Node *even;
	struct Node *oddPoint;
	struct Node *evenPoint;	
	struct spiltList *p = (divide(head));
	odd=p->odd;
	even=p->even;
	newHead=even;
	int n=1;
	//��������
	while(1){
		if(even==NULL)
		{
			break;
		}
		if(n%2==1)
		{
		evenPoint=even->next;
		even->next=odd;
		even=evenPoint;
		}
		else{
		oddPoint=odd->next;
		odd->next=even;
		odd=oddPoint;
		}
		n++;
	}
	oddPoint=oddPoint->next;
	if(oddPoint!=NULL)
	{
		odd->next=oddPoint;
		odd->next->next=NULL;
	}
	printList(newHead);
	return newHead;	
}

int main()
{
	changeList(creatList());
}