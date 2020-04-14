#include "types.h"
#include "stat.h"
#include "user.h"
//#include <stdio.h>

int main(int argc, char *argv[])
{

    if(argc != 2){
      printf(2, "usage: info param(1,2,3)\n");
      exit();
    }

    int param = atoi(argv[1]);
    int num = info(param);
    printf(2,"Info returned: %d\n", num);
    exit();
}
