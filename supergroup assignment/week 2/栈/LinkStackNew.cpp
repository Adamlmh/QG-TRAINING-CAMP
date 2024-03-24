#include "LinkStackNew.h"
Status initLStack(LinkStack* s) {//��ʼ��ջ
	s->top = (LinkStackPtr)malloc(LEN);
	if (s->top == NULL) {
		return wrong;
	}
	s->top->next = NULL;
	s->count = 0;
	return OK;
}
Status isEmptyLStack(LinkStack* s) {//�ж�ջ�Ƿ�Ϊ��
	if (s->top == NULL)
		return OK;
	if (s->top->next == NULL) {
		return OK;
	}
	return wrong;
}
Status getTopLStack(LinkStack* s, ElemType* e) {//��ջ��Ԫ��
	if (isEmptyLStack(s)||s->top==NULL) 
		return wrong;
	*e = s->top->data;
	return OK;
}
Status clearLStack(LinkStack* s) {
	if (isEmptyLStack(s)||s->top==NULL)//�ж�ջ��
		return wrong;
		s->top->next= NULL;
	return OK;
}//���ջ
Status destroyLStack(LinkStack* s) {//����ջ
	if (s->top == NULL)//�ж�ջ�Ƿ��ʼ��
		return wrong;
	LinkStackPtr p;
	while (s->top != NULL) {
		p = s->top;
		s->top = s->top->next;
		free(p);//�ͷſռ������ٽڵ�
	}
	s->count = 0;//ջ����Ϊ0
	return OK;
	}
Status LStackLength(LinkStack* s, int* length) {//���ջ����
	if (isEmptyLStack(s)||s->top==NULL)//�ж�ջ��
		return wrong;
	*length = s->count;
	return OK;
}
Status pushLStack(LinkStack* s, ElemType data) {//��ջ
	LinkStackPtr p = (LinkStackPtr)malloc(LEN);
	if (p == NULL||s->top==NULL)
		return wrong;
	p->data = data;
	p->next = s->top;
	s->top = p;
	(s->count)++;
	return OK;
}
Status popLStack(LinkStack* s, ElemType* data) {//��ջ
	if (isEmptyLStack(s)||s->top==NULL)
		return wrong;
	LinkStackPtr p;
	*data = s->top->data;
	p = s->top;//��ջ���ڵ㸳��p
	s->top = p->next;//��ջ���ڵ�ָ������һλ��ָ����һ�ڵ�
	free(p);
	s->count--;
	return OK;
}

void gotoxy(int x, int y)
{
    COORD pos = { x,y }; // ������ʾ��λ��
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ��׼����豸���
    SetConsoleCursorPosition(hOut, pos); //���������ֱ���ָ���ĸ����壬����λ��
}

void menu() {
    printf("====================\n");
    printf("[A]\t��ʼ��ջ\n");
    printf("[B]\t�ж�ջ�Ƿ�Ϊ��\n");
    printf("[C]\t�õ�ջ��Ԫ��\n");
    printf("[D]\t���ջ\n");
    printf("[E]\t����ջ\n");
    printf("[F]\t��ջ\n");
    printf("[G]\t��ջ\n");
    printf("[H]\t���ջ����\n");
    printf("[I]\t�˳�����\n");
    printf("====================\n");

}

