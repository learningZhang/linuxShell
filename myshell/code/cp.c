#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<assert.h>
#include<string.h>

//ls -l 
//ls -a

int main(int argc, char *args[])
{
	int rd = fopen(args[1], O_RDONLY);	
	int wd = fopen(args[2], O_WRONLY | O_CREAT, "0777");
	
	if (rd == -1 || wd == -1)
        {
		perror("open error");
	}

	char buff[128];
	while((read(rd, buff, 128)) != 0)
	{
		write(wd, buff, 128);
	}
	return 0;
}
