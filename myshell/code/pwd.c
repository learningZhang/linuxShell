#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
	char path[128] = {0};
        if(getcwd(path, 128) == -1)
	{
		perror("error");
	}
	printf("%s\n", path);
}
