#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RR(int ID[],int CPU[],int IO[],int arr_s[],int arr_const[],int r , int quantnum)
{FILE *out= fopen("outputRR.txt","a+");
int flag=0,flag_process=0;
int c=0;
int CPU_2[25]={0};
int q =quantnum;
int flagj[25]={0};
char done[25]={0};
for(int t=0 ; t<100 ; t++)
{
    out= fopen("outputRR.txt","a+");
    fprintf(out,"Quantnum:%d \n",q);

    for(int j=0; j< r ; j++)
          {
          if(IO[j]==0 && flagj[ID[j]]==0)
            {
                arr_s[j]=t;
                CPU[j] = CPU_2[ID[j]];
                flagj[ID[j]] = 1;
                compare_up(IO,CPU,ID,arr_s,arr_const,r);

            }
            if(CPU[j] == 0&& IO[j]>0)
            {
                IO[j] = IO[j]-1;
                fprintf(out,"Time:%d  ID:%d  State:  blocking \n",t,ID[j]);
            }

           if(t >= arr_s[j] && CPU[j]>0 && flag==0)
           {
                CPU[j] = CPU[j]-1;
                CPU_2[ID[j]] = CPU_2[ID[j]] +1;
                fprintf(out,"Time:%d  ID:%d  State:  running \n",t,ID[j]);
                flag = 1;
                c=j;
            }
            else if(t >= arr_s[j]&& CPU[j]>0 /*&& flag==1 */&& j!=c)
            {
                fprintf(out,"Time:%d  ID:%d  State:  ready \n",t,ID[j]);
            }

            if(CPU[j]==0 && flag==1&& q>1 && j==c)
            {
                flag_process=1;
            }

            }
        fclose(out);
        if(flag == 0 || q == 1 || flag_process ==1){
            arr_s[c]=t;
                if(arr_s[c] == arr_s[c+1] && flagj[ID[c+1]] == 1)
                {
                    arr_s[c]=t+1;
                }
            compare_up(IO,CPU,ID,arr_s,arr_const,r);
            q =quantnum;
            flag_process=0;
            }
        else {q--;}
        flag=0;
        }

}

void FCFS(int ID[],int CPU[],int IO[],int arr_s[],int arr_const[],int r)
{FILE *out= fopen("outputFCFS.txt","a+");
int flag=0;
int c=0;
int CPU_2[25]={0};
int flagj[25]={0};
char done[25]={0};
for(int t=0 ; t<100 ; t++)
{
    out= fopen("outputFCFS.txt","a+");
    for(int j=0 ; j< r ; j++)
          {
            if(IO[j]==0 && flagj[ID[j]]==0)
            {
                arr_s[j]=t;
                CPU[j] = CPU_2[ID[j]];
                flagj[ID[j]] = 1;
                compare_up(IO,CPU,ID,arr_s,arr_const,r);
            }
            if(CPU[j] == 0 && IO[j] == 0 && done[j]==0){done[j]=turnaround(t-1,arr_const[j],ID[j]);}
            if(CPU[j] == 0&& IO[j]>0)
            {
                IO[j] = IO[j]-1;
                fprintf(out,"Time:%d  ID:%d  State:  blocking \n",t,ID[j]);
            }

           if(t >= arr_s[j] && CPU[j]>0 && flag==0)
           {
                CPU[j] = CPU[j]-1;
                CPU_2[ID[j]] = CPU_2[ID[j]] +1;
                fprintf(out,"Time:%d  ID:%d  State:  running \n",t,ID[j]);
                flag = 1;
                c=j;
            }

            else if(t >= arr_s[j]&& CPU[j]>0 && flag==1 && j!=c)
            {
                fprintf(out,"Time:%d  ID:%d  State:  ready \n",t,ID[j]);
            }
            }
    fclose(out);
    flag=0;
    }
}

void compare_up(int IO[],int CPU[],int ID[],int arr_s[],int arr_const[],int r){
int p=0;
int a;
for(int i=0;i <r ; i++)
{
    for(int j=0 ; j< ( r-i-1) ;j++)
    {
        if(arr_s[j] > arr_s[j+1])
        {
            a = arr_s[j];
            arr_s[j] = arr_s[j+1];
            arr_s[j+1] = a;


            a = arr_const[j];
            arr_const[j] = arr_const[j+1];
            arr_const[j+1] = a;

            a = IO[j];
            IO[j] = IO[j+1];
            IO[j+1] = a;


            a = CPU[j];
            CPU[j] = CPU[j+1];
            CPU[j+1] = a;



            a = ID[j];
            ID[j] = ID[j+1];
            ID[j+1] = a;
        }
        }
    }
for(int i=0;i <r ; i++)
{
    for(int j=0 ; j< ( r-i-1) ;j++)
    {
        if(arr_s[j] == arr_s[j+1])

            {if(ID[j] > ID[j+1])

                {
                a = arr_s[j];
                arr_s[j] = arr_s[j+1];
                arr_s[j+1] = a;

                a = arr_const[j];
                arr_const[j] = arr_const[j+1];
                arr_const[j+1] = a;

                a = IO[j];
                IO[j] = IO[j+1];
                IO[j+1] = a;

                a = CPU[j];
                CPU[j] = CPU[j+1];
                CPU[j+1] = a;

                a = ID[j];
                ID[j] = ID[j+1];
                ID[j+1] = a;

                }
            }

    }

}
}

void put_in_array (char FR, int quantnum , int ch[] , int p)
{   int r=0;
    int ID[25] = {0};
    int CPU[25] = {0};
    int IO[25] = {0};
    int arr_const[25] = {0};
    int arr_s[25] = {0};

    for (int i =p; i>5 ; i=i-8)
    {
        arr_const[r] = ch[i];
        IO [r] = ch[i-2];
        CPU [r] = ch[i-4];
        ID [r] = ch[i-6];
        arr_s[r] = ch[i];
        r++;
    }
    compare_up(IO,CPU,ID,arr_s,arr_const,r);
    if (FR =='0')
                { FCFS(ID,CPU,IO,arr_s,arr_const,r);}
    else if (FR =='1')
                { RR(ID,CPU,IO,arr_s,arr_const,r,quantnum);}
    else
                {printf("Error in selscting scheduling \n");
                    exit(0);}

}
void read_file(char FR, int quantnum)
{
    char ch[100] ;
    FILE *f = fopen("processes.txt","r");
    int i=0;
    int num [100];
    while ((ch[i] =fgetc(f)) !=EOF)
    {
        ch[i] = ch[i];
        num[i] = ch[i]-'0';
        i++;
    }
    fclose(f);
    put_in_array(FR,quantnum,num,i-2);
}
int main()
{
    char FR;
    int quantnum;
    printf("Please insert your scheduling system\n");
    printf("(0 for FCFS and 1 for RR) : ");
    scanf("%c",&FR);
    if(FR == '1')
        {
            printf("Enter your quantum : ");
            scanf("%d",&quantnum);
        }
    read_file(FR,quantnum);
    return 0;
}

