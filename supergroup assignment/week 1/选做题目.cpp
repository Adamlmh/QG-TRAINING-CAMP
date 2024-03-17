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

// �ҵ���������м�ڵ�
struct Node* findMiddleNode(struct Node* head) {
    if (head == NULL || head->next == NULL)
        return head;

    struct Node *slow = head;
    struct Node *fast = head;

    // ��ָ��ÿ������������ָ��ÿ����һ��
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
	slow->next=NULL;
    // ������ָ�����ڵĽڵ㣬��Ϊ�м�ڵ�
    printList(slow);
    return slow;
}
// �жϵ������Ƿ�ɻ�
bool hasCycle(struct Node *head) {
    if (head == NULL || head->next == NULL)
        return false;

    struct Node *slow = head;
    struct Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;        // ��ָ��ÿ���ƶ�һ��
        fast = fast->next->next;  // ��ָ��ÿ���ƶ�����

        // �����ָ��׷������ָ�룬������ɻ�
        if (slow == fast)
            return true;
    }

    // �����ָ�뵽������ĩβ���������ɻ�
    return false;
}

//������ת����
struct Node* reverseList(struct Node *head){
	struct Node *prev=NULL;
	struct Node *curr=head;
	struct Node *next=NULL;
	while(curr!=NULL){
		next=curr->next;   //����ڵ�
		curr->next=prev;	//��תָ��	 
		prev=curr;			//��ǰ����
		curr=next;
	}
	printList(prev);
	return prev;
}
//�ݹ鷴ת����
struct Node* reverseListRecursive(struct Node *head){
	if(head==NULL||head->next==NULL) //��һ����� �ݹ������
	{
		return head;
	}
	struct Node *newHead =reverseListRecursive(head->next);
	//��ֳ���ͬ������
	//��ͬ�������
	head->next->next=head;
	head->next=NULL;
	return newHead;
}

void gotoxy(int x, int y)
{
    COORD pos = { x,y }; // ������ʾ��λ��
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ��׼����豸���
    SetConsoleCursorPosition(hOut, pos); //���������ֱ���ָ���ĸ����壬����λ��
}

void menu()
{
    printf("====================\n");
    printf("[A]\tcreatList\n");
    printf("[B]\tprintList\n");
    printf("[C]\tchangeList\n");
    printf("[D]\tfindMiddleNode\n");
    printf("[E]\thasCycle\n");
    printf("[F]\treverseList\n");
    printf("[G]\treverseListRecursive\n");
    printf("[H]\texit\n");
    printf("====================\n");
}

void show(int line)
{
    gotoxy(0, 0);
    menu();
    gotoxy(0, line);  // ѡ�еĸ�����ɫ
    if (line == 1)
        printf("\033[1;34;45m[A]\tcreatList\n\033[0m");
    if (line == 2)
        printf("\033[1;34;45m[B]\tprintList\n\033[0m");
    if (line == 3)
        printf("\033[1;34;45m[C]\tchangeList\n\033[0m");
    if (line == 4)
        printf("\033[1;34;45m[D]\tfindMiddleNode\n\033[0m");
    if (line == 5)
        printf("\033[1;34;45m[E]\thasCycle\n\033[0m");
    if (line == 6)
        printf("\033[1;34;45m[F]\treverseList\n\033[0m");
    if (line == 7)
        printf("\033[1;34;45m[H]\treverseListRecursive\n\033[0m");
     if (line == 8)
        printf("\033[1;34;45m[I]\texit\n\033[0m");       
}

