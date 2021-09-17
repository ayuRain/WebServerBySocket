#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
        int new_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        struct sockaddr_in sockin;
        memset(& sockin, 0, sizeof(sockin));
        sockin.sin_family = AF_INET;
        sockin.sin_port = htons(550);
        sockin.sin_addr.s_addr = inet_addr("172.17.2.74");
	printf("yexiaoyu\n");

        bind(new_sock, (struct sockaddr*)&sockin, sizeof(sockin));


        listen(new_sock, 20);

        struct sockaddr_in get_addr;
        socklen_t get_addr_size = sizeof(get_addr);
        int get_sock = accept(new_sock, (struct sockaddr*)&get_addr,&get_addr_size);
	char buf[1024] = {0};
	recv(get_sock, buf, strlen(buf) - 1, 0);
	printf("%s", buf);

        char QAQ[] = "HTTP/1.1 200 OK \nDate: Sat, 31 Dec 2005 23:59:59 GMT\nContent-Type: text/html;charset=ISO-8859-1\nContent-Length: 11\n\nhello world\n";
        write(get_sock, QAQ, sizeof(QAQ));


        close(get_sock);
        close(new_sock);


        return 0;
}
