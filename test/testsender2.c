#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "sender.h"
// #include <nanomsg/nn.h>
// #include <unistd.h>
// #include <nanomsg/pipeline.h>

static char* buf1;
static char* buf2;
static char* buf3;
static struct NanoSenderSession* nss;

void readFile(char* filepath){
  printf("reading file\n");
  //printf("length:%d\n",length );
  FILE *fp1;
  //char* buf;
  buf1=(char*)malloc(450*sizeof(char));
  buf2=(char*)malloc(4500*sizeof(char));
  buf3=(char*)malloc(45000*sizeof(char));
  //char buf[45551];
  fp1=fopen(filepath,"r");
  printf("opening %s\n",filepath );
  fgets(buf1,449,fp1);
  fgets(buf2,4449,fp1);
  fgets(buf3,44449,fp1);
  printf("get out all the byte\n");
  //buf[length-1]='\0';

  fclose(fp1);
  //return buf;
}


void sig_handler(int signo){
  if(signo==SIGINT){
    printf("free the buffers used\n");
    free(buf1);
    free(buf2);
    free(buf3);
    nss->disconnect(nss);
  }
  exit(0);
}

int main(int argc, char const *argv[])
{
	/* code */
	struct NanoSenderSession* nss;
	nss=newNanoSenderSession(argv[1]);
	nss->connect(nss);
	readFile("./text.txt");


	  int m=0;
  if(signal(SIGINT,sig_handler)==SIG_ERR)
    printf("\ncan not catch SIGINT\n");
   while(1){
  //   if(m%3==0){
      //printf("sending buffer 1:---%d\n",strlen(buf1));
      m++;
      nss->sendMessage(nss,buf1);
      sleep(3);
      m++;
      nss->sendMessage(nss,buf2);
      sleep(2);
      m++;
      nss->sendMessage(nss,buf3);
      sleep(1);
    //}else ifs(m%3==1){
       //printf("sending buffer 2:---%d\n",strlen(buf2));
      //sleep(10);
      //nss->sendMessage(nss,buf2);
    // //}else{
    //   printf("sending buffer 3:---%d\n",strlen(buf3));
      //nss->sendMessage(nss,buf3);
    // //}
    // m++;
    //sleep(30);
      printf("%d msg has sended\n",m );
  }
  //return nss->disconnect(nss);
  return 0;
}
