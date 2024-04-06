#include <stdio.h>
#include <stdlib.h>

// ���������ڵ����ɫ
#define RED 0
#define BLACK 1

// ������ڵ�ṹ
typedef struct RBNode {
    int data;
    struct RBNode *parent;
    struct RBNode *left;
    struct RBNode *right;
    int color; // 0��ʾ��ɫ��1��ʾ��ɫ
} RBNode;

// �����½ڵ�
RBNode *createNode(int data) {
    RBNode *newNode = (RBNode *)malloc(sizeof(RBNode));
    newNode->data = data;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = RED; // �²���Ľڵ�Ĭ��Ϊ��ɫ
    return newNode;
}

// ��������
void leftRotate(RBNode **root, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// ��������
void rightRotate(RBNode **root, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        *root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

// ������������
void insertFixup(RBNode **root, RBNode *z) {
    // ѭ��ֱ��z�ĸ��ڵ�Ϊ��ɫ����z��Ϊ���ڵ�
    while (z != *root && z->parent->color == RED) {
        // ���z�ĸ��ڵ������游�ڵ������
        if (z->parent == z->parent->parent->left) {
            // ��ȡz������ڵ�
            RBNode *y = z->parent->parent->right;
            // Case 1: z������ڵ��Ǻ�ɫ��
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK; // ��z�ĸ��ڵ���Ϊ��ɫ
                y->color = BLACK; // ��z������ڵ���Ϊ��ɫ
                z->parent->parent->color = RED; // ��z���游�ڵ���Ϊ��ɫ
                z = z->parent->parent; // ��zָ�����游�ڵ㣬������������
            } else {
                // Case 2: z������ڵ��Ǻ�ɫ�ģ���z���Һ���
                if (z == z->parent->right) {
                    z = z->parent; // ��zָ���丸�ڵ�
                    leftRotate(root, z); // ��z��������ת��ת��ΪCase 3
                }
                // Case 3: z������ڵ��Ǻ�ɫ�ģ���z������
                z->parent->color = BLACK; // ��z�ĸ��ڵ���Ϊ��ɫ
                z->parent->parent->color = RED; // ��z���游�ڵ���Ϊ��ɫ
                rightRotate(root, z->parent->parent); // ��z���游�ڵ��������ת
            }
        } else { // ���z�ĸ��ڵ������游�ڵ���Һ��ӣ�����������Գ�
            RBNode *y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK; // �����ڵ���Ϊ��ɫ����������
}

// ����ڵ�
void insertNode(RBNode **root, int data) {
    RBNode *z = createNode(data);
    RBNode *y = NULL;
    RBNode *x = *root;
    while (x != NULL) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == NULL) {
        *root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }
    insertFixup(root, z);
}

// ������������
void inorderTraversal(RBNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// ���ٺ����
void destroyRBTree(RBNode *root) {
    if (root != NULL) {
        destroyRBTree(root->left);
        destroyRBTree(root->right);
        free(root);
    }
}

// ����������ͼ�α�ʾ
void printRBTree(RBNode *root, int space) {
    if (root == NULL)
        return;

    space += 5;

    printRBTree(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    if (root->color == RED)
        printf("\033[1;31m"); // ��ɫ
    else
        printf("\033[1;37m"); // ��ɫ
    printf("%d\n", root->data);
    printf("\033[0m");

    printRBTree(root->left, space);
}

int main() {
    RBNode *root = NULL;
    int choice, value;
    while (1) {
        printf("\n���������\n");
        printf("1. ����\n");
        printf("2. �������\n");
        printf("3. �������ͼ�α�ʾ��\n");
        printf("4. �˳�\n");
        printf("����������ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("������Ҫ�����ֵ: ");
                scanf("%d", &value);
                insertNode(&root, value);
                break;
            case 2:
                printf("�������: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("�������ͼ�α�ʾ��\n");
            	printRBTree(root,0);
            	printf("\n");
				break;
            case 4:
                destroyRBTree(root);
                printf("�˳�����.\n");
                exit(0);
            default:
                printf("��Чѡ��\n");
        }
    }
    return 0;
}
