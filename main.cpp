#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAX_LENGTH 320 //最大使用内存为320KB

//---------------进程状态结构体-------------
typedef struct Process
{
    int num;   //作业号
    int size;  //作业大小
    int ctime; //作业进入时间
    int gtime; //作业运行时间
    int rtime; //作业运行时长
    int state; //进程状态有三种 0.未被调入内存执行 1.正在占用CPU执行 2.执行完，释放内存
} Process;
//---------------内存状态结构体-------------
typedef struct Memory
{
    int ID;
    int start;
    int size;
    int state; //内存状态有三种 0.尚未使用 1.使用 2.释放
    struct Memory *prior;
    struct Memory *next;
} * MemoryLinkList;

int f;
Process *Before_Sort; //排序前
Process *After_Sort;  //排序后
Process *temp;
/*
*功能:延时
*参数:无
*/
void delay()
{
    for (int x = 10000; x > 0; x--)
        for (int y = 1000; y > 0; y--)
            ;
}
/*
*功能:初始化链表
*参数:通过地址引用将链表传递给函数
*返回值:链表p
*/
MemoryLinkList initPartitionList(MemoryLinkList &p)
{
    p = (MemoryLinkList)malloc(sizeof(Memory));
    if (!p)
    {
        exit(0);
    }
    p->size = 320;
    printf("输入分区首地址");
    scanf("%d", &p->start);
    p->state = 0;
    p->next = NULL;
    p->prior = NULL;
    return p;
}
/*
*功能:输入各个进程的信息并将进程按照到达时间排序
*参数:进程的个数n
*输出:无
*/
int putIn(int &n)
{
    int i;
    Process temp;
    //printf("请输入任务数目:");
    //scanf("%d", &n);
    n = 9;
    Before_Sort = (Process *)malloc(n * sizeof(Process));
    After_Sort = (Process *)malloc(n * sizeof(Process));

    for (int i = 0; i < n; i++)
    {
        Before_Sort[i].num = i + 1;
        Before_Sort[i].state = 0; //默认状态为0
    }
    Before_Sort[0].size = 30;
    Before_Sort[0].ctime = Before_Sort[0].gtime = 0;
    Before_Sort[0].rtime = 10;
    Before_Sort[1].size = 28;
    Before_Sort[1].ctime = Before_Sort[1].gtime = 5;
    Before_Sort[1].rtime = 15;
    Before_Sort[2].size = 15;
    Before_Sort[2].ctime = Before_Sort[2].gtime = 6;
    Before_Sort[2].rtime = 16;
    Before_Sort[3].size = 6;
    Before_Sort[3].ctime = Before_Sort[3].gtime = 10;
    Before_Sort[3].rtime = 5;
    Before_Sort[4].size = 78;
    Before_Sort[4].ctime = Before_Sort[4].gtime = 10;
    Before_Sort[4].rtime = 10;
    Before_Sort[5].size = 108;
    Before_Sort[5].ctime = Before_Sort[5].gtime = 16;
    Before_Sort[5].rtime = 3;
    Before_Sort[6].size = 320;
    Before_Sort[6].ctime = Before_Sort[6].gtime = 18;
    Before_Sort[6].rtime = 20;
    Before_Sort[7].size = 60;
    Before_Sort[7].ctime = Before_Sort[7].gtime = 22;
    Before_Sort[7].rtime = 17;
    Before_Sort[8].size = 18;
    Before_Sort[8].ctime = Before_Sort[8].gtime = 22;
    Before_Sort[8].rtime = 30;
    //    for (i = 0; i < n; i++)
    //    {
    //        printf("\n请输入信息\n");
    //        printf("作业号:");
    //        scanf("%d", &Before_Sort[i].num);
    //        printf("作业大小:");
    //        scanf("%d", &Before_Sort[i].size);
    //        printf("作业进入时间:");
    //        scanf("%d", &Before_Sort[i].ctime);
    //        printf("作业运行时间:");
    //        scanf("%d", &Before_Sort[i].rtime);
    //        Before_Sort[i].state = 0; //默认状态为0
    //    }
    for (int j = 0; j < n; j++)
    {
        for (i = j; i < n; i++)
        {
            if (Before_Sort[j].ctime > Before_Sort[i].ctime)
            {
                temp = Before_Sort[j];
                Before_Sort[j] = Before_Sort[i];
                Before_Sort[i] = temp;
            }
        }
        After_Sort[j] = Before_Sort[j];
    }
    for (i = 0; i < n; i++)
    {
        printf("排序后的顺序由下表(从小到大):");
        printf("%d %d %d %d\n", After_Sort[i].num, After_Sort[i].size, After_Sort[i].ctime, After_Sort[i].rtime);
    }
    return 0;
}

