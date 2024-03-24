#define _CRT_SECURE_NO_WARNINGS
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<ctype.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#define upkey 72
#define downkey 80
#define leftkey 75
#define rightkey 77
#define LEN sizeof(StackNode)
typedef enum Status
{
	wrong = 0,
	OK = 1
} Status;

typedef int ElemType;

typedef  struct StackNode
{
	ElemType data;
	struct StackNode* next;
}StackNode, * LinkStackPtr;

typedef  struct  LinkStack
{
	LinkStackPtr top;//ջ��ָ��
	int	count;//Ԫ�ظ���
}LinkStack;



//��ջ
Status initLStack(LinkStack* s);//��ʼ��ջ
Status isEmptyLStack(LinkStack* s);//�ж�ջ�Ƿ�Ϊ��
Status getTopLStack(LinkStack* s, ElemType* e);//�õ�ջ��Ԫ��
Status clearLStack(LinkStack* s);//���ջ
Status destroyLStack(LinkStack* s);//����ջ
Status LStackLength(LinkStack* s, int* length);//���ջ����
Status pushLStack(LinkStack* s, ElemType data);//��ջ
Status popLStack(LinkStack* s, ElemType* data);//��ջ
void menu();//�˵�

#endif 
