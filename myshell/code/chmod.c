#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char *args[])
{

	int str[12] = {0} ;
	int x = 0;

	strcpy(str, args[1]);
	sscanf(str, "%d", &x);

	if (argc < 2)
	{
		perror("input too less\n");
	}
	if(chmod(args[1], x) == -1)
	{
		perror("error");
	}
        //que shao jiang x  zhuan hua wei mode_t lei xing
	

	return 0;
}

