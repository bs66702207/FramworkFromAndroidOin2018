#include<stdio.h>
union UN {
	int a;
	char c;
}un;
int main()
{
	union UN un;
	un.a=1;
	if(un.c=1)
		printf("xiaoduan\n");
	else
		printf("daduan\n");
	return 0;	
}
