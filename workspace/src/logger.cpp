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
     while (read(fd, buffer, sizeof(buffer) - 1) > 0) {
         // X5: Imprimir el texto en la pantalla
         printf("%s", buffer);
	
     }
     close(fd);
    
unlink("fifo_tenis");
return(0);
}
