#include"types.h"
#include"user.h"
#include"thread.h"
#include"mmu.h"

int thread_create(void *(*start_routine)(void*), void *arg)
{
	printf(1,"Started thread\n");
	void* stack = malloc(PGSIZE);

	if((uint)stack % PGSIZE)
	return -1;

	int* arg1 = stack + PGSIZE - sizeof(int*);
	*arg1 = (int)arg;

	int clone_pid = clone(stack, PGSIZE);
	
	if(clone_pid == 0)
	{
	  printf(1,"child\n");
	  //start_routine(arg);
	}
	else
	printf(1,"parent\n");

	printf(1,"Exit thread\n");
	return (int)arg;
}

void *start_routine(void * arg)
{
	//require_lock
	*((int*)arg) = 4;
	return arg;
	//release_lock
}
