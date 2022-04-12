

/* Программа, осуществляющая однонаправленную связь через pipe между процессом-родителем и процессом-ребенком */


#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
int fd[2], result;
size_t size;
char resstring[14];

/* Попытаемся создать pipe */

if(pipe(fd) < 0){

/* Если создать pipe не удалось, печатаем об этом сообщение и прекращаем работу */

printf("Can\'t create pipe\n");
exit(-1);
}

/* Порождаем новый процесс */

result = fork();

if(result <0){

/* Если создать процесс не удалось, сообщаем об этом и завершаем работу */

printf("Can\'t fork child\n");
exit(-1);

} else if (result > 0) {

/* Мы находимся в родительском процессе, который будет передавать информацию процессу-ребенку . В этом процессе выходной поток данных нам не понадобится, поэтому закрываем его.*/

close(fd[0]);

/* Пробуем записать в pipe 14 байт, т.е. всю строку "Hello, world!"
вместе с признаком конца строки */

size = write(fd[1], "Hello, world!", 14);

if(size != 14){

/* Если записалось меньшее количество байт, сообщаем об ошибке и завершаем работу */

printf("Can\'t write all string\n");
exit(-1);
}

/* Закрываем входной поток данных и на этом родитель прекращает работу */

close(fd[1]);
printf("Parent exit\n");

} else {

/* Мы находимся в порожденном процессе, который будет получать информацию от процесса-родителя. Он унаследовал от родителя таблицу открытых файлов и, зная файловые дескрипторы, соответствующие pip'у, может его использовать. В этом процессе входной поток данных нам не понадобится, поэтому закрываем его.*/

close(fd[1]);

/* Пробуем прочитать из pip'а 14 байт в массив, т.е. всю записанную строку */

size = read(fd[0], resstring, 14);

if(size < 0){

/* Если прочитать не смогли, сообщаем об ошибке и завершаем работу */

printf("Can\'t read string\n");
exit(-1);
}

/* Печатаем прочитанную строку */

printf("%s\n",resstring);

/* Закрываем входной поток и завершаем работу */

close(fd[0]);

}

return 0;
} 