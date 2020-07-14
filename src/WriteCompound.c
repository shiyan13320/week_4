#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STR 20

/* ��ӡ��ǰʱ������־�� */
void local_time(FILE *fptm)
{
    time_t t;
    struct tm *lt;
    time(&t);
    lt = localtime(&t);
    fprintf(fptm, "%d-%d-%d %d:%d  ", lt->tm_year+1900, 1+lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min);
    printf("%d-%d-%d %d:%d  \n", lt->tm_year+1900, 1+lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min);
}

/* ������Ľ����ӡ����־�ļ��� */
void Write_Result(int len, char strExp[])
{
    FILE *fp;

    if ((fp = fopen("F:\\CodeBlocks\\CalcCompound\\journal.txt" ,"a")) == NULL)
    {
         printf("Unable to open this file");
         exit(0);
    }
    local_time(fp);

    fwrite(strExp, strlen(strExp), 1, fp);
    fclose(fp);
}
