#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "STD_TYPES.h"


#define MAX_LENGTH 100


void push(s32 c);
void pop();
void show();
u8 empty();
s32 getTop();

s32 inp_array[MAX_LENGTH]={0};
s32 top = -1;


// Function to convert Infix expression to postfix
char* InfixToPostfix(const char* expression);

// Function to verify whether an operator has higher precedence over other
int HasHigherPrecedence(char operator1, char operator2);

// Function to verify whether a character is operator symbol or not.
int IsOperator(char C);

int IsOperand(char C);

int performOperation(int op1, int op2, char op);

// Function to evaluate Postfix expression and return output
void evaluate(char *postfix);


// Function to evaluate Postfix expression and return output
char* InfixToPostfix(const char* expression)
{
	char* postfix = malloc(MAX_LENGTH * sizeof(char));
	int len = strlen(expression);
	int x = 0;

	// Stack to store operators
	char stack[MAX_LENGTH];
	int top = -1;
	u8 inDigit = 1;

	for (int i = 0; i < len; i++) 
	{
// 		if (expression[i] == ' ')
// 		{
// 			postfix[x++] =' ';
// 		}
		 if (IsOperator(expression[i])) 
		{
			inDigit = 0;
			while (top != -1  && HasHigherPrecedence(stack[top], expression[i])) 
			{
				postfix[x++] = ' ';
				postfix[x++] = stack[top--];
			}
			stack[++top] = expression[i];
		}
		
		else if (IsOperand(expression[i])) 
		{
			inDigit = 1;
			postfix[x++] = expression[i];
		}
		if(inDigit==0)
		{
			postfix[x++] = ' ';
		}
	}

	while (top != -1) {
		postfix[x++] = ' ';
		postfix[x++] = stack[top--];
	}

	postfix[x] = '\0'; // Add null terminator to the postfix expression
	return postfix;
	//stack +
	//postfix 20 10 +
	//20+10
	
}


// Function to verify whether a character is alphanumeric letter or numeric digit.
int IsOperand(char C)
{
	if ((C >= '0' && C <= '9') || (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z')) {
		return 1;
	}
	return 0;
}

// Function to verify whether a character is operator symbol or not.
int IsOperator(char C)
{
	if (C == '+' || C == '-' || C == '*' || C == '/') {
		return 1;
	}
	return 0;
}

// Function to get weight of an operator. An operator with higher weight will have higher precedence.
int GetOperatorWeight(char op)
{
	int weight = -1;
	switch (op)
	{
		case '+':
		case '-':
		weight = 1;
		break;
		case '*':
		case '/':
		weight = 2;
		break;
	}
	return weight;
}

// Function to perform an operation and return output.
int HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	return op1Weight >= op2Weight ? true : false;
}



int performOperation(int op1, int op2, char op)
{
	volatile	int ans;
	switch (op) {
		case '+':
		ans = op2 + op1;
		break;
		case '-':
		ans = op2 - op1;
		break;
		case '*':
		ans = op2 * op1;
		break;
		case '/':
		ans = op2 / op1;
		break;
	}
	return ans;
}


// Function to evaluate Postfix expression and return output    20 10 +
void evaluate(char* expression)
{
	char* postfix = InfixToPostfix(expression);
	u8 buffer[15];
	u16 i, op1, op2, len, j, x,error=0;
	len = strlen(postfix);
	j = 0;

	for (i = 0; i < len; i++) 
	{

		if (postfix[i] >= '0' && postfix[i] <= '9') {
			buffer[j++] = postfix[i];
			//push(postfix[i]-'0');
		}
		else if (postfix[i] == ' ') {
			if (j > 0) {
				buffer[j] = '\0';
				x = atoi(buffer);
				push(x);
				j = 0;
			}
		}
		else if (IsOperator(postfix[i])) {
			j = 0;
			op1 = getTop();
			pop();
			op2 = getTop();
			pop();
			if(postfix[i]=='/' && op1==0)
			{
				error=1;
				break;
			}
			push(performOperation(op1, op2, postfix[i]));
		}
	}
	if (error)
	{
		LCD_u8SetPosXY(1,0);
		LCD_u8SendString("ERROR!");
	}
	else 
	{
		LCD_u8SetPosXY(1,0);
		LCD_voidWriteNumber(getTop());
	}
	free(postfix);
}

void push(s32 c)
{

	if (top == MAX_LENGTH - 1)
	{
		
	}
	else
	{
		top++;
		inp_array[top] = c;
	}
}

void pop()
{
	if (top == -1)
	{
		
	}
	else
	{
		top --;
	}
}

s32 getTop(){
	
	if (top == -1)
	{
		
	}
	else
	{
		return inp_array[top];
	}
}

u8 empty(){
	
	return (top==-1) ? 1 : 0;
};