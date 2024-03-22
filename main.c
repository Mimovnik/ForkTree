#include <unistd.h>
#include <stdio.h>

int main() {
  int n = 8;
  for(int i = 0; i < n; i++) {
    if(i % 4 == 0) {
      int left = fork();
      if(left == 0) {
        waitpid(getppid(), NULL, 0);
        return 0;
      }
      int pid = fork();
      if(pid != 0) {
        waitpid(pid, NULL, 0);
        return 0;
      }
    }
    else if(i % 4 == 2){
      int pid = fork();
      if(pid != 0) {
        int right = fork();
        if(right == 0) {
          waitpid(getppid(), NULL, 0);
          return 0;
        }
        waitpid(pid, NULL, 0);
        return 0;
      }
    }else {
      int pid = fork();
      if(pid != 0) {
        waitpid(pid, NULL, 0);
        return 0;
      }
    }
  }
  execlp("ps", "-u mimovnik", "--forest", NULL);
  return 0;
}
