// Вторая программа. Данная программа ответственна за занесение данных в pipe()

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
 
int main(int argc, char* argv[]){

    int fd[2];
    ssize_t size;
    char str[13]={"Second pipe!"};
 
    // Аргументы приходят в виде const char*. Необходимо преобразовать в число. Заведомо известно, что там кроме чисел ничего быть не может
    fd[0] = atoi(argv[0]);
    fd[1] = atoi(argv[1]);
 
    // Закрытие входного потока данных
    close(fd[0]);
    size=write(fd[1], str, 13);
    if (size!=13)
    {
        printf("Error! Cant't read!\n");
        exit(-1);
    }
    
    // Закрытие выходного потока данных
    close(fd[1]);
    return 0;
}
