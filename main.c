#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;
typedef struct Node
{
    Process data ;
    struct Node* next;
} Node;
typedef struct
{
    Node* start;


} Queue;
Queue*init()
{
    Queue*q=malloc(sizeof(Queue)) ;

    q->start=NULL;

    return q;
}
Node*newNode(Process x)
{
    Node*n=malloc(sizeof(Node));
    n->data=x;
    n->next=NULL;
    return n;
}

int isEmpty(Queue*q)
{
    {
        if(q->start==NULL)
            return 1;
        else
            return 0;
    }
    return -1;
}
void enqueue(Queue*q,Process value)
{
    Node*n=newNode(value);
    if(q->start==NULL)
    {
        q->start=n;
    }
    else
    {
        Node *temp= q->start;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=n;
    }
}
Process Deque (Queue *q)
{
    Process x;
    if(q->start!=NULL)
    {

        Node*temp=q->start;
        x=temp->data;
        q->start=q->start->next;
        free(temp);


    }
    else
    {
        exit(0);
    }
    return x;


}

int idle(Queue*q,int t)
{
    Node *temp=q->start;
    int    flag=0;
    while(temp!=NULL)
    {
        if (temp->data.starting_time<=t)
        {
            flag=1;

            break;
        }
        temp=temp->next;


    }
    return flag;

}
void destroy(Queue *q)
{

    while(q->start!=NULL)
    {

        Node*temp = q->start;
        q->start=q->start->next;
        free(temp);
    }
    free(q);

}



void RoundRobin(char* filename)
{
    FILE *fp=fopen(filename,"r");
    Queue*q=init();
    char str[40];
    fgets(str,40,fp);
    char*token;
    int timeslot;
    token=strtok(str," ");
    while(token)
    {
        timeslot=atoi(token);
        token=strtok(NULL," ");
    }
    Process p;
    p.name=(char*)malloc(4);
    while(fscanf(fp,"%s%d%d\n",p.name,&p.starting_time,&p.remaining_time)!=EOF)
    {

        enqueue(q, p);
        p.name=(char*)malloc(4);
    }
    fclose(fp);

    int t=0;
    while(t<timeslot )
    {
        int y=idle(q, t);
        if (y==0)
        {
            printf("idle\t <%d-->%d>\n",t,t+1);
            t++;
        }
        else
        {


            Process temp;
            temp.name=(char*)malloc(4);
            temp=Deque(q);

            if (temp.starting_time<=t)
            {

                int x=temp.remaining_time;
                if(x-1>0)
                {

                    printf("%s\t <%d-->%d>\n",temp.name,t,t+1);
                    temp.remaining_time=x-1;
                    enqueue(q,temp);


                    t++;
                }
                else if(x-1==0)
                {

                    printf("%s\t <%d-->%d>\t %s aborts\n",temp.name,t,t+1,temp.name);
                    t++;
                }
            }
            else
            {
                enqueue(q,temp);

            }



        }
    }
    destroy(q);
    printf("stop\n");
}




int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;
}

