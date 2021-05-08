#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *math = "1+2+3+4*5/2-6+7";
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
	char map[] = { [0]=0, ['+']=1, ['-']=1, ['*']=2, ['/']=2, ['#'] = 0,};
	return map[op1] - map[op2];
}

int get_num(void)
{
	int ch = *pc++;
	
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

int expr(int oper)
{
	int num=get_num();	
	int op; 
	int t;

loop:
	op = get_op();
	if(pri(oper,op) >= 0) {
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
	pc = math;

	int ans = expr('\0');

	printf("ans=%d\n", ans);

	char buf[120];

	
	sprintf(buf, "echo $((%s))", math);
	system(buf);

	return 0;
}
