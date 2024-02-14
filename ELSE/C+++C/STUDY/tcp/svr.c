#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>

#define maxsec 20

typedef struct clieninfo
{                 
  int connfdp;            
  signed char padress[20];       
} clieninfoT;

void *createthread(void *vargp);

void *threadsend(void *vargp);
void *threadrecv(void *vargp); 

int exit_flag;

int main(int argc, char **argv)
{ 
	if(argc !=2) 
	{
		printf("start e.g:  ./svr 9001\n");
		return -1;
	}
		
//	printf("argc %d argv[1]: %s \n", argc, argv[1]);
  exit_flag = 1;	
	
  int listenfd = socket(AF_INET, SOCK_STREAM,0);
  if(listenfd < 0)
  {        
    perror("socket err\n");        
    exit(-1);
  }
  
 
  int flags = fcntl(listenfd, F_GETFL, 0);
  fcntl(listenfd, F_SETFL, flags | O_NONBLOCK);
         
  struct hostent *hp;
  struct sockaddr_in serveraddr;
  
  bzero((char *)&serveraddr,sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(atoi(argv[1]));
  
  if(bind(listenfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) < 0)
  {        
    perror("connect error\n");        
    exit(-1);
  }
  
  if(listen(listenfd,10) < 0)
  {        
    perror("listen error");        
    exit(-1);
  } 
  printf("Server started... \n");

  struct sockaddr_in clientaddr;
  int clientlen, i;
  pthread_t sectid[maxsec]; 
  memset(&sectid, 0, maxsec * sizeof(pthread_t));
  i = 0;            
 
 clieninfoT Pclient;
 memset(&Pclient, 0, sizeof(clieninfoT));

  clientlen = sizeof(clientaddr);
  while(exit_flag)
  {
    Pclient.connfdp = accept(listenfd,(struct sockaddr *)&clientaddr, &clientlen);
    if (Pclient.connfdp == -1 && errno == EAGAIN) 
    	{
       //  fprintf(stderr, "no client connections yet\n");
         usleep(100);
         continue;
      }   
    memcpy(Pclient.padress, inet_ntoa(clientaddr.sin_addr ), 20);
    printf("Pclient.padress %s\n", Pclient.padress);
      

    printf("Accepted client  [ip:%s port:%d]\n",inet_ntoa(clientaddr.sin_addr),  htons(clientaddr.sin_port));

    pthread_create(&sectid[i],NULL,createthread,&Pclient);
    usleep(500);
  }
  int m = 0;
  for( m = 0; m < maxsec; m++)
  {
    if(sectid[m] !=0) 
    {
    	printf("sectid  pthread_join .....\n");
       pthread_join(sectid[m], NULL);
       printf("sectid  pthread_join completed\n");
    } 
  }
  
  EXIT_SUCCESS;
}

void *createthread(void *vargp)
{
  pthread_t tid1,tid2;

  pthread_create(&tid1,NULL,threadsend,vargp);
  pthread_create(&tid2,NULL,threadrecv,vargp);
  if(tid1 !=0) 
  {
     pthread_join(tid1,NULL);
     printf("server threadsend  pthread_join completed\n");
  }
  if(tid2 !=0)
  {
     pthread_join(tid2, NULL);
     printf("server threadrecv  pthread_join completed\n");
  }
  printf("server createthread over \n");
  pthread_exit(0);
}

void *threadsend(void * vargp)
{

  int connfd = ((clieninfoT *)vargp)->connfdp;
  
  int idata;
  signed char temp[100];
  while(exit_flag)
  {
  	memset(temp, 0, sizeof(temp));
    fgets(temp, 100, stdin);
    if(strlen(temp) > 0)
    {
      send(connfd, temp, 100, 0);
      printf("             msg send OK\n");    	
    }
    usleep(500);
    if(memcmp(temp, "exit", 4) == 0)
    {
      exit_flag = 0; break;  		
    }    
  }
  printf("server send over and exit \n");
  pthread_exit(0);  
}

void *threadrecv(void *vargp)
{
  char temp[100];

  int connfd = ((clieninfoT *)vargp)->connfdp;
  while(exit_flag)
  {
  	memset(temp, 0, sizeof(temp));
  	int idata = 0;
  	if(!exit_flag) break;
    idata = recv(connfd,temp,100,0);
    if(idata > 0)
    {
      printf("client[%s] message: %s\n", ((clieninfoT *)vargp)->padress, temp);
    }
    usleep(500);    
  }
  printf("server threadrecv over and exit \n");
  pthread_exit(0);
}
