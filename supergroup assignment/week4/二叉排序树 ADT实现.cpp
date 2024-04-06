#include <stdio.h>
#include <stdlib.h>

// 二叉树结点定义
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 栈结点定义
typedef struct StackNode {
    struct TreeNode* treeNode;
    struct StackNode* next;
} StackNode;

// 创建一个新的树结点
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode != NULL) {
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

// 插入结点
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

// 查找结点
TreeNode* searchNode(TreeNode* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }
    if (value < root->data) {
        return searchNode(root->left, value);
    }
    return searchNode(root->right, value);
}

// 找到以node为根的子树的最小结点
TreeNode* findMin(TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// 删除结点
TreeNode* deleteNode(TreeNode* root, int value) {
    if (root == NULL) {
        return root;
    }
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        // 找到要删除的结点
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            printf("成功删除该节点\n");
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            printf("成功删除该节点\n");
            return temp;
        }
        // 有两个子结点的情况
        TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}


// 前序遍历
void preorderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// 中序遍历
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// 后序遍历
void postorderTraversal(TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}



// 前序遍历 (非递归)
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


// 中序遍历 (非递归)
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

// 后序遍历 (非递归)
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


// 层序遍历
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

// 销毁二叉树
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
        printf("\n二叉排序树操作\n");
        printf("1. 插入\n");
        printf("2. 删除\n");
        printf("3. 查找\n");
        printf("4. 前序遍历 (递归)\n");
        printf("5. 中序遍历 (递归)\n");
        printf("6. 后序遍历 (递归)\n");
        printf("7. 前序遍历 (非递归)\n");
        printf("8. 中序遍历 (非递归)\n");
        printf("9. 后序遍历 (非递归)\n");
        printf("10. 层序遍历\n");
        printf("11. 退出\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("请输入要插入的值: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("请输入要删除的值: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("请输入要查找的值: ");
                scanf("%d", &value);
                if (searchNode(root, value) != NULL) {
                    printf("树中找到了该值.\n");
                } else {
                    printf("树中未找到该值.\n");
                }
                break;
            case 4:
                printf("前序遍历 (递归): ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("中序遍历 (递归): ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("后序遍历 (递归): ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 7:
                printf("前序遍历 (非递归): ");
                iterativePreorder(root);
                printf("\n");
                break;
            case 8:
                printf("中序遍历 (非递归): ");
                iterativeInorder(root);
                printf("\n");
                break;
            case 9:
                printf("后序遍历 (非递归): ");
                iterativePostorder(root);
                printf("\n");
                break;
            case 10:
                printf("层序遍历: ");
                levelOrderTraversal(root);
                printf("\n");
                break;
            case 11:
                destroyTree(root);
                printf("退出程序.\n");
                exit(0);
            default:
                printf("无效选择\n");
        }
    }
    return 0;
}
