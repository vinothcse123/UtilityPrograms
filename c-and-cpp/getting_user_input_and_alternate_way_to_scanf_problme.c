#include<stdio.h>

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


int main()
{
	printf("%d",getInt());
}

