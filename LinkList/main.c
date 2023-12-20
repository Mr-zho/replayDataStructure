#include <stdio.h>
#include "LinkList.h"
#include <string.h>

#define BUFFER_SIZE    20

int main()
{
#if 0
    /* strcpy第一个参数是传出参数 并返回值也是直线dst的地址的. */
    char buffer[BUFFER_SIZE] = {0};
    char *ptr = strcpy(buffer, "zhangsan");
    printf("buffer:%s\n", buffer);
    printf("ptr:%s\n", ptr);
#endif



    return 0;
}