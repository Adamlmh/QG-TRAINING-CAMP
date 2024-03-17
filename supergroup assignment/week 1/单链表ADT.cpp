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
#define L 30
//����˼·����ÿ�����ֳܷ�ÿ������ʵ��
//������������ �������� ����ڵ� ɾ���ڵ�  ��ӡ���� �������� �ȹ���
//�����ṹ��
struct Node{
	char data[20]={0};
	int num;
	struct Node *next;
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

//��������
void destroyList(struct Node **head){
	struct Node *p1,*p2;
	p1=*head;
	while(p1!=NULL)
	{
		p2=p1->next;
		free(p1);
		p1=p2;
	}
	*head=NULL;
	printf("���ٳɹ�");
}

//����ڵ�
void insertNode(struct Node **head){
	//�����½ڵ�
	struct Node *newNode=(struct Node *)malloc(LEN);
	if(newNode == NULL)
	{
		printf("�ڴ����ʧ��");
		exit(1);
	}
	int insertNum;
	char insertdata[20];
	printf("���������ڵ�Ľڵ���");
	scanf("%d",&insertNum);
	printf("���������ڵ������");
	scanf("%s",newNode->data);
	newNode->num=insertNum;
	newNode->next = NULL;
	
	//������Ϊ�� ���½ڵ�ֱ��Ϊͷ�ڵ�
	if(*head==NULL)
	{
		newNode->num=1;
		*head=newNode;
		return;
	}
	//�ҵ�����λ��
	struct Node *p=*head;
	int t=1;
	while(p->next!=NULL && p->num<insertNum-1)
	{
		t++;
		p=p->next;
	}
	if(newNode->num!=t+1)
	{
		printf("����ռ��˷ѣ���������Ϊ%d",t+1);
	}
	newNode->num=t+1;
	//����ڵ�
	newNode->next=p->next;
	p->next=newNode;
	//���º����ڵ���
	newNode=newNode->next;
	while(newNode!=NULL)
	{
		newNode->num=newNode->num+1;
		newNode=newNode->next;		
	}
}

//ɾ���ڵ�
void deleteNode(struct Node **head)
{
    // �������Ϊ�գ�ֱ�ӷ���
    if (*head == NULL)
        return;
	int num;
	char data[20];
	printf("������Ҫɾ���Ľڵ���");
	scanf("%d",&num);
	printf("������Ҫɾ��������");
	scanf("%s",data);	
	// ���Ҫɾ���Ľڵ���ͷ�ڵ�
        struct Node *temp = *head;
		struct Node *prev = *head;	
    if ((strcmp((*head)->data, data) == 0)&&(*head)->num == num) {
        *head = (*head)->next;
        free(temp);
    }
	else{
		 // Ѱ��Ҫɾ���ڵ��ǰһ���ڵ�
		while(prev->next!=NULL)
		{
			if((strcmp(prev->next->data, data) == 0)&&prev->next->num==num)
			{
				break;
			}
			prev=prev->next;
		}
		// ���������û��Ҫɾ���Ľڵ�
		if(prev->next==NULL)
		{
		printf("û����Ҫɾ���Ľڵ�");
		return;			
		}
		// ɾ���ڵ�
		Node *temp=prev->next;
		prev->next=temp->next;
		free(temp);
		printf("ɾ���ɹ�");
	}
	//���º����ڵ���
	prev=prev->next;
	while(prev!=NULL)
	{
		prev->num=prev->num-1;
		prev=prev->next;		
	}
	return;	        
}
//��������
void findData(struct Node *head)
{
	printf("��������Ҫ���ҵ�����");
	char data[20];
	scanf("%s",data);
	while(head!=NULL)
	{
		if(strcmp(data,head->data)==0)
		{
			printf("���ݴ��ڵ�%d�ڵ�",head->num);
			return ;
		}
		head=head->next;
	}
	printf("���ݲ�����");
	return ;
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
    printf("[C]\tdestroyList\n");
    printf("[D]\tinsertNode\n");
    printf("[E]\tdeleteNode\n");
    printf("[F]\tfindData\n");
    printf("[G]\texit\n");
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
        printf("\033[1;34;45m[C]\tdestroyList\n\033[0m");
    if (line == 4)
        printf("\033[1;34;45m[D]\tinsertNode\n\033[0m");
    if (line == 5)
        printf("\033[1;34;45m[E]\tdeleteNode\n\033[0m");
    if (line == 6)
        printf("\033[1;34;45m[F]\tfindData\n\033[0m");
    if (line == 7)
        printf("\033[1;34;45m[H]\texit\n\033[0m");
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
                else if (ch == downkey && line != 7)
                {
                    line++;
                    show(line);
                    continue;
                }
                else if (ch == upkey && line == 1)
                {
                    line = 7;
                    show(line);
                    continue;
                }
                else if (ch == downkey && line == 7)
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
                destroyList(&pt);
                line = 0;
                break;
            }
            else if (c1 == 'd' || c1 == 'D')
            {
                system("cls");
                gotoxy(0, 0);
                insertNode(&pt);
                line = 0;
                break;
            }
            else if (c1 == 'e' || c1 == 'E')
            {
                system("cls");
                gotoxy(0, 0);
                deleteNode(&pt);
                line = 0;
                break;
            }
            else if (c1 == 'f' || c1 == 'F')
            {
                system("cls"); 
                gotoxy(0, 0);
                findData(pt);
                line = 0;
                break;
            }
            else if (c1 == 'g' || c1 == 'G')
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
            destroyList(&pt);
        }
        else if (line == 4)
        {
            system("cls");
            gotoxy(0, 0);
            insertNode(&pt);
        }
        else if (line == 5)
        {
            system("cls");
            gotoxy(0, 0);
            deleteNode(&pt);
        }
        else if (line == 6)
        {
            system("cls");
            gotoxy(0, 0);
            findData(pt);
        }
        else if (line == 7)
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
