#include<stdio.h>
#define MAX_STRING_BUF_SIZE 1000

int getInt()
{
	char l_buffer[256];
	int i=0;
	if (fgets(l_buffer, sizeof(l_buffer), stdin)) {
		if (1 == sscanf(l_buffer, "%d", &i)) {
			return i;
		}
	}	
	return i;
}


void getString(char *p_outputString)
{
	if(!p_outputString)
		return;	
	
	fgets(p_outputString, MAX_STRING_BUF_SIZE, stdin);	
	return ;
}


int main()
{
	printf("%d",getInt());
}
