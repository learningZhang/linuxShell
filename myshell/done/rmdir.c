#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>
#include<assert.h>


int main(int argc, char *argv[])
{
	if (rmdir(argv[1]) == -1)
	{
		perror("error");
	}
	return 0;
}
