#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <pthread.h>
#include <unistd.h>
#define  ZERO 0
/*
struct filosofo{
	pthread_t filo[5];
	int eatingTimes = ZERO;
};
*/
//printf("Filosofo %d pensa \n", *filo);

pthread_mutex_t mutex_garfo[5];
pthread_t filosofo[5];
int id[5];
	

void pegarGarfo(int *filo){
	pthread_mutex_lock(&(mutex_garfo[*filo]));
	if(*filo <= 4){
		pthread_mutex_lock(&(mutex_garfo[*filo+1]));
		printf("Filosofo %d pensa \n", *filo);
	}
	else{
		pthread_mutex_lock(&(mutex_garfo[0]));
		printf("Filosofo %d pensa \n", *filo);
		return;
	}
}

void largarGarfo(int *filo){
	pthread_mutex_unlock(&(mutex_garfo[*filo]));
	if(*filo <= 4){
		pthread_mutex_unlock(&(mutex_garfo[*filo+1]));
		printf("Filosofo %d come \n", *filo);
	}
	else{
		pthread_mutex_unlock(&(mutex_garfo[0]));
		printf("Filosofo %d come \n", *filo);
		return;
	}
	printf("Filosofo %d terminou de comer \n", *filo);
}


void* vidaFilosofo(void* var){
	int *filo = (int *)(var);
	for(int u = 0; u <= 40; u++){
		
	//	printf("Filosofo %d pensa \n", *filo);
		sleep(2);
		
		pegarGarfo(filo);
	
	//	printf("Filosofo %d come \n", *filo);
		sleep(5);
		largarGarfo(filo);
		
	}
	
	pthread_exit(NULL);	
}

int main(int argc, char** argv) {
//	filosofo  *f;
	for(int i = 0; i <= 4; i++){
		pthread_mutex_init(&(mutex_garfo[i]), NULL);
	}
	for(int j = 0; j <= 4; j++){
		id[j]=j;
		pthread_create(&filosofo[j], NULL, &vidaFilosofo, (void*) &id[j]);
	}
	while(1){
	}
	return 0;
}



