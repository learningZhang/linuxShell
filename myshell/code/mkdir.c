#include<sys/types.h>
#include<sys/stat.h>

//int mkdir(const char*path, mod_t mode);
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		perror("paremeter too less\n");
	}
	mode_t mode = 0777;

	if (mkdir(argv[1], 0777) == -1)
	{	
		perror("error");
	}
	
	return 0;
}
