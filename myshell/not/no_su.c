#include<pwd.h>
#include<assert.h>
#include<sys/types.h>
#include<unistd.h>
#include<pwd.h>
#include<shadow.h>
#include<stdlib.h>

int main(int argc, char *argv[])      //su test
{
	struct passwd *p;
	if ((p = getpwnam(argv[1])) == NULL)
	{
		perror("username error");
		exit(0);
	}
	
	struct spwd *sp = getspnam(p->d_name);
	if (sp == NULL)
	{
		perror("error\n");
	}
	printf("%s \n", sp->sp_pwdp);
	char passwd[128] = {0};
	fgets(passwd, 128, stdin);
	passwd[strlen(passwd)-1] = 0;
	
	char lt[128] = {0};
	int i = 0;
	int num = 0;
	for( ; i<strlen(sp->sp_pwdp); i++)
	{
		if (*sp->sp_pwdp == '$')
		{
			if(num == 2)
			{
				break;
			}
			num++;
		}
	}
	char *cry = crypt(ls, passwd);
	if (strcmp(cry, ) != 0)
	{
		printf("fail\n");
		exit(0);
	}
	printf("succeed\n");
*/
	int pid = fork();
	assert(pid != -1);
	if (pid == 0)
	{
		if (setuid(p->pw_uidset) == -1)
		{
			perror("setuid is error");
		}
		int i = setenv(p->d_name, "home", 1);
		if (i == -1)
		{
			perror("sentenv is wrong\n");
		}
		execl(p>pw_shell, p->pw_shell, (char *)0);
	}
	wait(NULL);
}

