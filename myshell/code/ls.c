#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>
#include<shadow.h>
#define LS 1
#define LL 2
#define LA 3

void print(char *str, int tag);            //如果用户执行的ll该怎么进行，将ls的可执行文档复制一份改名为ll?                                    

int main(int argc, char*argv[])
{	
	char buf[256] = {0};
	getcwd(buf, 256);
	if (argc == 1)
	{
//		if (strcmp(argv[0], "ls"))                  //ls
//		{
	//		printf("ls\n");
			print(buf, LS);
//		}
//		else if (strcmp(argv[0], "ll"))          // ll
//		{
//			print(buf, LL);
//		}
	}
	else
	{
		if (!(strncmp(argv[1], "-l", 2)))            // ls -l
		{
			if (argc > 2)
			{
			//	printf("ls -l out\n");
				print(argv[2], LL); 
			}
			else
			{
			//	printf("ls -l\n");
				print(buf, LL);//ls -l 
			}
		}
		else if (!(strncmp(argv[1], "-a", 2)))
		{
			if (argc > 2)
			{
			//	printf("ls -a out\n"); // ls -a out
				print(argv[2], LA); 
			}
			else
			{
			//	printf("ls -a\n");
				print(buf, LA); //ls -a 
			}
		}
		else
		{
		//	printf("ls out  ");
			print(argv[1], LS); //ls out
		}
	}
}

void print(char *str, int tag)
{
	DIR *dir = opendir(str);
	if (dir == NULL)
	{
		printf("cannot open %s: no such file or directory\n", str);
		exit(0);
	}


	struct dirent *pre = NULL;
	struct stat st;

	if (tag == LS || tag == LA) //ls            ls -a
	{
		while((pre = readdir(dir)) != NULL)
		{
		 	lstat(pre->d_name, &st);
			if (tag == LS)
			{
				if (!(strncmp(pre->d_name, ".", 1)))
				{
					continue;
				}
			}
			if (S_ISDIR(st.st_mode))
			{
				printf("\033[34m%s\033[30m   ", pre->d_name);
			}
			else if (st.st_mode & S_IXOTH || st.st_mode & S_IXGRP || st.st_mode &S_IXUSR)
			{
				printf("\033[32m%s\033[30m   ",pre->d_name);
			}
		}
	printf("\n");
	}
	else// ll
	{
		while ((pre = readdir(dir)) != NULL)
		{
			lstat(pre->d_name, &st);
			
			if (!(strncmp(pre->d_name, ".", 1)))
			{
				continue;
			}
			if (S_ISDIR(st.st_mode))
			{
				char user[127] = {0};
				//long st_uid = st.st_uid;//get user
				//long st_gid = st.st.gid;//get owns
                                printf("\033[32m%ld %ld %ld  %s \033[30m\n", st.st_nlink, st.st_uid, st.st_gid, pre->d_name);
			}		
			else if (st.st_mode & S_IXOTH || st.st_mode & S_IXGRP || st.st_mode &S_IXUSR)
			{
			
                                printf("\033[34m%ld %ld %ld  %s\033[30m\n", st.st_nlink, st.st_uid, st.st_gid, pre->d_name);
			}
		} 
	}
	closedir(dir);
}
