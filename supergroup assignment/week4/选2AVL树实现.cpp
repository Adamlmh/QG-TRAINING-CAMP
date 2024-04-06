#include <stdio.h>
#include <stdlib.h>

// AVL���ڵ�ṹ
typedef struct AVLNode {
    int data;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// ����ڵ�ĸ߶�
int height(AVLNode *node) {
    if (node == NULL) return 0;
    return node->height;
}

// ����ڵ��ƽ������
int balanceFactor(AVLNode *node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

// �����½ڵ�
AVLNode *createNode(int data) {
    AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// ��������
AVLNode *rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

// ��������
AVLNode *leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

// ����ڵ�
AVLNode *insertNode(AVLNode *node, int data) {
    if (node == NULL) return createNode(data);

    if (data < node->data) {
        node->left = insertNode(node->left, data);
    } else if (data > node->data) {
        node->right = insertNode(node->right, data);
    } else {
        // �ظ�ֵ
        return node;
    }

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    int balance = balanceFactor(node);

    // ��������ƽ��
    if (balance > 1 && data < node->left->data) {
        return rightRotate(node);
    }

    // ��������ƽ��
    if (balance < -1 && data > node->right->data) {
        return leftRotate(node);
    }

    // ������������ƽ�⣬LL���
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // ������������ƽ�⣬RR���
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// �������AVL��
void inorderTraversal(AVLNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// ����AVL��
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
        printf("\nAVL������\n");
        printf("1. ����\n");
        printf("2. �������\n");
        printf("3. �˳�\n");
        printf("����������ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("������Ҫ�����ֵ: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("�������: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 3:
                destroyAVLTree(root);
                printf("�˳�����.\n");
                exit(0);
            default:
                printf("��Чѡ��\n");
        }
    }
    return 0;
}