void show(int line)
{
    gotoxy(0, 0);
    menu();
    gotoxy(0, line);  // ѡ�еĸ�����ɫ
    if (line == 1)
        printf("\033[1;34;45m[A]\t��ʼ��ջ\n\033[0m");
    if (line == 2)
        printf("\033[1;34;45m[B]\t�ж�ջ�Ƿ�Ϊ��\n\033[0m");
    if (line == 3)
        printf("\033[1;34;45m[C]\t�õ�ջ��Ԫ��\n\033[0m");
    if (line == 4)
        printf("\033[1;34;45m[D]\t���ջ\n\033[0m");
    if (line == 5)
        printf("\033[1;34;45m[E]\t����ջ\n\033[0m");
    if (line == 6)
        printf("\033[1;34;45m[F]\t��ջ\n\033[0m");
    if (line == 7)
        printf("\033[1;34;45m[G]\t��ջ\n\033[0m");
    if (line == 8)
        printf("\033[1;34;45m[H]\t���ջ����\n\033[0m");
    if (line == 9)
        printf("\033[1;34;45m[I]\t�˳�����\n\033[0m");
        
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
        system("cls");   //ϵͳ����
        system("color 79");  //���ÿ���̨����ɫ
        Beep(2000, 250); //ϵͳ���� 
        menu(); //��ʾ�˵�
        line = 1;
        gotoxy(0, line); //�ƶ���굽��һ�е���λ��
        printf("\033[1;34;45m[A]\t��ʼ��ջ\n\033[0m"); //Ĭ�ϲ˵���һ�и�����ɫ

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
                system("cls");   //ϵͳ����
                gotoxy(0, 0);    //���ص���ʼλ��
			if (initLStack(s))
				printf("��ʼ���ɹ�\n");
			else
				printf("��ʼ��ʧ��\n");
                line = 0;
                break;
            }
            else if (c1 == 'b' || c1 == 'B')
            {
                system("cls");
                gotoxy(0, 0);
			if (OK==isEmptyLStack(s))
				printf("ջΪ��\n");
			else if (2 == isEmptyLStack(s))
				printf("ջδ��ʼ��\n");
			else
				printf("ջ��Ϊ��\n");
                line = 0;
                break;
            }
            else if (c1 == 'c' || c1 == 'C')
            {
                system("cls");
                gotoxy(0, 0);
			if (getTopLStack(s, &e)) {
				printf("ջ��Ԫ��Ϊ%d\n", e);
			}
			else {
				printf("ջΪ�ջ���ջδ��ʼ��\n");
			}
                line = 0;
                break;
            }
            else if (c1 == 'd' || c1 == 'D')
            {
                system("cls");
                gotoxy(0, 0);
			if (clearLStack(s))
				printf("������\n");
			else
				printf("ջΪ�ջ���ջδ��ʼ��\n");
                line = 0;
                break;
            }
            else if (c1 == 'e' || c1 == 'E')
            {
                system("cls");
                gotoxy(0, 0);
			if (destroyLStack(s))
				printf("ջ���ٳɹ�\n");
			else
				printf("ջδ��ʼ��\n");
                line = 0;
                break;
            }
            else if (c1 == 'f' || c1 == 'F')
            {
                system("cls"); 
                gotoxy(0, 0);
			a:
			printf("������Ҫ����ջ������(����)��");
			scanf("%s", &b);
			for (int i = 0; i < strlen(b); i++) {
				if (!isdigit(b[i])) {
					printf("����Ƿ�������������\n");
					goto a;
				}
			}
			e = (int)atof(b);
			if (pushLStack(s, e))
				printf("��ջ�ɹ�\n");
			else
				printf("ջδ��ʼ��,��ջʧ��\n");
                line = 0;
                break;
            }
            else if (c1 == 'g' || c1 == 'G')
            {
                system("cls"); 
                gotoxy(0, 0);
			if (popLStack(s, &e)) {
				printf("��ջ�ɹ���ȡ��������Ϊ%d\n", e);
			}
			else
				printf("��ջʧ�ܣ�ջΪ�ջ���ջδ��ʼ��\n");
                line = 0;
                break;
            }
            else if (c1 == 'h' || c1 == 'H')
            {
                system("cls"); 
                gotoxy(0, 0);
			if (LStackLength(s, &length))
				printf("ջ����Ϊ%d\n", length);
			else
				printf("ջΪ�ջ���ջδ��ʼ��\n");
                line = 0;
                break;
            }			
            else if (c1 == 'i' || c1 == 'I')
            {
                system("cls"); 
                gotoxy(0, 0);
                exit(0);
			printf("�˳�����ɹ�\n");
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
				printf("��ʼ���ɹ�\n");
			else
				printf("��ʼ��ʧ��\n");
        }
        else if (line == 2)
        {
            system("cls");
            gotoxy(0, 0);
			if (OK==isEmptyLStack(s))
				printf("ջΪ��\n");
			else if (2 == isEmptyLStack(s))
				printf("ջδ��ʼ��\n");
			else
				printf("ջ��Ϊ��\n");
        }
        else if (line == 3)
        {
            system("cls");
            gotoxy(0, 0);
			if (getTopLStack(s, &e)) {
				printf("ջ��Ԫ��Ϊ%d\n", e);
			}
			else {
				printf("ջΪ�ջ���ջδ��ʼ��\n");
			}
        }
        else if (line == 4)
        {
            system("cls");
            gotoxy(0, 0);
			if (clearLStack(s))
				printf("������\n");
			else
				printf("ջΪ�ջ���ջδ��ʼ��\n");
        }
        else if (line == 5)
        {
            system("cls");
            gotoxy(0, 0);
			if (destroyLStack(s))
				printf("ջ���ٳɹ�\n");
			else
				printf("ջδ��ʼ��\n");
        }
        else if (line == 6)
        {
            system("cls");
            gotoxy(0, 0);
			printf("������Ҫ����ջ������(����)��");
			scanf("%s", &b);
			e = (int)atof(b);
			if (pushLStack(s, e))
				printf("��ջ�ɹ�\n");
			else
				printf("ջδ��ʼ��,��ջʧ��\n");
        }
        else if (line == 7)
        {
            system("cls");
            gotoxy(0, 0);
 			if (popLStack(s, &e)) {
				printf("��ջ�ɹ���ȡ��������Ϊ%d\n", e);
			}
			else
				printf("��ջʧ�ܣ�ջΪ�ջ���ջδ��ʼ��\n");
        }
                else if (line == 8)
        {
            system("cls");
            gotoxy(0, 0);
			if (LStackLength(s, &length))
				printf("ջ����Ϊ%d\n", length);
			else
				printf("ջΪ�ջ���ջδ��ʼ��\n");
        }
                else if (line == 9)
        {
            system("cls");
            gotoxy(0, 0);
                exit(0);
			printf("�˳�����ɹ�\n");
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
