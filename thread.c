#include"types.h"
#include"user.h"
#include"thread.h"
#include"mmu.h"

int thread_create(void *(*start_routine)(void*), void *arg)
{
	printf(1,"Started thread\n");
	int size = PGSIZE;
	void* stack = malloc(size);

	if((uint)stack % PGSIZE)
	return -1;
	printf(1,"stack = %p\n",stack);
	printf(1,"startR = %p\n",start_routine);
	printf(1,"startR = %d\n",start_routine);

	//int* arg1 = stack + size - 4;
	//*arg1 = (int)arg;

	int clone_pid = clone(stack, size);
	
	if(clone_pid == 0)
	{
	  printf(1,"child\n");
	  printf(1,"second\n");
	  //start_routine(arg);
	  exit();
	}
	else
	printf(1,"parent\n");
	if(wait() < 0)
	return -1;

	printf(1,"Exit thread\n");
	return (int)arg;
}

void *start_routine(void * arg)
{
	//require_lock
	*((int*)arg) = 4;
	printf(1,"start routine\n");
	return arg;
	//release_lock
}
