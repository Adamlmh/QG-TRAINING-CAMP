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
//总体思路：将每个功能分成每个函数实现
//创建结构体
struct Node{
	char data[20]={0};
	int num;
	struct Node *next;
};

struct spiltList{
	struct Node *odd;
	struct Node *even;
};
//创建链表
struct Node *creatList(){
	int n = 0;
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
		}
		else{
			p2->next=p1;
		}
		p1->num=n;
		p2=p1;
		p1=(struct Node *)malloc(LEN);
		printf("请输入字符数组,回车结束\n");
		gets(p1->data);
	}
	p2->next=NULL;
	return head;
}

//打印链表
void printList(struct Node *head)
{
	struct Node *p;
	p=head;
	if(p==NULL)
	{
		printf("空链表");
	}
	while(p!=NULL)
	{
		printf("%s %d \n",p->data,p->num);
		p=p->next;
	}
}

//链表分拆
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
		printf("空链表无法拆分");	
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

//单链表奇偶调换
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
	//交叉链表
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

// 找到单链表的中间节点
struct Node* findMiddleNode(struct Node* head) {
    if (head == NULL || head->next == NULL)
        return head;

    struct Node *slow = head;
    struct Node *fast = head;

    // 快指针每次走两步，慢指针每次走一步
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
	slow->next=NULL;
    // 返回慢指针所在的节点，即为中间节点
    printList(slow);
    return slow;
}
// 判断单链表是否成环
bool hasCycle(struct Node *head) {
    if (head == NULL || head->next == NULL)
        return false;

    struct Node *slow = head;
    struct Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;        // 慢指针每次移动一步
        fast = fast->next->next;  // 快指针每次移动两步

        // 如果快指针追上了慢指针，则链表成环
        if (slow == fast)
            return true;
    }

    // 如果快指针到达链表末尾，则链表不成环
    return false;
}

//迭代反转链表
struct Node* reverseList(struct Node *head){
	struct Node *prev=NULL;
	struct Node *curr=head;
	struct Node *next=NULL;
	while(curr!=NULL){
		next=curr->next;   //保存节点
		curr->next=prev;	//反转指针	 
		prev=curr;			//向前迭代
		curr=next;
	}
	printList(prev);
	return prev;
}
//递归反转链表
struct Node* reverseListRecursive(struct Node *head){
	if(head==NULL||head->next==NULL) //最一般情况 递归截至点
	{
		return head;
	}
	struct Node *newHead =reverseListRecursive(head->next);
	//拆分成相同子问题
	//相同解决方法
	head->next->next=head;
	head->next=NULL;
	return newHead;
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
    gotoxy(0, line);  // 选中的高亮变色
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
                	printf("链表为循环链表\n");
				}
				else{
					printf("链表不是循环链表\n");
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
                	printf("链表为循环链表\n");
				}
				else{
					printf("链表不是循环链表\n");
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