void menu_control()
{
    char c1, c2, ch;
    int line, sec;
    long long j;
    time_t t;
    struct Node *pt=NULL;
    struct tm* lt;

    while(1)
    { 
        system("cls");   //ϵͳ����
        system("color 79");  //���ÿ���̨����ɫ
        Beep(2000, 250); //ϵͳ���� 
        menu(); //��ʾ�˵�
        line = 1;
        gotoxy(0, line); //�ƶ���굽��һ�е���λ��
        printf("\033[1;34;45m[A]\tInput\n\033[0m"); //Ĭ�ϲ˵���һ�и�����ɫ

        for (; (c1 = _getch()) != '\r';)  // ��ȡ����ֵ������'\r'�س������
        { //ע���û���ͷ������������ַ�����:
          //LEFT(-32,75), UP(-32,72), DOWN(-32,80),Right(-32,77)
            if (c1 == -32)
            {
                c2 = _getch(); //��ð����ĵڶ�����ֵ�������ݷ���ѡ��˵�����
                ch = c2;
                if (ch == upkey && line != 1)
                {
                    line--;
                    show(line);
                    continue;
                }
                else if (ch == downkey && line != 8)
                {
                    line++;
                    show(line);
                    continue;
                }
                else if (ch == upkey && line == 1)
                {
                    line = 8;
                    show(line);
                    continue;
                }
                else if (ch == downkey && line == 8)
                {
                    line = 1;
                    show(line);
                    continue;
                }
            }

            if (c1 == 'a' || c1 == 'A')
            {
                system("cls");   //ϵͳ����
                gotoxy(0, 0);    //���ص���ʼλ��
                pt=creatList();
                line = 0;
                break;
            }
            else if (c1 == 'b' || c1 == 'B')
            {
                system("cls");
                gotoxy(0, 0);
                printList(pt);
                line = 0;
                break;
            }
            else if (c1 == 'c' || c1 == 'C')
            {
                system("cls");
                gotoxy(0, 0);
                changeList(pt);
                line = 0;
                break;
            }
            else if (c1 == 'd' || c1 == 'D')
            {
                system("cls");
                gotoxy(0, 0);
                findMiddleNode(pt);
                line = 0;
                break;
            }
            else if (c1 == 'e' || c1 == 'E')
            {
                system("cls");
                gotoxy(0, 0);
                int b;
                b=hasCycle(pt);
                if(b==1)
                {
                	printf("����Ϊѭ������\n");
				}
				else{
					printf("������ѭ������\n");
				}
                line = 0;
                break;
            }
            else if (c1 == 'f' || c1 == 'F')
            {
                system("cls"); 
                gotoxy(0, 0);
                reverseList(pt);
                line = 0;
                break;
            }
            else if (c1 == 'g' || c1 == 'G')
            {
                system("cls"); 
                gotoxy(0, 0);
                reverseListRecursive(pt);
                line = 0;
                break;
            }
            else if (c1 == 'h' || c1 == 'H')
            {
                system("cls"); 
                gotoxy(0, 0);
                exit(0);
                line = 0;
                break;
            }       			                                           
        }

        if (line == 1)
        {
            system("cls");
            gotoxy(0, 0);
            pt=creatList();
        }
        else if (line == 2)
        {
            system("cls");
            gotoxy(0, 0);
            printList(pt);
        }
        else if (line == 3)
        {
            system("cls");
            gotoxy(0, 0);
            changeList(pt);
        }
        else if (line == 4)
        {
            system("cls");
            gotoxy(0, 0);
            findMiddleNode(pt);
        }
        else if (line == 5)
        {
            system("cls");
            gotoxy(0, 0);
                int b;
                b=hasCycle(pt);
                if(b==1)
                {
                	printf("����Ϊѭ������\n");
				}
				else{
					printf("������ѭ������\n");
				}
        }
        else if (line == 6)
        {
            system("cls");
            gotoxy(0, 0);
            reverseList(pt);
        }
        else if (line == 7)
        {
            system("cls");
            gotoxy(0, 0);
            reverseListRecursive(pt);
        }
        else if (line == 8)
        {
            system("cls");
            gotoxy(0, 0);
                exit(0);
        }        
        /*j = pow(10, 10); 
        while (j--); */  

        time(&t); //��ȡʱ���
        lt = localtime(&t); // תΪʱ��ṹ
        sec = lt->tm_sec;
        // printf("time is: %d/%d/%d %d:%d:%d\n", lt->tm_year + 1900, lt->tm_mon, lt->tm_mday, lt->tm_hour,lt->tm_min, lt->tm_sec);

        do   // ��ʱһ��
        {
            time(&t); //��ȡʱ���
            lt = localtime(&t); // תΪʱ��ṹ
            j = lt->tm_sec - sec;
            if (j < 0) j = j + 60;
         //   printf("time is: %d-%d\n", lt->tm_sec, sec);
        } while (j < 3);
    }
}
int main()
{
	menu_control();
	return 0;
}
