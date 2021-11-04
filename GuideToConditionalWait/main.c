//
// Created by tokoyama on 04/11/21.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int fuel = 0;
pthread_cond_t condShm;
pthread_mutex_t mutexfuel;

void *fuel_filling(void *args) {
    printf("FILLING FUEL\n");
    for (int i = 0; i < 5; ++i) {
        pthread_mutex_lock(&mutexfuel);
        fuel += 15;
        printf("filled fuel, current fuel level: %d\n", fuel);
        pthread_mutex_unlock(&mutexfuel);
//        if(fuel>40)
//        {
            pthread_cond_signal(&condShm);
//        }
        sleep(1);
    }
}

void *car(void *arg) {

    printf("here to get fuel\n ");
    pthread_mutex_lock(&mutexfuel);
    while (fuel<40)
    {
        printf("Waiting for fuel\n");
        pthread_cond_wait(&condShm, &mutexfuel);
    }
    fuel -= 40;
    printf("removed fuel, current fuel level: %d\n", fuel);
    pthread_mutex_unlock(&mutexfuel);

}

int main() {
    pthread_t th[2];
    pthread_mutex_init(&mutexfuel, NULL);
    pthread_cond_init(&condShm, NULL);
    if (pthread_create(&th[0], NULL, &car, NULL) != 0) {
        perror("failed to create thread");
    }
    if (pthread_create(&th[1], NULL, &fuel_filling, NULL) != 0) {
        perror("failed to create thread");
    }

    for (int j = 0; j < 2; ++j) {
        if (pthread_join(th[j], NULL) != 0) {
            perror("failed to join thread");
        }

    }
    pthread_mutex_destroy(&mutexfuel);
    pthread_cond_destroy(&condShm);
    return 0;
}
