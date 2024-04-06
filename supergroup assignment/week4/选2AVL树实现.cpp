#include <stdio.h>
#include <stdlib.h>

// AVL树节点结构
typedef struct AVLNode {
    int data;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// 计算节点的高度
int height(AVLNode *node) {
    if (node == NULL) return 0;
    return node->height;
}

// 计算节点的平衡因子
int balanceFactor(AVLNode *node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

// 创建新节点
AVLNode *createNode(int data) {
    AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// 右旋操作
AVLNode *rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

// 左旋操作
AVLNode *leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

// 插入节点
AVLNode *insertNode(AVLNode *node, int data) {
    if (node == NULL) return createNode(data);

    if (data < node->data) {
        node->left = insertNode(node->left, data);
    } else if (data > node->data) {
        node->right = insertNode(node->right, data);
    } else {
        // 重复值
        return node;
    }

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    int balance = balanceFactor(node);

    // 左子树不平衡
    if (balance > 1 && data < node->left->data) {
        return rightRotate(node);
    }

    // 右子树不平衡
    if (balance < -1 && data > node->right->data) {
        return leftRotate(node);
    }

    // 左右子树均不平衡，LL情况
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // 左右子树均不平衡，RR情况
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// 中序遍历AVL树
void inorderTraversal(AVLNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// 销毁AVL树
void destroyAVLTree(AVLNode *root) {
    if (root != NULL) {
        destroyAVLTree(root->left);
        destroyAVLTree(root->right);
        free(root);
    }
}

int main() {
    AVLNode *root = NULL;
    int choice, value;
    while (1) {
        printf("\nAVL树操作\n");
        printf("1. 插入\n");
        printf("2. 中序遍历\n");
        printf("3. 退出\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("请输入要插入的值: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("中序遍历: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 3:
                destroyAVLTree(root);
                printf("退出程序.\n");
                exit(0);
            default:
                printf("无效选择\n");
        }
    }
    return 0;
}
