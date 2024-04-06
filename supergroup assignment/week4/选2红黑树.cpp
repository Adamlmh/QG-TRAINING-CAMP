#include <stdio.h>
#include <stdlib.h>

// 定义红黑树节点的颜色
#define RED 0
#define BLACK 1

// 红黑树节点结构
typedef struct RBNode {
    int data;
    struct RBNode *parent;
    struct RBNode *left;
    struct RBNode *right;
    int color; // 0表示红色，1表示黑色
} RBNode;

// 创建新节点
RBNode *createNode(int data) {
    RBNode *newNode = (RBNode *)malloc(sizeof(RBNode));
    newNode->data = data;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = RED; // 新插入的节点默认为红色
    return newNode;
}

// 左旋操作
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

// 右旋操作
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

// 插入修正操作
void insertFixup(RBNode **root, RBNode *z) {
    // 循环直到z的父节点为黑色或者z成为根节点
    while (z != *root && z->parent->color == RED) {
        // 如果z的父节点是其祖父节点的左孩子
        if (z->parent == z->parent->parent->left) {
            // 获取z的叔叔节点
            RBNode *y = z->parent->parent->right;
            // Case 1: z的叔叔节点是红色的
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK; // 将z的父节点设为黑色
                y->color = BLACK; // 将z的叔叔节点设为黑色
                z->parent->parent->color = RED; // 将z的祖父节点设为红色
                z = z->parent->parent; // 将z指向其祖父节点，继续向上修正
            } else {
                // Case 2: z的叔叔节点是黑色的，且z是右孩子
                if (z == z->parent->right) {
                    z = z->parent; // 将z指向其父节点
                    leftRotate(root, z); // 对z进行左旋转，转换为Case 3
                }
                // Case 3: z的叔叔节点是黑色的，且z是左孩子
                z->parent->color = BLACK; // 将z的父节点设为黑色
                z->parent->parent->color = RED; // 将z的祖父节点设为红色
                rightRotate(root, z->parent->parent); // 对z的祖父节点进行右旋转
            }
        } else { // 如果z的父节点是其祖父节点的右孩子，与上述情况对称
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
    (*root)->color = BLACK; // 将根节点设为黑色，修正结束
}

// 插入节点
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

// 中序遍历红黑树
void inorderTraversal(RBNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// 销毁红黑树
void destroyRBTree(RBNode *root) {
    if (root != NULL) {
        destroyRBTree(root->left);
        destroyRBTree(root->right);
        free(root);
    }
}

// 输出红黑树的图形表示
void printRBTree(RBNode *root, int space) {
    if (root == NULL)
        return;

    space += 5;

    printRBTree(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    if (root->color == RED)
        printf("\033[1;31m"); // 红色
    else
        printf("\033[1;37m"); // 黑色
    printf("%d\n", root->data);
    printf("\033[0m");

    printRBTree(root->left, space);
}

int main() {
    RBNode *root = NULL;
    int choice, value;
    while (1) {
        printf("\n红黑树操作\n");
        printf("1. 插入\n");
        printf("2. 中序遍历\n");
        printf("3. 红黑树的图形表示：\n");
        printf("4. 退出\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("请输入要插入的值: ");
                scanf("%d", &value);
                insertNode(&root, value);
                break;
            case 2:
                printf("中序遍历: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("红黑树的图形表示：\n");
            	printRBTree(root,0);
            	printf("\n");
				break;
            case 4:
                destroyRBTree(root);
                printf("退出程序.\n");
                exit(0);
            default:
                printf("无效选择\n");
        }
    }
    return 0;
}
