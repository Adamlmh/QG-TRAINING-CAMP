#include <stdio.h>
#include <stdlib.h>

// ��������㶨��
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ջ��㶨��
typedef struct StackNode {
    struct TreeNode* treeNode;
    struct StackNode* next;
} StackNode;

// ����һ���µ������
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode != NULL) {
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

// ������
TreeNode* insertNode(TreeNode* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }
    return root;
}

// ���ҽ��
TreeNode* searchNode(TreeNode* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }
    if (value < root->data) {
        return searchNode(root->left, value);
    }
    return searchNode(root->right, value);
}

// �ҵ���nodeΪ������������С���
TreeNode* findMin(TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// ɾ�����
TreeNode* deleteNode(TreeNode* root, int value) {
    if (root == NULL) {
        return root;
    }
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        // �ҵ�Ҫɾ���Ľ��
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            printf("�ɹ�ɾ���ýڵ�\n");
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            printf("�ɹ�ɾ���ýڵ�\n");
            return temp;
        }
        // �������ӽ������
        TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}


// ǰ�����
void preorderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// �������
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// �������
void postorderTraversal(TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}



// ǰ����� (�ǵݹ�)
void iterativePreorder(TreeNode* root) {
    if (root == NULL) return;

    StackNode* stack = NULL;

    while (1) {
        while (root != NULL) {
            printf("%d ", root->data);
            if (root->right != NULL) {
                StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
                temp->treeNode = root->right;
                temp->next = stack;
                stack = temp;
            }
            root = root->left;
        }
        if (stack == NULL) break;
        root = stack->treeNode;
        stack = stack->next;
    }
}


// ������� (�ǵݹ�)
void iterativeInorder(TreeNode* root) {
    if (root == NULL) return;

    StackNode* stack = NULL;

    while (1) {
        while (root != NULL) {
            StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
            temp->treeNode = root;
            temp->next = stack;
            stack = temp;
            root = root->left;
        }
        if (stack == NULL) break;
        root = stack->treeNode;
        printf("%d ", root->data);
        stack = stack->next;
        root = root->right;
    }
}

// ������� (�ǵݹ�)
void iterativePostorder(TreeNode* root) {
    if (root == NULL) return;

    StackNode* stack1 = NULL;
    StackNode* stack2 = NULL;

    stack1 = (StackNode*)malloc(sizeof(StackNode));
    stack1->treeNode = root;
    stack1->next = NULL;

    while (stack1 != NULL) {
        TreeNode* current = stack1->treeNode;
        stack1 = stack1->next;

        StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
        temp->treeNode = current;
        temp->next = stack2;
        stack2 = temp;

        if (current->left != NULL) {
            StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
            temp->treeNode = current->left;
            temp->next = stack1;
            stack1 = temp;
        }
        if (current->right != NULL) {
            StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
            temp->treeNode = current->right;
            temp->next = stack1;
            stack1 = temp;
        }
    }

    while (stack2 != NULL) {
        printf("%d ", stack2->treeNode->data);
        stack2 = stack2->next;
    }
}


// �������
void levelOrderTraversal(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        TreeNode* current = queue[front++];
        printf("%d ", current->data);
        if (current->left != NULL) queue[rear++] = current->left;
        if (current->right != NULL) queue[rear++] = current->right;
    }
}

// ���ٶ�����
void destroyTree(TreeNode* root) {
    if (root != NULL) {
        destroyTree(root->left);
        destroyTree(root->right);
        free(root);
    }
}

int main() {
    TreeNode* root = NULL;
    int choice, value;
    while (1) {
        printf("\n��������������\n");
        printf("1. ����\n");
        printf("2. ɾ��\n");
        printf("3. ����\n");
        printf("4. ǰ����� (�ݹ�)\n");
        printf("5. ������� (�ݹ�)\n");
        printf("6. ������� (�ݹ�)\n");
        printf("7. ǰ����� (�ǵݹ�)\n");
        printf("8. ������� (�ǵݹ�)\n");
        printf("9. ������� (�ǵݹ�)\n");
        printf("10. �������\n");
        printf("11. �˳�\n");
        printf("����������ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("������Ҫ�����ֵ: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("������Ҫɾ����ֵ: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("������Ҫ���ҵ�ֵ: ");
                scanf("%d", &value);
                if (searchNode(root, value) != NULL) {
                    printf("�����ҵ��˸�ֵ.\n");
                } else {
                    printf("����δ�ҵ���ֵ.\n");
                }
                break;
            case 4:
                printf("ǰ����� (�ݹ�): ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("������� (�ݹ�): ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("������� (�ݹ�): ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 7:
                printf("ǰ����� (�ǵݹ�): ");
                iterativePreorder(root);
                printf("\n");
                break;
            case 8:
                printf("������� (�ǵݹ�): ");
                iterativeInorder(root);
                printf("\n");
                break;
            case 9:
                printf("������� (�ǵݹ�): ");
                iterativePostorder(root);
                printf("\n");
                break;
            case 10:
                printf("�������: ");
                levelOrderTraversal(root);
                printf("\n");
                break;
            case 11:
                destroyTree(root);
                printf("�˳�����.\n");
                exit(0);
            default:
                printf("��Чѡ��\n");
        }
    }
    return 0;
}
