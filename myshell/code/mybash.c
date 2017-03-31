#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <pwd.h>

#define MAX_ARGV_NUM 10
#define PATH "/home/xuanyu/Desktop/project/mybin/exec/"

void printinfo();

int main(int agrc, char *agrv[])
{
   char *myargv[MAX_ARGV_NUM] = {0};
   while(1)
   {
		memset(myargv, 0, MAX_ARGV_NUM);
        printinfo();
        char buff[128] = {0};
		fgets(buff, 128, stdin);
        buff[strlen(buff)-1] = 0;
        myargv[0] = strtok(buff, " ");
        int i = 0;
        char *s = NULL;
        while ((s = strtok(NULL, " ")) != NULL)
        {
			myargv[++i] = s;
        }

 		int tag = 0;
		if (myargv[0] == NULL)
		{
			continue;
		}
        if (!(strcmp("exit", myargv[0])))
        {
			exit(0);
        }

        if (!(strcmp(myargv[0], "cd")))
        {
			if (chdir(myargv[1]) == -1)
			{		
				printf("error\n");
				continue;
			}
		}

		char path_info[256] = {0};
		if (strncmp(buff, "/", 1)!=0 && strncmp(buff, "./", 2)!=0)
		{
			strcpy(path_info, PATH);
		}
        int pid = fork();
        assert(pid != -1);
		strcat(path_info, myargv[0]);
        if (pid == 0)
        {
		//execvp(myargv[0], myargv);
			execv(path_info, myargv);
			printf("bash: command not found\n");
			exit(0);
        }
        wait(NULL);     
   }
}

void printinfo()
{ 
    uid_t uid = getuid();
    char s = '#';
    if (uid != 0)
	{
		s = '$';
 	}

    struct passwd *p = getpwuid(uid);
	assert(p!=NULL);
     
	char hostname[128] = {0} ;
    gethostname(hostname, 128);
	
    char address[256] = {0};
	if (getcwd(address, 256) == NULL)
    {
        perror("error");
    }
    char *q1 = "/"; 
	char *q = strtok(address, "/");
    while(q != NULL)
	{
		q1 = q;
        q = strtok(NULL,"/");
	}
    printf("[%s@%s %s]%c",p->pw_name, hostname, q1, s);
}
