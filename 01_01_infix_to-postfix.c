#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack structure
typedef struct
{
    char arr[MAX];
    int top;
} Stack;

// Initialize stack
void initStack(Stack *s)
{
    s->top = -1;
}

// Check empty
int isEmpty(Stack *s)
{
    return s->top == -1;
}

// Check full
int isFull(Stack *s)
{
    return s->top == MAX - 1;
}

// Push to stack
void push(Stack *s, char c)
{
    if (!isFull(s))
    {
        s->arr[++s->top] = c;
    }
}

// Pop from stack
char pop(Stack *s)
{
    if (!isEmpty(s))
    {
        return s->arr[s->top--];
    }
    return '\0'; // return null char if empty
}

// Peek top of stack
char peek(Stack *s)
{
    if (!isEmpty(s))
    {
        return s->arr[s->top];
    }
    return '\0';
}

// Function to return precedence of operators
int precedence(char op)
{
    switch (op)
    {
    case '/':
    case '*':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

// Function to check if character is operator
int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Convert infix to postfix
void infixToPostfix(char infix[], char postfix[])
{
    Stack s;
    initStack(&s);
    int k = 0;

    for (int i = 0; i < strlen(infix); i++)
    {
        char c = infix[i];

        if (isdigit(c) || isalpha(c))
        {
            // Operand → directly add to postfix
            postfix[k++] = c;
        }
        else if (c == '(')
        {
            push(&s, c);
        }
        else if (c == ')')
        {
            // Pop until '(' is found
            while (!isEmpty(&s) && peek(&s) != '(')
            {
                postfix[k++] = pop(&s);
            }
            pop(&s); // remove '('
        }
        else if (isOperator(c))
        {
            // Pop operators with higher/equal precedence
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(c))
            {
                postfix[k++] = pop(&s);
            }
            push(&s, c);
        }
    }

    // Pop remaining operators
    while (!isEmpty(&s))
    {
        postfix[k++] = pop(&s);
    }

    postfix[k] = '\0'; // null terminate string
}

// Driver code
int main()
{
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
