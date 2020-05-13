#include "types.h"
#include "stat.h"
#include "user.h"
//#include <stdio.h>

int main(int argc, char *argv[])
{

    settickets(30,"prog1");
    int i, k;
    const int loop = 43000;

    for (i=0;i<loop;i++)
    {
	asm("nop");
	for (k=0;k<loop;k++)
	{
	    asm("nop");
	}
    }	   
    getticks();
    exit();
}
