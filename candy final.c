#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int buffer,candytype,cx,box,n,full;
int p=0,c=0,in=0,item=0,out=0,bn=0;
int i=0,j=0,boxf=0,b=1;
int bufferlist[99];
char candylist[100][20];
int boxlist[100][100];

pthread_mutex_t mutex;
sem_t sema;

void printallcandy()//to print all candy
{
 for(cx=1;cx<=candytype;cx++)
    {
   printf("%d %s \n",cx,candylist[cx]);
   }

}
void printcandy(int x)//to print a selected candy
{
   printf(" %s ",candylist[x]);

}
void printbox()//to print the boxes
{
  for(int t=0; t<i; t++)
    {
    printf("Box %d:",t+1);
    for(int q=0; q<box; q++)
        {
            if(boxlist[t][q]==-1)
              {printf("EMPTY");}
            else{
              printcandy(boxlist[t][q]);
            }
            printf(" , ");
        }
        printf("\n");
    }
}


void *produce(void *pro)
{
   pthread_mutex_lock(&mutex);
   sem_wait(&sema);

   bufferlist[in]=item;//put the selected candy in buffer
   buffer--;// one buffer space is used
   in=(in+1)%full;//to count the buffer no
   p++;//to count the producer thread number

   sem_post(&sema);
   pthread_mutex_unlock(&mutex);
   pthread_exit(NULL);

}


void *consume(void *con)
{
  pthread_mutex_lock(&mutex);

  buffer++;//one buffer space is free
  boxlist[i][j]=bufferlist[out];//put candy from buffer to box
    j++;
    if(j==box)//to update the index of boxlist array
    {
        i++;
        j=0;
    }

    bufferlist[out]=-1;//put -1 to free buffer space
    out = (out+1)%full;//to count the buffer no
    c++;//to count the consumer thread number
    boxf++;//to count box number

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}




int main(){

printf("Enter Bounded Buffer Size :");
    scanf("%d",&buffer);
 full=buffer;

for(int k=0; k<buffer; k++)
    {
        bufferlist[k]=-1;//to make every element of buffer -1
    }


printf("Enter the number of candy type:");
    scanf("%d",&candytype);


for(cx=1;cx<=candytype;cx++)
    {
        printf("Candy %d: ",cx);
        scanf("%s",candylist[cx]);//enter candy names
    }

 for(int t=0; t<100; t++)
    {
        for(int q=0; q<100; q++)
        {
            boxlist[t][q]=-1;//make -1 to all boxlist elements
        }
    }


printf("Enter capacity in a box: ");
    scanf("%d",&box);//highest number of candy can be put in a box


pthread_t producer[99],consumer[99];
pthread_mutex_init(&mutex, NULL);
sem_init(&sema,0,1);

while(1)
    {
        printf("\n1. Produce candy\n2. Consume candy\n3. Show candy in box\n4. Show empty buffer space\n5. Show candy list\n6. exit");
        printf("\nEnter your choice:");
        scanf("%d",&n);

        if(n==1){//to produce candy

          int h,pPro;
            printf("How many candy you want to produce: ");
            scanf("%d",&pPro);
            for(h=0; h<pPro; h++)
            {
            if(buffer>0){//if buffer has any space to put candy

               printallcandy();
               printf("Enter the candy you want to produce:");
               scanf("%d",&item);//select the candy that want to produce

               pthread_create(&producer[p],NULL, (void*)produce,NULL);//producer thread that send to produce funtion

               int prono=p+1;
               printf("Producer %d produced candy ", prono);
               printcandy(item);//print the candy that want to produce
               printf(" in buffer %d\n",in);

               pthread_join(producer[p], NULL);//start to run the thread

            }
            else
                {
                    printf("###Buffer is full.###\n");
                }

        }
        }
        else if(n==2)
        {
            int v,pCon;
            printf("How many candy you want to consume: ");
            scanf("%d",&pCon);
            for(v=0; v<pCon; v++)
            {
                if(buffer<full)//if buffer is not totally empty
                {

                    pthread_create(&consumer[c], NULL, (void *)consume, NULL);//consumer thread that send to consume function

                    printf("Consumer %d consumed candy ", c+1);
                    printcandy(bufferlist[out]);//print the candy that is consumed by the consumer
                    printf(" from buffer %d\n",bn);
                    bn = (bn+1)%full;//to count the buffer number

                    pthread_join(consumer[c], NULL);//start the thread
                }


                else
                {
                    printf("###Buffer is empty.###\n");
                }
            }

        }

        else if(n==3)
        {
            if(boxf!=0)//if box created
            {
                printbox();
            }
            else
            {
                printf("###No box has been created yet###\n");
            }

        }

        else if(n==4)
        {
            printf("Empty buffer space : %d\n",buffer);
        }

        else if(n==5)
        {
            printallcandy();
        }


        else if(n==6)
        {
            exit(0);
        }
        else
        printf("###Wrong Choice.###\n");
    }
    pthread_mutex_destroy(&mutex);
    return 0;

}
