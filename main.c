#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {

    int file_descriptor[2];
    int numero[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sommapari = 0;
    int sommadispari = 0;
    int risultato = 0;
    pipe(file_descriptor);
    pid_t pid = fork();
    if (pid == 0) {
        close(file_descriptor[0]);
        for (int i = 0; i < 10; i++) {
            if (numero[i] % 2 == 0) {
                sommapari += numero[i];
            }
        }
        write(file_descriptor[1], &sommapari, sizeof(sommapari));
        close(file_descriptor[1]);
        exit(0);
    } else {
        close(file_descriptor[1]);
        for (int i = 0; i < 10; i++) {
            if (numero[i] % 2 != 0) {
                sommadispari += numero[i];
            }
        }
        read (file_descriptor[0], &sommadispari, sizeof(sommadispari));
        close(file_descriptor[0]);
        wait(NULL);

        risultato = sommapari + sommadispari;
        printf("Somma dispari: %d\n", sommadispari);
        printf("Somme pari: %d\n", sommapari);
        printf("Somma totale: %d\n", risultato);
    }
    return 0;
}