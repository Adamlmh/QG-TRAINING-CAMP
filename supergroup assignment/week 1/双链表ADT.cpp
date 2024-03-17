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
//总体思路：将每个功能分成每个函数实现
//包括创建链表 销毁链表 插入节点 删除节点  打印链表 查找数据 等功能
//创建结构体
struct Node{
	char data[20]={0};
	int num;
	struct Node *prev;
	struct Node *next;
};

//创建双向链表
struct Node *creatList(){
	int n = 0;
	struct Node *headEndPointer;
	struct Node *head;
	struct Node *p1,*p2;
	head=NULL;
	p1=p2=(struct Node *) malloc(LEN);
	printf("请输入字符数组,回车结束\n");
	gets(p1->data);
	while(strlen(p1->data)!=0)
	{
		n++;
		if(n==1)
		{
			head=p1;
			head->prev=NULL;
		}
		else{
			p2->next=p1;
			p1->prev=p2;
		}
		p1->num=n;
		p2=p1;
		p1=(struct Node *)malloc(LEN);
		printf("请输入字符数组,回车结束\n");
		gets(p1->data);
	}
	p2->next=NULL;
	headEndPointer=(struct Node *) malloc(LEN);
	//通过一个新的节点同时返回头节点和尾节点
	//prev是头节点 next是未节点
	headEndPointer->prev=head;
	headEndPointer->next=p2;
	return headEndPointer;
}

//打印链表
void printList(struct Node *headEndPointer)
{
	struct Node *p;
	printf("请输入1代表从头到尾打印，输入其他数字代表从尾到头打印\n");
	int n;
	scanf("%d",&n);
	if(n==1)
	{
		p=headEndPointer->prev;
	}
	else{
		p=headEndPointer->next;
	}
	if(p==NULL)
	{
		printf("空链表");
	}
	while(p!=NULL)
	{
		printf("%s %d \n",p->data,p->num);
		if(n==1)
		{
		p=p->next;	
		}
		else{
		p=p->prev;
		}		
	}
}

//销毁链表
void destroyList(struct Node **headEndPointer){
	struct Node *p1,*p2;
	p1=*headEndPointer;
	p1=p1->prev;
	while(p1!=NULL)
	{
		p2=p1->next;
		free(p1);
		p1=p2;
	}
	(*headEndPointer)->next=NULL;
	(*headEndPointer)->prev=NULL;
	printf("销毁完成");
}

//插入节点
void insertNode(struct Node **headEndPointer){
	//创建新节点
	struct Node *newNode=(struct Node *)malloc(LEN);
	if(newNode == NULL)
	{
		printf("内存分配失败");
		exit(1);
	}
	int insertNum;
	char insertdata[20];
	printf("请输入插入节点的节点数");
	scanf("%d",&insertNum);
	printf("请输入插入节点的数据");
	scanf("%s",newNode->data);
	newNode->num=insertNum;
	newNode->next = NULL;
	
	//若链表为空 则新节点直接为头节点
	if(*headEndPointer==NULL)
	{
		newNode->num=1;
		*headEndPointer=newNode;
		(*headEndPointer)->prev=NULL;
		(*headEndPointer)->next=NULL;
		return;
	}
	//找到插入位置
	struct Node *p=*headEndPointer;
	p=p->prev;
	int t=1;
	while(p->next!=NULL && p->num<insertNum-1)
	{
		t++;
		p=p->next;
	}
	if(newNode->num!=t+1)
	{
		printf("避免空间浪费，插入结点数为%d",t+1);
	}
	newNode->num=t+1;
	//插入节点
	if(p->next==NULL)
	{
	newNode->prev=p;
	newNode->next=NULL;
	p->next=newNode;
	printf("插入成功");
	(*headEndPointer)->next=newNode;
	return ;
	}
	newNode->next=p->next;
	newNode->prev=p;
	p->next->prev=newNode;
	p->next=newNode;
	//更新后续节点数
	newNode=newNode->next;
	while(newNode!=NULL)
	{
		newNode->num=newNode->num+1;
		newNode=newNode->next;		
	}
	printf("插入成功");
}
//删除节点
void deleteNode(struct Node **headEndPointer)
{
	struct Node **head=&((*headEndPointer)->prev);
    // 如果链表为空，直接返回
    if (*head == NULL)
        return;
	int num;
	char data[20];
	printf("请输入要删除的节点数");
	scanf("%d",&num);
	printf("请输入要删除的数据");
	scanf("%s",data);	
	// 如果要删除的节点是头节点
        struct Node *temp = *head;
		struct Node *prev = *head;	
    if ((strcmp((*head)->data, data) == 0)&&(*head)->num == num) {
    	(*head)->next->prev=NULL;
        *head = (*head)->next;
        free(temp);
    }
	else{
		 // 寻找要删除节点的前一个节点
		while(prev->next!=NULL)
		{
			if((strcmp(prev->next->data, data) == 0)&&prev->next->num==num)
			{
				break;
			}
			prev=prev->next;
		}
		// 如果链表中没有要删除的节点
		if(prev->next==NULL)
		{
		printf("没有你要删除的节点");
		return;			
		}
		// 删除节点
		Node *temp=prev->next;
		temp->next->prev=prev;
		prev->next=temp->next;
		free(temp);
	}
	//更新后续节点数
	prev=prev->next;
	while(prev!=NULL)
	{
		prev->num=prev->num-1;
		prev=prev->next;		
	}
		printf("删除成功");	
	return;	        
}
//查找链表
void findData(struct Node *headEndPointer)
{
	struct Node *head=headEndPointer->prev;
	printf("请输入需要查找的数据");
	char data[20];
	scanf("%s",data);
	while(head!=NULL)
	{
		if(strcmp(data,head->data)==0)
		{
			printf("数据存在第%d节点",head->num);
			return ;
		}
		head=head->next;
	}
	printf("数据不存在");
	return ;
}

void gotoxy(int x, int y)
{
    COORD pos = { x,y }; // 设置显示的位置
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos); //两个参数分别是指定哪个窗体，具体位置
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
    gotoxy(0, line);  // 选中的高亮变色
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
        printf("\033[1;34;45m[F]\texit\n\033[0m");
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
        system("cls");   //系统清屏
        system("color 79");  //设置控制台的颜色
        Beep(2000, 250); //系统发声 
        menu(); //显示菜单
        line = 1;
        gotoxy(0, line); //移动光标到第一行的首位置
        printf("\033[1;34;45m[A]\tInput\n\033[0m"); //默认菜单第一行高亮变色

        for (; (c1 = _getch()) != '\r';)  // 读取按键值，遇到'\r'回车则结束
        { //注意敲击箭头键会出现两个字符数据:
          //LEFT(-32,75), UP(-32,72), DOWN(-32,80),Right(-32,77)
            if (c1 == -32)
            {
                c2 = _getch(); //获得按键的第二个键值，并根据方向选择菜单功能
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
                system("cls");   //系统清屏
                gotoxy(0, 0);    //光标回到初始位置
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

        time(&t); //获取时间戳
        lt = localtime(&t); // 转为时间结构
        sec = lt->tm_sec;
        // printf("time is: %d/%d/%d %d:%d:%d\n", lt->tm_year + 1900, lt->tm_mon, lt->tm_mday, lt->tm_hour,lt->tm_min, lt->tm_sec);

        do   // 延时一会
        {
            time(&t); //获取时间戳
            lt = localtime(&t); // 转为时间结构
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
