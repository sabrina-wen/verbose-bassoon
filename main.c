#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  int fds[2]; // for parent to child pipe
  int fds2[2]; // for child to parent pipe
  pipe(fds);
  pipe(fds2);
  int READ = 0;
  int WRITE = 1;

  int f = fork(); // create child process whose id is 0
  if (f != 0) { // if parent process
    close(fds[READ]);
    int num = 82;
    write(fds[WRITE], &num, sizeof(num));
    printf("[parent] sending: %d\n", num);
    //printf("parent pid: %d\n", getpid());
  }
  if (f == 0) { // if child process
    //printf("child pid: %d\n", getpid());
    close(fds[WRITE]);
    int num;
    read(fds[READ], &num, sizeof(num));
    printf("[child] doing witchcraft on: %d\n", num);
    num += 11;
    //printf("new val of num: %d\n", num);
    close(fds2[READ]);
    write(fds2[WRITE], &num, sizeof(num));
    printf("[child] sending magic: %d\n", num);
  }

  if (f != 0) { // back to parent process
    close(fds2[WRITE]);
    int num;
    read(fds2[READ], &num, sizeof(num));
    printf("[parent] recieved new val: %d\n", num);
  }

  return 0;
}
