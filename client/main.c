#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


//#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <strings.h>//
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int rs_fd = -1; // ДЕЯЙПХОРНП ЙЮМЮКЮ
int count =0;
char buf[60];

int OpenChannel(char * comname)
{
struct termios term;

   rs_fd = open(comname ,O_RDWR|O_NOCTTY); /*нРЙПШБЮЕЛ ТЮИКНБШИ ДЕЯЙПХОРНП ДКЪ ГЮОХЯХ Х ВРЕМХЪ.
						         comname - ХЛЪ ЙНЛОНПРЮ, ДКЪ Linux НМН ЛНФЕР АШРЭ, Й ОПХЛЕПС, РЮЙХЛ: /dev/ttyS0 */

   if ( rs_fd==-1 ) return 1;

   bzero(&term, sizeof(term));

   bzero(&term, sizeof(term));

   term.c_cflag = B9600 | CS8 | CLOCAL | CREAD;  /* яЙНПНЯРЭ 9600 АХР/ЯЕЙ, 8 АХР ДЮММШУ,
						                ХЦМНПХПНБЮРЭ СОПЮБКЕМХЕ КХМХЪЛХ Я ОНЛНЫЭЧ ЛНДЕЛЮ, БЙКЧВХРЭ ОПХЕЛ,
						                ББНД - МЕЙЮМНМХВЕЯЙХИ */
   term.c_iflag = IGNPAR;			     /*  ХЦМНПХПНБЮРЭ НЬХАЙХ ВЕРМНЯРХ Х ОНГХЖХНМХПНБЮМХЪ */
   term.c_oflag = 0;

   term.c_lflag = 0;

   term.c_cc[VTIME]    = 100;   /* нОПЕДЕКЪЕЛ РЮИЛЮСР ДКЪ ОПХЕЛЮ ДЮММШУ.
			                 бПЕЛЪ НФХДЮМХЪ СЙЮГШБЮЕРЯЪ Б ДЕЯЪРШУ ДНКЪУ ЯЕЙСМДШ*/
   term.c_cc[VMIN]     = 0;

   tcflush(rs_fd, TCIFLUSH);
   tcsetattr(rs_fd,TCSANOW,&term);

   int statusm;
   ioctl(rs_fd, TIOCMGET, &statusm);
   statusm &= ~TIOCM_DTR;  /* бЙКЧВЮЕЛ ЯХЦМЮКШ DTR Х RTS ДКЪ ОХРЮМХЪ ОПХЕЛНОЕПЕДЮРВХЙНБ
			            (НЯНАЕММНЯРЭ ПЮММХУ БЕПЯХИ sdk1.1). */
   statusm |=  TIOCM_RTS;
   ioctl(rs_fd, TIOCMSET, &statusm);

   return 0;
}

unsigned char Rsio(void)
{
    int i =0;
    count = 0;
    unsigned char c;
    while(1)
    {

    if ( read( rs_fd, &c ,1 ) == 1 )
    {
        printf(": %c", c);
        buf[i]=c;
        i++;
        count++;
        if (c==10)
        {
            buf[i]=0;
            count--;
            break;
        }
    }
}
    //else
      //  throw ex_timeout();
    return 0;
}
/* МЮВЮКН ЯНЙЕРЮ*/

int main(int argc, char *argv[])
{
	char mass0[] = {0xAA, 0x00, 0x25, 0xFF,
			0xAA, 'E', '4', 0xFF,
			0xAA, '4', 'E', 0xFF,
			0xAA, '4', '2', 0xFF,
			0xAA, 'D', '#', 0xFF,
			0xAA, '4', '4', 0xFF,
			0xAA, 'E', '4', 0xFF,
			0xAA, '4', 'F', 0xFF,
			0xAA, '4', '4', 0xFF,
			0xAA, 'E', '4', 0xFF,
			0xAA, '1', 'D', 0xFF,
			0xAA, '4', '4', 0xFF,
			0xAA, 'C', '4', 0xFF,
			0xAA, '2', 'B', 0xFF,
			0xAA, '3', '4', 0xFF,
			0xAA, 'C', '4', 0xFF,
			0xAA, '4', 'B', 0xFF,
			0xAA, '3', '4', 0xFF,
			0xAA, 'A', '3', 0xFF,
			0xAA, '2', ' ', 0xFF,
			0xAA, 0x00, 0xA9, 0xFF };
	char mass1[] = {0xAA, 0x40, 0x18, 0xFF,
			0xAA, 'C', '4', 0xFF,
			0xAA, '4', 'D', 0xFF,
			0xAA, '4', '4', 0xFF,
			0xAA, 'E', '4', 0xFF,
			0xAA, '4', 'F', 0xFF,
			0xAA, '4', '4', 0xFF,
			0xAA, 'G', '4', 0xFF,
			0xAA, '4', 'A', 0xFF,
			0xAA, '4', '4', 0xFF,
			0xAA, 'B', '4', 0xFF,
			0xAA, '4', 'C', 0xFF,
			0xAA, '5', '4', 0xFF,
			0xAA, 0x00, 0xA9, 0xFF };
	char mass2[] = {0xAA, 0x80, 0x00, 0xFF};
	char mass3[] = {0xAA, 0xC0, 0x00, 0xFF};

        int len = 1024;

        int sock;
        struct sockaddr_in addr;

        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0)
        {
            perror("socket");
            return 0;
        }

        addr.sin_family = AF_INET;
        addr.sin_port = htons(3425); // ХКХ КЧАНИ ДПСЦНИ ОНПР...
        addr.sin_addr.s_addr = inet_addr("192.168.0.105");//htonl(INADDR_LOOPBACK);
        if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("connect");
            return 0;
        }
        OpenChannel("/dev/ttyUSB0");
        //rs_fd = open("/home/olga/Рабочий стол/kakashka/client/bin/Debug/file",O_RDONLY);
        if (rs_fd == -1)
        {
            perror("open");
            exit(2);
        }
        char *data;
	write(rs_fd, mass1, sizeof(mass1));
	sleep(3);
	write(rs_fd, mass0, sizeof(mass0));
	while(1)
	{
        Rsio();

            int blocks = count/4;
            data = malloc((blocks - 2)/2);
            int iterator = 0;
            int i;
            for(i = 1; i < blocks - 1; i++)
            {
                data[iterator] = buf[i*4 + 1];
                iterator++;
                data[iterator] = buf[i*4 + 2];
                iterator++;
            }
	data[iterator] = 0;
	
	i = 0;

	printf(buf);
        printf("\n");
        printf(data);
        printf("\n");

        char response[1024] = {0};
        send(sock, data, sizeof(data)+32, 0);
        free(data);

        int respDataCount = recv(sock, response, sizeof(response), 0);
        printf(response);
        printf("\n");
		
	respDataCount = recv(sock, response, sizeof(response), 0);
        printf(response);
        printf("\n");
	    
	sleep(1);
	if (response[0] == '1')
		write(rs_fd, mass3, sizeof(mass3));
	else
		write(rs_fd, mass2, sizeof(mass2));
           
            
            //sleep(5);
        }
            return 0;
}