/*
*全名:showPartitionSpecificationTable
*功能:显示分区说明表
*参数:包含内存信息的链表
*输出:控制台显示分区说明表的具体信息
*/
void showPartSpeTab(MemoryLinkList pl)
{
    printf("\n\t\t\t分区说明表\n");
    printf("\t-----------------------------------------\n");
    printf("\t  区号\t分区长度\t    起始地址     \t状态\n");
    printf("\t-----------------------------------------\n");
    while (pl)
    {
        printf("\t\t%d\t\t%d\t\t\t%d\t\t", pl->ID, pl->size, pl->start);
        if (pl->state == 0)
            printf("\t未分配\n");
        if (pl->state == 1)
            printf("\t已分配\n");
        pl = pl->next;
    }
    printf("\t-----------------------------------------\n");
}

/*
*功能:显示可用表
*思想:同分区说明表不同的一点是把已分配的分区排除
*参数:包含内存信息的链表
*输出:控制台显示可用表的具体信息
*/
void showUsableForm(MemoryLinkList pl)
{
    printf("\n\t\t\t可用表\n");
    printf("\t----------------------------------\t\n");
    printf("\t  区号\t分区长度\t\t起始地址\n");
    printf("\t----------------------------------\t\n");
    while (pl)
    {
        if (pl->state == 0)
            printf("\t\t%d   \t%d\t\t%d\n", pl->ID, pl->size, pl->start);
        pl = pl->next;
    }
    printf("\t-----------------------------------\n");
}

/*
*功能:回收模拟的内存
*功能具体描述:当进程结束后,内存空间释放,链表中的结构会相应的改变,具体的,就是相邻的空间会合并
*思想:1.分四种情况,回收的内存前方向有空闲内存空间,后方向有空闲内存空间,前后方向都有空闲内存空间,前后方向都没有空闲内存空间
*实现:删除相应的链表指针并重新设置新指针结构
*参数:第一个参数是正结束完的进程, 需要回收相应的内存空间,第二个是
*/
void callBack(MemoryLinkList pl3, MemoryLinkList &pl)
{
    while (pl3)
    {
        if (pl3->state == 0)
        {
            //当前驱后继都存在时且前驱未分配后继已分配,执行下列算法
            //------------------------------------------------------------------------------
            if (pl3->next && pl3->prior && pl3->prior->state == 0 && pl3->next->state == 1)
            {
                pl3->size += pl3->prior->size;
                pl3->start = pl3->prior->start;
                pl3->state = 0;
                pl3->ID = 0;
                if (pl3->prior->prior)
                {
                    pl3->prior->prior->next = pl3;
                    pl3->prior = pl3->prior->prior;
                }
                else
                {
                    pl3->prior = pl3->prior->prior;
                    pl = pl3;
                    pl3 = pl;
                }
            }
            //------------------------------------------------------------------------------

            //当前驱后继都存在时且前驱已分配后继未分配,执行下列算法
            //------------------------------------------------------------------------------
            else if (pl3->prior && pl3->next && pl3->next->state == 0 && pl3->prior->state == 1)
            {
                pl3->size += pl3->next->size;
                pl3->state = 0;
                pl3->ID = 0;
                if (pl3->next->next)
                {
                    pl3->next->next->prior = pl3;
                    pl3->next = pl3->next->next;
                }
                else
                {
                    pl3->next = pl3->next->next;
                }
            }
            //------------------------------------------------------------------------------

            //当前驱不存在时,执行以下算法
            //------------------------------------------------------------------------------
            else if (!pl3->prior)
            {
                if (pl3->next && pl3->next->state == 0)
                {
                    pl3->size += pl3->next->size;
                    pl3->state = 0;
                    pl3->ID = 0;
                    if (pl3->next->next)
                        pl3->next->next->prior = pl3;
                    pl3->next = pl3->next->next;
                }
                else
                {
                    pl3->state = 0;
                }
            }
            //------------------------------------------------------------------------------

            //当后继不存在时,执行以下算法
            //------------------------------------------------------------------------------
            else if (!pl3->next)
            {
                if (pl3->prior && pl3->prior->state == 0)
                {
                    pl3->size += pl3->prior->size;
                    pl3->state = 0;
                    pl3->ID = 0;
                    pl3->start = pl->start;
                    if (pl3->prior->prior)
                    {
                        pl3->prior->prior->next = pl3;
                        pl3->prior = pl3->prior->prior;
                    }
                    else
                    {
                        pl3->prior = NULL;
                        pl = pl3;
                        pl3 = pl;
                    }
                }
                else
                {
                    pl3->state = 0;
                }
            }
            //------------------------------------------------------------------------------

            //当前驱后继都存在时且前驱未分配后继未分配,执行下列算法
            //------------------------------------------------------------------------------
            else if (pl3->next && pl3->prior && pl3->next->state == 0 && pl3->prior->state == 0)
            {
                pl3->size = pl3->size + pl3->next->size + pl3->prior->size;
                pl3->state = 0;
                pl3->ID = 0;
                pl3->start = pl3->prior->start;
                if (pl3->next->next)
                    pl3->next->next->prior = pl3;
                if (pl3->prior->prior)
                {
                    pl3->prior->prior->next = pl3;
                    pl3->next = pl3->next->next;
                    pl3->prior = pl3->prior->prior;
                }
                else
                {
                    pl3->next = pl3->next->next;
                    pl3->prior = pl3->prior->prior;
                    pl = pl3;
                    pl3 = pl;
                }
            }
            //------------------------------------------------------------------------------
        }
        //下一个内存空间
        pl3 = pl3->next;
    }
}

