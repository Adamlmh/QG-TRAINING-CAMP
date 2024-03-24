#include "LinkStackNew.h"
Status initLStack(LinkStack* s) {//初始化栈
	s->top = (LinkStackPtr)malloc(LEN);
	if (s->top == NULL) {
		return wrong;
	}
	s->top->next = NULL;
	s->count = 0;
	return OK;
}
Status isEmptyLStack(LinkStack* s) {//判断栈是否为空
	if (s->top == NULL)
		return OK;
	if (s->top->next == NULL) {
		return OK;
	}
	return wrong;
}
Status getTopLStack(LinkStack* s, ElemType* e) {//得栈顶元素
	if (isEmptyLStack(s)||s->top==NULL) 
		return wrong;
	*e = s->top->data;
	return OK;
}
Status clearLStack(LinkStack* s) {
	if (isEmptyLStack(s)||s->top==NULL)//判断栈空
		return wrong;
		s->top->next= NULL;
	return OK;
}//清空栈
Status destroyLStack(LinkStack* s) {//销毁栈
	if (s->top == NULL)//判断栈是否初始化
		return wrong;
	LinkStackPtr p;
	while (s->top != NULL) {
		p = s->top;
		s->top = s->top->next;
		free(p);//释放空间以销毁节点
	}
	s->count = 0;//栈长度为0
	return OK;
	}
Status LStackLength(LinkStack* s, int* length) {//检测栈长度
	if (isEmptyLStack(s)||s->top==NULL)//判断栈空
		return wrong;
	*length = s->count;
	return OK;
}
Status pushLStack(LinkStack* s, ElemType data) {//入栈
	LinkStackPtr p = (LinkStackPtr)malloc(LEN);
	if (p == NULL||s->top==NULL)
		return wrong;
	p->data = data;
	p->next = s->top;
	s->top = p;
	(s->count)++;
	return OK;
}
Status popLStack(LinkStack* s, ElemType* data) {//出栈
	if (isEmptyLStack(s)||s->top==NULL)
		return wrong;
	LinkStackPtr p;
	*data = s->top->data;
	p = s->top;//把栈顶节点赋给p
	s->top = p->next;//将栈顶节点指针下移一位，指向下一节点
	free(p);
	s->count--;
	return OK;
}

void gotoxy(int x, int y)
{
    COORD pos = { x,y }; // 设置显示的位置
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos); //两个参数分别是指定哪个窗体，具体位置
}

void menu() {
    printf("====================\n");
    printf("[A]\t初始化栈\n");
    printf("[B]\t判断栈是否为空\n");
    printf("[C]\t得到栈顶元素\n");
    printf("[D]\t清空栈\n");
    printf("[E]\t销毁栈\n");
    printf("[F]\t入栈\n");
    printf("[G]\t岀栈\n");
    printf("[H]\t检测栈长度\n");
    printf("[I]\t退出程序\n");
    printf("====================\n");

}

void show(int line)
{
    gotoxy(0, 0);
    menu();
    gotoxy(0, line);  // 选中的高亮变色
    if (line == 1)
        printf("\033[1;34;45m[A]\t初始化栈\n\033[0m");
    if (line == 2)
        printf("\033[1;34;45m[B]\t判断栈是否为空\n\033[0m");
    if (line == 3)
        printf("\033[1;34;45m[C]\t得到栈顶元素\n\033[0m");
    if (line == 4)
        printf("\033[1;34;45m[D]\t清空栈\n\033[0m");
    if (line == 5)
        printf("\033[1;34;45m[E]\t销毁栈\n\033[0m");
    if (line == 6)
        printf("\033[1;34;45m[F]\t入栈\n\033[0m");
    if (line == 7)
        printf("\033[1;34;45m[G]\t岀栈\n\033[0m");
    if (line == 8)
        printf("\033[1;34;45m[H]\t检测栈长度\n\033[0m");
    if (line == 9)
        printf("\033[1;34;45m[I]\t退出程序\n\033[0m");
        
}

