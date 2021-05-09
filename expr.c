#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int expr(int oper);
char math[100]; //"-1+2*3/-2--3-1+2+3+4*5/-2-6+7-8*2/-4-5-7+++++-9";
char *pc;
 
int get_pri(int op)
{
	switch (op) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	}
	exit(-1);
}

int pri(int op1, int op2)
{
	char map[] = { [0]=0, ['(']=1, [')']=1, ['+']=2, ['-']=2, ['*']=3, ['/']=3};
	int pri1 = map[op1];
	int pri2 = map[op2];
	return pri1 - pri2;
}

int get_num(void)
{
	int ch = *pc++;
	if(ch == '+') 
		return expr(ch);
	else if(ch == '-')
		return -expr(ch);
	else if(ch == '(' )
		return expr(ch);
	return ch - '0';
}

int get_op(void)
{
	int ch = *pc++;
	return ch;
}

void unget(void)
{
	pc--;
}

int peek(void)
{
	return *pc;
}

int expr(int oper)
{
	int num;
	int op; 

	num = get_num();	

loop:
	op = get_op();
	if(pri(oper,op)>= 0) {
		if(!(oper == '(' && op == ')'))
			unget();
		return num;
	}

	//  oper < op
	switch(op) {
	case '+':
			num = num + expr(op);
		break;
	case '-':
			num = num - expr(op);
		break;
	case '*':
		num = num * expr(op);
		break;
	case '/':
		num = num / expr(op);
		break;
	}

	goto loop;	
}

int main(int argc, char **argv)
{
	strcpy(math, argv[1]);
	pc = math;

	int ans = expr('\0');

	printf("ans=%d\n", ans);

	char buf[120];
	
	sprintf(buf, "echo $((%s))", math);

	system(buf);

	return 0;
}
