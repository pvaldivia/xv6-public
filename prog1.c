#include"types.h"
#include"user.h"
#include"stat.h"
#include"thread.h"

int main(int argc, char* argv[])
{
	int val = 1;
	int* arg = &val;
	thread_create(start_routine,(void*)arg);

	//printf(1,"arg has changed and threads share memory\n");
	//for(int i = 0; i < atoi(argv[1]);i++)
	//{
	//	thread_create(start_routine,arg);
	//}
	exit();
}
