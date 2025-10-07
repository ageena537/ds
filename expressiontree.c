#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 50

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

// Stack for Node pointers (used in tree construction)
typedef struct NodeStack {
    Node* data[MAX];
    int top;
} NodeStack;

void initNodeStack(NodeStack* s) {
    s->top = -1;
}

void pushNode(NodeStack* s, Node* node) {
    s->data[++(s->top)] = node;
}

Node* popNode(NodeStack* s) {
    return s->data[(s->top)--];
}

// Stack for operators (char stack)
typedef struct CharStack {
    char data[MAX];
    int top;
} CharStack;

void initCharStack(CharStack* s) {
    s->top = -1;
}

void pushChar(CharStack* s, char c) {
    s->data[++(s->top)] = c;
}

char popChar(CharStack* s) {
    return s->data[(s->top)--];
}

char peekChar(CharStack* s) {
    if (s->top == -1) return '\0';
    return s->data[s->top];
}

int isEmptyCharStack(CharStack* s) {
    return s->top == -1;
}

int isOperand(char c) {
    return isalpha(c);
}

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void infixToPostfix(char* infix, char* postfix) {
    CharStack s;
    initCharStack(&s);
    int k = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (isOperand(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            pushChar(&s, c);
        } else if (c == ')') {
            while (!isEmptyCharStack(&s) && peekChar(&s) != '(') {
                postfix[k++] = popChar(&s);
            }
            popChar(&s); // pop '('
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!isEmptyCharStack(&s) && precedence(peekChar(&s)) >= precedence(c)) {
                postfix[k++] = popChar(&s);
            }
            pushChar(&s, c);
        }
    }
    while (!isEmptyCharStack(&s)) {
        postfix[k++] = popChar(&s);
    }
    postfix[k] = '\0';
}

Node* constructExpressionTree(char* postfix) {
    NodeStack s;
    initNodeStack(&s);
    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        if (isOperand(c)) {
            pushNode(&s, createNode(c));
        } else {
            Node* node = createNode(c);
            node->right = popNode(&s);
            node->left = popNode(&s);
            pushNode(&s, node);
        }
    }
    return popNode(&s);
}

void preorder(Node* root) {
    if (root == NULL) return;
    printf("%c ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%c ", root->data);
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    Node* root = constructExpressionTree(postfix);

    printf("Prefix Expression: ");
    preorder(root);
    printf("\n");

    printf("Postfix Expression (from tree): ");
    postorder(root);
    printf("\n");

    freeTree(root);

    return 0;
}
         
        
