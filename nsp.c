#include<stdio.h>
#include<libgen.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc,char*args[])
{ 
	char*cmd;
	cmd=basename(args[0]);
	char*cwd;
	cwd=dirname(args[0]);

	char path[8192];
	snprintf(path,8192-1,"%s/.%s/%s",cwd,cmd,args[1]?args[1]:""); 

	args[1]=path;
	execv(path,args+1);

	int err;
	struct stat meta;
	err=stat(path,&meta);
	if(err==0 && !S_ISDIR(meta.st_mode))
		execlp("cat","cat",path,NULL);
	else
		execlp("ls","ls","-1",path,NULL);

	snprintf(path,8192-1,"%s/.%s",cwd,cmd);
	execlp("ls","ls","-1",path,NULL);

	perror(cmd); 
	return 1;
}

