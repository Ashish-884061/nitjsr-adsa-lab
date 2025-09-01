#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack for chars (operators)
typedef struct
{
    char arr[MAX];
    int top;
} CharStack;

// Stack for integers (evaluation)
typedef struct
{
    int arr[MAX];
    int top;
} IntStack;

// Initialize char stack
void initCharStack(CharStack *s) { s->top = -1; }
int isCharEmpty(CharStack *s) { return s->top == -1; }
void pushChar(CharStack *s, char c) { s->arr[++s->top] = c; }
char popChar(CharStack *s) { return s->arr[s->top--]; }
char peekChar(CharStack *s) { return s->arr[s->top]; }

// Initialize int stack
void initIntStack(IntStack *s) { s->top = -1; }
int isIntEmpty(IntStack *s) { return s->top == -1; }
void pushInt(IntStack *s, int val) { s->arr[++s->top] = val; }
int popInt(IntStack *s) { return s->arr[s->top--]; }

// Precedence of operators
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

int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Convert infix to postfix
void infixToPostfix(char infix[], char postfix[])
{
    CharStack s;
    initCharStack(&s);
    int k = 0;

    for (int i = 0; i < strlen(infix); i++)
    {
        char c = infix[i];

        if (isdigit(c))
        {
            // Handle multi-digit numbers
            while (i < strlen(infix) && isdigit(infix[i]))
            {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' '; // space as separator
            i--;                // adjust for loop increment
        }
        else if (c == '(')
        {
            pushChar(&s, c);
        }
        else if (c == ')')
        {
            while (!isCharEmpty(&s) && peekChar(&s) != '(')
            {
                postfix[k++] = popChar(&s);
                postfix[k++] = ' ';
            }
            popChar(&s); // remove '('
        }
        else if (isOperator(c))
        {
            while (!isCharEmpty(&s) && precedence(peekChar(&s)) >= precedence(c))
            {
                postfix[k++] = popChar(&s);
                postfix[k++] = ' ';
            }
            pushChar(&s, c);
        }
        // ignore spaces
    }

    while (!isCharEmpty(&s))
    {
        postfix[k++] = popChar(&s);
        postfix[k++] = ' ';
    }

    postfix[k] = '\0';
}

// Evaluate postfix expression
int evaluatePostfix(char postfix[])
{
    IntStack s;
    initIntStack(&s);

    for (int i = 0; i < strlen(postfix); i++)
    {
        char c = postfix[i];

        if (isdigit(c))
        {
            int num = 0;
            while (i < strlen(postfix) && isdigit(postfix[i]))
            {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            pushInt(&s, num);
        }
        else if (isOperator(c))
        {
            int b = popInt(&s);
            int a = popInt(&s);
            int res;

            switch (c)
            {
            case '+':
                res = a + b;
                break;
            case '-':
                res = a - b;
                break;
            case '*':
                res = a * b;
                break;
            case '/':
                res = a / b;
                break;
            }
            pushInt(&s, res);
        }
    }
    return popInt(&s);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s \"expression\"\n", argv[0]);
        return 1;
    }

    char infix[MAX], postfix[MAX];
    strcpy(infix, argv[1]);

    infixToPostfix(infix, postfix);
    int result = evaluatePostfix(postfix);

    printf("%d\n", result);

    return 0;
}
// gcc p2.c -o p2.exe
//.\p2.exe "(23-8)*3+28/4"
