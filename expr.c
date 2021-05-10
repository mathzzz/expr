#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int expr(int oper);
int get_op(void);
void unget(void);

char math[100]; 
char *pc;
int reg[26];

int pri(int op1, int op2)
{
	char map[] = { [0]=0, ['='] = 1, [','] = 1, [';']=2, ['+']=3, ['-']=3, ['*']=4, ['/']=4};
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
	else if(ch == '(' || ch == '{')
		return expr(ch);
	else if(ch >= 'a' && ch <= 'z') {
		int op = get_op();
		if(op == '=') { // left value
			return reg[ch - 'a'] = expr(op);
		}else { // right value
			unget();
			return reg[ch - 'a'];
		}
	}
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
	int num, op, t;
	num = get_num();	

loop:
	op = get_op();
	if(oper == '(' && op == ')')
		return num;
	if(oper == '{' && op == '}')
		return num;

	if(pri(oper,op)>= 0) {
		unget();
		return num;
	}

	//  oper < op
	switch(op) {
	case ',':
		num = expr(op);
		break;
	case '+':
		num = num + (t=expr(op));
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
	case '%':
		num  = num % expr(op);
		break;
	}

	goto loop;	
}

int main(int argc, char **argv)
{
	int i;
	strcpy(math, argv[1]);
	pc = math;
	int ans = expr('\0');
	for(i=0; i<5; i++){
		printf("%c=%d,", 'a'+i, reg[i]);
	}
	printf("|%s:ans=%d\n", math, ans);
	char buf[120];
	
	sprintf(buf, "echo $((%s))", math);

	//system(buf);

	return 0;
}
