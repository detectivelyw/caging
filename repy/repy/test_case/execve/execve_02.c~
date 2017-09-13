#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    int ret;
    char cmd_send[100] = "";
    char env_send[100] = ""; 
    const char* cmd_ptr;
    const char* env_ptr;
    ret = 0;

    char *cmd[] = { "ls", "-l", (char *)0 };
    char *env[] = { "HOME=/usr/home", "LOGNAME=home", (char *)0 };

    int i;
    for (i = 0; ; i++) {
      if (cmd[i] == NULL) {
        strcat(cmd_send, "\0");
        break; 
      }
      else {
        strcat(cmd_send, cmd[i]);
        strcat(cmd_send, " ");
      }
    }

    for (i = 0; ; i++) {
      if (env[i] == NULL) {
        strcat(env_send, "\0");
        break; 
      }
      else {
        strcat(env_send, env[i]);
        strcat(env_send, " ");
      }
    }

    cmd_ptr = cmd_send;
    env_ptr = env_send;

    printf("cmd: %s \n", cmd_ptr);
    printf("env: %s \n", env_ptr);

    return 0;
}
