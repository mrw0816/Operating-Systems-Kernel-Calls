#include <iostream>
#include <list>
#include <iterator>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <cstdlib>



#define READ 0
#define WRITE 1

#define TO_KERNEL 3
#define FROM_KERNEL 4



using namespace std;
int main (int argc, char** argv)
{
    int pid = getpid();
    int ppid = getppid();

	printf ("writing in pid %d\n", pid);
	const char *msg = "requesting system time";
	write (TO_KERNEL, msg, strlen(msg));


	printf ("trapping to %d in pid %d\n", ppid, pid);
    kill (ppid, SIGTRAP);


	char message[1024];
	int num_read = read(FROM_KERNEL, message, 1024);
	if(num_read>0){
		cout<<"In child process: "<< pid << endl;
		cout<< message << endl;
	}
	
	const char *msg2 = "requesting process list";
	cout<<"Writiting request for process list!"<<endl;
	write (TO_KERNEL, msg2, strlen(msg2));
	kill (ppid, SIGTRAP);

	char message2[1024];
	num_read = read(FROM_KERNEL, message2, 1024);
	if(num_read>0){
		cout<<"In child process: "<< pid << endl;
		cout<<message2<<endl;
	}
	

    
	printf("END OF CHILD");
    exit (0);
}