void menu_control()
{
    char c1, c2, ch;
    int line, sec;
    long long j;
    time_t t;
	int e=0,length=0;
	char a[1],b[] = "";
	LinkStack* s=(LinkStack*)malloc(sizeof(LinkStack));
	initLStack(s);

    while(1)
    { 
    	    struct tm* lt;
        system("cls");   //系统清屏
        system("color 79");  //设置控制台的颜色
        Beep(2000, 250); //系统发声 
        menu(); //显示菜单
        line = 1;
        gotoxy(0, line); //移动光标到第一行的首位置
        printf("\033[1;34;45m[A]\t初始化栈\n\033[0m"); //默认菜单第一行高亮变色

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
                else if (ch == downkey && line != 9)
                {
                    line++;
                    show(line);
                    continue;
                }
                else if (ch == upkey && line == 1)
                {
                    line = 9;
                    show(line);
                    continue;
                }
                else if (ch == downkey && line == 9)
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
			if (initLStack(s))
				printf("初始化成功\n");
			else
				printf("初始化失败\n");
                line = 0;
                break;
            }
            else if (c1 == 'b' || c1 == 'B')
            {
                system("cls");
                gotoxy(0, 0);
			if (OK==isEmptyLStack(s))
				printf("栈为空\n");
			else if (2 == isEmptyLStack(s))
				printf("栈未初始化\n");
			else
				printf("栈不为空\n");
                line = 0;
                break;
            }
            else if (c1 == 'c' || c1 == 'C')
            {
                system("cls");
                gotoxy(0, 0);
			if (getTopLStack(s, &e)) {
				printf("栈顶元素为%d\n", e);
			}
			else {
				printf("栈为空或者栈未初始化\n");
			}
                line = 0;
                break;
            }
            else if (c1 == 'd' || c1 == 'D')
            {
                system("cls");
                gotoxy(0, 0);
			if (clearLStack(s))
				printf("清空完毕\n");
			else
				printf("栈为空或者栈未初始化\n");
                line = 0;
                break;
            }
            else if (c1 == 'e' || c1 == 'E')
            {
                system("cls");
                gotoxy(0, 0);
			if (destroyLStack(s))
				printf("栈销毁成功\n");
			else
				printf("栈未初始化\n");
                line = 0;
                break;
            }
            else if (c1 == 'f' || c1 == 'F')
            {
                system("cls"); 
                gotoxy(0, 0);
			a:
			printf("请输入要存入栈的数字(整数)：");
			scanf("%s", &b);
			for (int i = 0; i < strlen(b); i++) {
				if (!isdigit(b[i])) {
					printf("输入非法，请重新输入\n");
					goto a;
				}
			}
			e = (int)atof(b);
			if (pushLStack(s, e))
				printf("入栈成功\n");
			else
				printf("栈未初始化,入栈失败\n");
                line = 0;
                break;
            }
            else if (c1 == 'g' || c1 == 'G')
            {
                system("cls"); 
                gotoxy(0, 0);
			if (popLStack(s, &e)) {
				printf("岀栈成功，取出的数据为%d\n", e);
			}
			else
				printf("岀栈失败，栈为空或者栈未初始化\n");
                line = 0;
                break;
            }
            else if (c1 == 'h' || c1 == 'H')
            {
                system("cls"); 
                gotoxy(0, 0);
			if (LStackLength(s, &length))
				printf("栈长度为%d\n", length);
			else
				printf("栈为空或者栈未初始化\n");
                line = 0;
                break;
            }			
            else if (c1 == 'i' || c1 == 'I')
            {
                system("cls"); 
                gotoxy(0, 0);
                exit(0);
			printf("退出程序成功\n");
			return ;
                line = 0;
                break;
            }						                                           
        }

        if (line == 1)
        {
            system("cls");
            gotoxy(0, 0);
			if (initLStack(s))
				printf("初始化成功\n");
			else
				printf("初始化失败\n");
        }
        else if (line == 2)
        {
            system("cls");
            gotoxy(0, 0);
			if (OK==isEmptyLStack(s))
				printf("栈为空\n");
			else if (2 == isEmptyLStack(s))
				printf("栈未初始化\n");
			else
				printf("栈不为空\n");
        }
        else if (line == 3)
        {
            system("cls");
            gotoxy(0, 0);
			if (getTopLStack(s, &e)) {
				printf("栈顶元素为%d\n", e);
			}
			else {
				printf("栈为空或者栈未初始化\n");
			}
        }
        else if (line == 4)
        {
            system("cls");
            gotoxy(0, 0);
			if (clearLStack(s))
				printf("清空完毕\n");
			else
				printf("栈为空或者栈未初始化\n");
        }
        else if (line == 5)
        {
            system("cls");
            gotoxy(0, 0);
			if (destroyLStack(s))
				printf("栈销毁成功\n");
			else
				printf("栈未初始化\n");
        }
        else if (line == 6)
        {
            system("cls");
            gotoxy(0, 0);
			printf("请输入要存入栈的数字(整数)：");
			scanf("%s", &b);
			e = (int)atof(b);
			if (pushLStack(s, e))
				printf("入栈成功\n");
			else
				printf("栈未初始化,入栈失败\n");
        }
        else if (line == 7)
        {
            system("cls");
            gotoxy(0, 0);
 			if (popLStack(s, &e)) {
				printf("岀栈成功，取出的数据为%d\n", e);
			}
			else
				printf("岀栈失败，栈为空或者栈未初始化\n");
        }
                else if (line == 8)
        {
            system("cls");
            gotoxy(0, 0);
			if (LStackLength(s, &length))
				printf("栈长度为%d\n", length);
			else
				printf("栈为空或者栈未初始化\n");
        }
                else if (line == 9)
        {
            system("cls");
            gotoxy(0, 0);
                exit(0);
			printf("退出程序成功\n");
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
