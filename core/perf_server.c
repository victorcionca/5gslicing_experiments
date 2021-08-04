#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <signal.h>

#define BUFSIZE 1024

void main(int argc, char *argv[0]){
    int sockfd;
    int optval;
    struct sockaddr_in server_addr;
    char buf[BUFSIZE];
    const char* monitored_process;
    pid_t current_perf_process = 0;
    char perf_output_file[] = "perf_stat_000";

    // Read the monitored process pid from the command line
    if (argc < 2){
        printf("Usage: %s <pid>\n", argv[0]);
        return;
    }
    monitored_process = argv[1];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0){
        printf("Error creating socket\n");
        return;
    }

    optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int));

    memset((void*)&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons((unsigned short)54321);

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Error binding socket\n");
        return;
    }

    while (1){
        int recvd;
        recvd = recv(sockfd, buf, BUFSIZE, 0);
        if (recvd < 0){
            printf("Error while receiving packet\n");
            return;
        }

        printf("Received %d: %s (", recvd, buf);
        for (int i=0;i<recvd; i++) printf(" %02hhx", buf[i]);
        printf("\n");
        /* check packet */
        if (buf[0] == (char) 0xC0 && buf[1] == (char) 0xFF && buf[2] == (char) 0xEE){
            printf("Received command\n");
            // Message structure
            // buf[3] -- command: 1 is start 0 is stop
            // buf[4] -- current rate (uint8_t)
            if (buf[3] == 1){
                printf("Start measurement at rate %hhu\n", buf[4]);
                if (current_perf_process){
                    printf("perf is already running\n");
                    continue;
                }
                // Perf is not running yet, must run it now.
                sprintf(perf_output_file, "perf_stat_%03hhu", buf[4]);
                current_perf_process = fork();
                if (!current_perf_process) // In the child
                    execl("/bin/perf", "perf", "stat", "-p",  monitored_process,
                            "-o", perf_output_file, (char*)NULL);
            }else if (buf[3] == 0){
                if (!current_perf_process){
                    printf("perf is not running\n");
                    continue;
                }
                printf("Stop measurement. Rate was %hhu\n", buf[4]);
                kill(current_perf_process, SIGINT);
            }
        }
    }
}

