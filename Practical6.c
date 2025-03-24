#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

typedef struct {
    char data[MAX];
    int top;
} CharStack;

void push(Stack* s, int value) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    s->data[++(s->top)] = value;
}

int pop(Stack* s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

void pushChar(CharStack* s, char op) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    s->data[++(s->top)] = op;
}

char popChar(CharStack* s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? a / b : (printf("Division by zero error\n"), exit(1), 0);
    }
    return 0;
}

int evaluateExpression(char* expr) {
    Stack values = {.top = -1};
    CharStack ops = {.top = -1};

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            i--;
            push(&values, num);
        } else if (expr[i] == '(') {
            pushChar(&ops, expr[i]);
        } else if (expr[i] == ')') {
            while (ops.top != -1 && ops.data[ops.top] != '(') {
                int b = pop(&values);
                int a = pop(&values);
                char op = popChar(&ops);
                push(&values, applyOperation(a, b, op));
            }
            popChar(&ops);
        } else {
            while (ops.top != -1 && precedence(ops.data[ops.top]) >= precedence(expr[i])) {
                int b = pop(&values);
                int a = pop(&values);
                char op = popChar(&ops);
                push(&values, applyOperation(a, b, op));
            }
            pushChar(&ops, expr[i]);
        }
    }

    while (ops.top != -1) {
        int b = pop(&values);
        int a = pop(&values);
        char op = popChar(&ops);
        push(&values, applyOperation(a, b, op));
    }

    return pop(&values);
}

int main() {
    // Hardcoded grammar productions
    int n = 3; 
    char grm[3][20] = {
        "E->E+T",
        "E->T",
        "T->T*F"
    };

    // Checking if it's operator grammar
    int isOperatorGrammar = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 3; grm[i][j] != '\0'; j++) {
            if (grm[i][j] == '+' || grm[i][j] == '-' || grm[i][j] == '*' || grm[i][j] == '/') {
                isOperatorGrammar = 1;
                break;
            }
        }
    }

    if (isOperatorGrammar)
        printf("Operator grammar detected.\n");
    else {
        printf("Not operator grammar.\n");
        return 0;
    }

    // Hardcoded arithmetic expression
    char expr[] = "3+5*2-8/4";
    printf("Evaluating Expression: %s\n", expr);

    int result = evaluateExpression(expr);
    printf("Result: %d\n", result);

    return 0;
}
