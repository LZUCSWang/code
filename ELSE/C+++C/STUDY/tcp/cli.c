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

int exit_flag;

void *threadsend(void *vargp);
void *threadrecv(void *vargp); 

int main(int argc, char **argv)
{ 
  if(argc !=3) 
  {
    printf("start e.g:  ./cli 192.168.5.128 9001\n");
    return -1;
  }		
  //printf("argc %d argv[1]: %s argv[2]: %s\n", argc, argv[1], argv[2]);
  exit_flag = 1;	
  int clientfdp;

  clientfdp = socket(AF_INET,SOCK_STREAM,0);
  
//  int flags = fcntl(clientfdp, F_GETFL, 0);
//  fcntl(clientfdp, F_SETFL, flags | O_NONBLOCK);  
  
  struct sockaddr_in serveraddr;struct hostent *hp;
  bzero((char *)&serveraddr,sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(atoi(argv[2]));
  serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
  
  if(connect(clientfdp,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) < 0)
  {        
    printf("Connect error\n");
    exit(-1);
  }
  
  pthread_t tid1,tid2;
  printf("Connect server success.\n");
  pthread_create(&tid1,NULL,threadsend,&clientfdp);
  pthread_create(&tid2,NULL,threadrecv,&clientfdp);  
  

  if(tid1 !=0) 
  {
     pthread_join(tid1,NULL);
     printf("threadsend  pthread_join completed\n");
  }
  if(tid2 !=0)
  {
     pthread_join(tid2, NULL);
     printf("threadrecv  pthread_join completed\n");
  }
  
  close(clientfdp);
  printf("client close\n");
  return EXIT_SUCCESS;
}

void *threadsend(void * vargp)
{

  int connfd = *((int *)vargp);
  int idata;char temp[100];
  while(exit_flag)
  {
    memset(temp, 0, sizeof(temp));

    fgets(temp,100,stdin);
    if(strlen(temp) > 0)
    {    	
      send(connfd,temp,100,0);
      printf("          message send OK\n");   	
    }
    usleep(500);
    if(memcmp(temp, "exit", 4) == 0)
    {
      exit_flag = 0; break;  		
    }
      
  }
  printf("client send over and exit \n");
  pthread_exit(0);
}

void *threadrecv(void *vargp)
{
  char temp[100];
  int connfd = *((int *)vargp);
  while(exit_flag)
  {
    int idata = 0;
    if(!exit_flag) break;
    idata = recv(connfd,temp,100,0);
    if(idata > 0)
    {
      printf("Message from server :%s\n", temp);
    }
    usleep(500); 
  }  
  
  printf("client threadrecv over and exit \n");
  pthread_exit(0);
}