void firstFit(MemoryLinkList block_first, int n)
{
    int t = 0;
    int num = n;
    while (num)
    {
        MemoryLinkList pl1 = block_first, q = block_first, pl2;
        printf(" 时钟 :%d\n", t);

        //如果当前的时间正好是结束时间,则将此进程结束并置标志位
        for (int m = 0; m < n; m++)
        {
            if (t == After_Sort[m].gtime + After_Sort[m].rtime)
            {
                num -= 1;
                After_Sort[m].state = 2;
                while (q)
                {
                    if (q->ID == After_Sort[m].num)
                    {
                        q->state = 0;
                        callBack(block_first, block_first);
                    }
                    q = q->next;
                }
                q = block_first;
                printf("当前正在退出某进程\n");
                showPartSpeTab(block_first);
                showUsableForm(block_first);
            }
        }
        //如果是开始时间则开始改变状态
        //        for (int m = 0; m < n; m++)
        //        {
        //
        //        }
        //如果是开始时间,则执行以下算法
        for (int m = 0; m < n; m++)
        {
            if (t == After_Sort[m].ctime)
            {
                After_Sort[m].state = 1;
                printf(" 作业 :%d已到达 ,对其分配!\n", After_Sort[m].num);
            }
            if (t == After_Sort[m].gtime)
            {
                //如果当前pl1的空间存在且pl1已分配或者空间不够分配,则寻找下一个指针
                while (pl1 && (pl1->state == 1 || pl1->size < After_Sort[m].size))
                    pl1 = pl1->next;
                //在pl1中寻找到合适的空间
                if (!pl1)
                {
                    printf(" 内存不足，等待释放 \n");
                    ;
                    for (int i = m; i < n; i++)
                        After_Sort[i].gtime += 1;
                    callBack(block_first, block_first);
                    showPartSpeTab(block_first);
                }
                if (pl1)
                {
                    pl2 = (Memory *)malloc(sizeof(Memory));
                    pl2->start = pl1->start + After_Sort[m].size;
                    pl2->state = 0;
                    pl2->ID = 0;
                    pl2->size = pl1->size - After_Sort[m].size;
                    if (pl2->size > 5)
                    {
                        pl1->size = After_Sort[m].size;
                        pl1->state = 1;
                        pl1->ID = After_Sort[m].num;
                        if (pl1->next)
                            pl1->next->prior = pl2;
                        pl2->next = pl1->next;
                        pl2->prior = pl1;
                        pl1->next = pl2;
                        pl1 = block_first;
                    }
                    else
                    {
                        pl1->state = 1;
                        pl1->ID = After_Sort[m].num;
                    }
                    showPartSpeTab(block_first);
                    showUsableForm(block_first);
                }
            }
        }
        t += 1;
        delay();
    }
}
/*
*功能:主函数,提供选择界面
*变量:p-链表,n-进程个数,ch-参数提供选择,f-循环变量
*/
int main()
{
    MemoryLinkList p;
    int n, ch;
    ch = 0;
    f = 1;
    printf("-----------------------------------------------------\n");
    printf("                动态分区分配存储管理系统                 \n");
    printf("-----------------------------------------------------\n");
    printf("请输入作业信息                                         \n");
    printf("-----------------------------------------------------\n");
    putIn(n);
    while (f)
    {
        printf("------------------------------------------------------\n");
        printf("1------>  最先适应\n");
        printf("2------>  最佳适应\n");
        printf("3------>  最坏适应\n");
        printf("------------------------------------------------------\n");
        printf("请输入选择： \n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            initPartitionList(p);
            firstFit(p, n);
            ch = 0;
            break;
        case 2:
            initPartitionList(p);
            //Nextfit(p, n);
            ch = 0;
            break;
        case 3:
            f = 0;
            break;
        }
    }
}