/*
Fue necesario modificar tasks.json para que funcionara pow() agregando el linker -lm:
"args": [
				"-g",
				"${file}",
				"-o",
				"${fileDirname}/bin/${fileBasenameNoExtension}",
				"-lm"
			],

También instalar ncurses. para usar kbhit():
sudo apt-get install libncurses5-dev libncursesw5-dev
*/

#include <stdio.h>
#include <ncurses.h>
#include <sys/time.h>
#include <signal.h>
#include <math.h>
#include <stdbool.h>

#define ms 200
int exponente = -1;
bool flag = true;

void t1_handler();

void main(void)
{

        // Inicializando estructura itimerval
        struct itimerval t1 = {0};  

        // Temporizador único de 200 ms
        t1.it_value.tv_usec = ms*1000;        

        // Temporizador periódico de 200 ms
        t1.it_interval.tv_usec = ms*1000;
        
        //Asignamos el temporizador periódico de 200 ms con el reloj en tiempo real:
        setitimer(ITIMER_REAL, &t1, NULL);
        
        //Asigna a la función t1_handler el manejo de la señal SIGALARM
        //SIGALARM es la señal que se envía cuando expira un límite de tiempo,
        //en este caso el del intervalo de 200 ms.
        signal(SIGALRM, t1_handler);

        //super loop
        while(1);
        //no funcionó la instalación de ncurses.h
        //while(!_kbhit());                                
}

void t1_handler()
{
    //En formato hexadecimal con 4 dígitos para forzar la aparición de ceros,
    //Hay que hacer casting a tipo int porque porque pow() regresa tipo double:
    printf("%04x\n", (int) pow(16,exponente));       

    //Para producir efecto de ascendente y desdencente:
    (flag == true)? exponente++ : exponente--;
    if (exponente > 2) flag = false;
    if (exponente < 0) flag = true;    
}