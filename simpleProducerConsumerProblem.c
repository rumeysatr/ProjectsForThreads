/*
Üretici thread bir buffer’a veri eklerken, 
tüketici thread buffer’dan veri çeker.
Buffer’ın senkronizasyonu için mutex kullanılır.
Örneğin, üretici bir diziyi doldururken tüketici 
bu diziden eleman alır ve ekrana yazdırır.
*/

#include <pthread.h>

#define BUFFER_SIZE 10 // buffer boyutu (dizi için gerekli)

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex; //mutex değişkeni
pthread_cond_t full;	//buffer dolu olan koşul değişkeni
pthread_cond_t empty;	//buffer boş olan koşul değişkeni

int main()
{
	pthread_t prod_t, cons_t;

	pthread_mutex_init(&mutex, NULL); 
	pthread_cond_init(&full, NULL);
	pthread_cond_init(&empty, NULL);

	pthread_create(&prod_t, NULL, producer, NULL); //üretici thread
	pthread_create(&cons_t, NULL, consumer, NULL); //tüketici thread

	pthread_join(prod_t, NULL); //üretici threadin işi bitene kadar bekliyor
	pthread_join(cons_t, NULL); //tüketici threadin işi bitene kadar bekliyor

	pthread_

}