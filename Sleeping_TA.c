#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>


#define NUM_CHAIRS 5
#define NUM_STUDENTS 5

pthread_mutex_t help;
pthread_mutex_t during_help;
sem_t ta_ready; 
sem_t student_ready; 

int student_num = 0;
int infinite = 1;

void* ta(void* arg) {
     
    while (infinite ) {
        sem_wait(&student_ready); 
        pthread_mutex_lock(&help);

        if (student_num > 0) {
            student_num--;
        }
        pthread_mutex_unlock(&help);

        int time;
        pthread_mutex_lock(&during_help);
        time = (rand() % 6) + 1;
        printf("The TA helped the student for %ds\n", time);
        pthread_mutex_unlock(&during_help);
        
        sem_post(&ta_ready);
        sleep(time); 
    }
    return NULL;
}

void* student(void* arg) {
    int student_id = *((int*)arg);
    free(arg);

    while (infinite) {
        sleep(rand() % 6 + 1); 
        if(student_num == 0){
            printf("TA is sleeping \n");
            printf("Student %d awaken TA. \n" , student_id);
        }

        pthread_mutex_lock(&help);
        if (student_num < NUM_CHAIRS) {
            student_num++;
            if(student_num != 1){
            printf("Student %d is come to waiting line. Student number in line: %d \n", student_id, student_num-1  );
            printf("Available chairs: %d \n", NUM_CHAIRS-student_num  );
            }
            
            pthread_mutex_unlock(&help);
            
            sem_post(&student_ready);
            sem_wait(&ta_ready);
            
            pthread_mutex_lock(&during_help);
            printf("Student %d is getting help from TA\n", student_id);
            pthread_mutex_unlock(&during_help);
        } else {
            pthread_mutex_unlock(&help);
            printf("Waiting chairs are full. Student %d is leaving.\n", student_id);
        }
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t ta_thread;
    pthread_t student_threads[NUM_STUDENTS];

    pthread_mutex_init(&help, NULL);
    pthread_mutex_init(&during_help, NULL);
    sem_init(&ta_ready, 0, 1);
    sem_init(&student_ready, 0, 0);

    pthread_create(&ta_thread, NULL, ta, NULL);

    for (int i = 0; i < NUM_STUDENTS; i++) {
        int* student_id = malloc(sizeof(int));
        *student_id = i ;
        pthread_create(&student_threads[i], NULL, student, student_id);
    }

    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_join(student_threads[i], NULL);
    }

    pthread_mutex_destroy(&help);
    pthread_mutex_destroy(&during_help);
    sem_destroy(&ta_ready);
    sem_destroy(&student_ready);

    return 0;
}
