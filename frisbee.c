#include"types.h"
#include"user.h"
#include"stat.h"
//#include"thread.h"

#include"mmu.h"

struct lock_t 
{
  int ticket;       // Is the lock held?
  int turn;       // Is the lock held?
};

static inline int FAA(int* addr, int newval)
{
  __asm__ volatile
  ("lock; xaddl %0, %1"
     : "+r" (newval), "+m" (*addr)
     :
     : "memory"
  );
  return newval;
}

static struct {
  struct lock_t lock;
  int threads[10];
  int turns[10];
} tTable;  

void
lock_init(struct lock_t *lock)
{
  lock->turn = 0;
  lock->ticket = 0;
}

void lock_aquire(struct lock_t* lock)
{
  while(FAA(&lock->turn,1) != 0);
  __sync_synchronize();
}

void lock_release(struct lock_t* lock)
{
  __sync_synchronize();
  asm volatile("movl $0, %0" : "+m" (lock->turn) : );
}

int thread_create(void *(*start_routine)(void*), void *arg)
{
	int size = PGSIZE;
	void* stack = malloc(size);

	if((uint)stack % PGSIZE)
	{
	  stack = stack + (PGSIZE - ((uint)stack % PGSIZE));
	}

	int*ret = stack + size - 8;
	*ret = 0xffffffff;

	int* arg1 = stack + size - 4;
	*arg1 = (int)arg;

	int location_func = (int)(*start_routine);

	int clone_pid = clone(stack, location_func);
	
	return clone_pid;
}

int threadExecuting;
int thread;
int numThreads;
int pass;

void *start_routine(void * arg)
{
	int t_id;

	lock_aquire(&tTable.lock);
	t_id = thread;
	thread++;	
	lock_release(&tTable.lock);

	while (*((int*)arg) > 0)
	{
	  lock_aquire(&tTable.lock);
	  if (*((int*)arg) <= 0)
	  {
	    lock_release(&tTable.lock);
	    break;
	  }

	  if(t_id != threadExecuting)
	  {
	    lock_release(&tTable.lock);
	    continue;
	  }

	  threadExecuting = (t_id+1)%numThreads;
	  printf(1,"Pass number no:%d Thread %d is passing the token to thread %d\n",pass,t_id, threadExecuting);

	  *((int*)arg) = *((int*)arg) - 1;
	  pass++;

	  if (*((int*)arg) <= 0)
	  {
	    lock_release(&tTable.lock);
	    break;
	  }

	  lock_release(&tTable.lock);
	}
	exit();
}

int main(int argc, char* argv[])
{
	
	lock_init(&tTable.lock);
	thread = 0;
	numThreads = atoi(argv[1]);
	threadExecuting = 0;
	pass = 1;

	int val = atoi(argv[2]);
	int* arg = &val;
	for(int i = 0; i < atoi(argv[1]); i++)
	tTable.threads[i] = thread_create(start_routine,(void*)arg);

	void* fstack = 0;
	for(int i = 0; i < atoi(argv[1]); i++)
	{
	  if(join(fstack) < 0)
	  return -1;;
	}
	printf(1,"\nSimulation of Frisbee game has finished, %d rounds were played in total!\n",atoi(argv[2]));

	exit();
}
