#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
int main(int argc, char **argv) {
    int fd;
    char buffer[1024];
    printf("Logger iniciado. Esperando goles...\n");
    
   
    while(1){
    // borrar FIFO por si existiera previamente
    unlink("fifo_tenis");

     /* crear el FIFO */
     if (mkfifo("fifo_tenis", 0666)<0) {
         perror("No puede crearse el FIFO");
         return(1);
     }
     /* Abrir el FIFO */
     if ((fd = open("fifo_tenis", O_RDONLY)) < 0) {
         perror("No puede abrirse el FIFO");
         return(1);
     }
     /* Leer de la FIFO */
     int partida_terminada = 0;
     while (read(fd, buffer, sizeof(buffer) - 1) > 0) {
         // X5: Imprimir el texto en la pantalla
         printf("%s", buffer);
	
	 if(strstr(buffer, "J1: 3") != NULL || strstr(buffer, "J2: 3") != NULL){
	   partida_terminada = 1;
	 }
     }
     close(fd);
    
    if(partida_terminada){
     printf("Fin de la partida. Cerrando logger.\n");
     unlink("fifo_tenis");
     break;
    }
   }
unlink("fifo_tenis");
return(0);
}
