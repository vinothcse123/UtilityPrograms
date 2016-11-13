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



void getString(char *p_outputString,int p_len=MAX_SINGLE_LINE_BUFFER_LENGTH)
{	
	
	if(!p_outputString)
		return;	
		
	memset(p_outputString,0,MAX_SINGLE_LINE_BUFFER_LENGTH*sizeof(char));	
	fgets(p_outputString, p_len, stdin);	
	return ;
}


int main()
{
	printf("%d",getInt());
}
