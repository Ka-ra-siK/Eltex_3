// Первая программа. Её необходимо запускать.
// Данная программа выводит в консоль информацию, которая была занесена в pipe() второй программой.

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
 
int main( int argc, char *argv[]) {

    int fd[2], newProc;
    size_t size;
    char str[13];

    // для передачи значения дескриптора в другую программу необходимо int преобразовывать в char
    char fd0[11], fd1[11];

    if(pipe(fd) < 0) {
        printf("Erorr! Can not create pipe!\n");
        exit(-1);
    }

    newProc = fork();

    if (newProc < 0) {
        printf("Erorr! Can not create child!\n");
        exit(-1);

    } else if (newProc > 0) {
        // Внутри родительского процесса
        // Закрытие выходного потока данных
        close(fd[1]);

        read(fd[0], str, 140);
        
        // Закрытие входного потока данных
        close(fd[0]);
        printf ("Reading result: %s\n", str);

    } else {
        // Внутри порождённого процесса
        // Запись первого аргумента в массив символов
        sprintf(fd0, "%d", fd[0]);
        
        //Запись второго аргумента в массив символов
        sprintf(fd1, "%d", fd[1]);
        
        execl("./second11", fd0, fd1, NULL);
    }

    return 0;
}
