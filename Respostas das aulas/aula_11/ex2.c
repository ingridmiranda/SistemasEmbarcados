#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int fd;

void fechar_programa(){
	close(fd);
	fd = open("/sys/class/gpio/unexport",O_WRONLY);
	write(fd,"4",2);
	printf("Fechando programa\n");
	close(fd);
	sleep(1);
	exit(0);
}




int main(){

float frequencia;
float periodo;

	signal(SIGINT,fechar_programa);

	//Setar frequencia
	printf("Digite a frequência desejada em Hz:");
	scanf("%f", &frequencia);
	periodo = 1000000/(2*frequencia);

	//Setando como export
	printf("Realizar o export\n");
	fd = open("/sys/class/gpio/export",O_WRONLY);
	write(fd,"4",2);
	close(fd);
	sleep(1);

	//Setando como saída
	printf("Setar o pin como saída\n");
	fd = open("/sys/class/gpio/gpio4/direction",O_WRONLY);
	write(fd,"out",4);
	close(fd);
	sleep(1);



	fd = open("/sys/class/gpio/gpio4/value",O_WRONLY);
	printf("Iniciando o blink\n");
	while(1){
		write(fd,"1",2);
		usleep(periodo);
		write(fd,"0",2);
		usleep(periodo);
	}

	return 0;
}
