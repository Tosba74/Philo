#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void    *func1(void *arg)
{
    int i = -1;
    char *str = arg;
    //pthread_cond_wait(&cond, &mutex);
    pthread_mutex_lock(&mutex);
    while (str[++i])
    {
        dprintf(2, "\033[32m%c\033[0m", str[i]);
        usleep(100000);
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void    *func2(void *arg)
{
    int i = -1;
    char *str = arg;
    pthread_mutex_lock(&mutex);
    while (str[++i])
    {
        dprintf(2, "\033[33m%c\033[0m", str[i]);
        usleep(100000);
    }
    //pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(int ac, char **av)
{
    pthread_t p1;
    pthread_t p2;

    if (ac == 3)
    {
        pthread_create(&p1, NULL, &func1, av[1]);
        pthread_join(p1, NULL);
        pthread_create(&p2, NULL, &func2, av[2]);
        pthread_join(p2, NULL);
        pthread_mutex_destroy(&mutex);
    
    }
    return 0;
}
