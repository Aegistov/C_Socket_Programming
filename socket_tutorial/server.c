#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int		main(void)
{
	int			listenfd;
	int			connfd;
	struct	sockaddr_in	serv_addr;
	char		send_buff[1025];
	time_t		ticks;

	listenfd = 0;
	connfd = 0;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(send_buff, '0', sizeof(send_buff));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000);

	bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	listen(listenfd, 10);

	while (1)
	{
		connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);

		ticks = time(NULL);
		snprintf(send_buff, sizeof(send_buff), "%.24s\r\n", ctime(&ticks));
		write(connfd, send_buff, strlen(send_buff));

		close(connfd);
		sleep(1);
	}
}
