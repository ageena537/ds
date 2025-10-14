#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    return root;
}


void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, value,n;
       printf("Enter Total number of value to insert: ");
         scanf("%d", &n);
         for(int i=1;i<=n;i++)
         {
         printf("Value %i:" , i);
         scanf("%d",& value);
          root = insert(root, value);
        }
    
  printf("\nInorder Traversal: ");
  inorder(root);
 printf("\n");
             
        
printf("Preorder Traversal: ");
preorder(root);
printf("\n");
            
 printf("Postorder Traversal: ");
 postorder(root);
 printf("\n");
            
 
    return 0;
}
