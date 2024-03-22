#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

void grow_leaf();
void grow_branch();
void grow_branch_and_leaf();

int main() {
  int n = 8;
  for(int i = 0; i < n; i++) {
    if(i % 4 == 0) {
      grow_leaf();
      grow_branch();
    }
    else if(i % 4 == 2) {
      grow_branch_and_leaf();
    }
    else{
      grow_branch();
    }
  }
  execlp("ps", "-u mimovnik", "--forest", NULL);
  return 0;
}

// creates a new proccess that waits for its parent to finish
void grow_leaf() {
  int pid = fork();
  if(pid == -1) {
    perror("fork() failed\n");
    exit(1);
  }
  if(pid == 0) {
    waitpid(getppid(), NULL, 0);
    exit(0);
  }
}

// creates a new proccess and waits for it to finish
void grow_branch() {
  int pid = fork();
  if(pid == -1) {
    perror("fork() failed\n");
    exit(1);
  }
  if(pid != 0) {
    waitpid(pid, NULL, 0);
    exit(0);
  }
}

// creates a new proccess and waits for it to finish also creates a leaf before waiting
void grow_branch_and_leaf(){
  int pid = fork();
  if(pid == -1) {
    perror("fork() failed\n");
    exit(1);
  }
  if(pid != 0) {
    grow_leaf();
    waitpid(pid, NULL, 0);
    exit(0);
  }
}

