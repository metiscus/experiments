#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char** argv)
{
    short pid = 0;
    int c = '#';
    while(c)
    {
        printf("Menu:\n");
        printf("1.) VLC\n");
        printf("2.) gedit:\n");
        c = fgetc(stdin);
        if(c >= '1' && c<='2')
        {
            if(pid !=0)
            {
                kill(pid, 9);
                pid = 0;
            }

            char *args [] = { "derp.mp3", NULL };

            pid = fork();
            if(pid == 0)
            {
                switch (c)
                {
                case '1':
                    execv("/usr/bin/vlc", args);
                    exit(0);
                    break;
                case '2':
                    execv("/usr/bin/gedit", NULL);
                    exit(0);
                    break;
                }
            }
        }
    }
}
