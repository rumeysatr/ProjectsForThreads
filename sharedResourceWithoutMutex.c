/*
Birden fazla iş parçacığı tarafından erişilen 
paylaşılan bir değişken (örneğin bir sayaç) oluşturun. 
Her iş parçacığında sayacı artırın. Yarış koşulları nedeniyle 
hatalı sonuçları gözlemleyin.
*/

#include <pthread.h>
#include <stdio.h>

#define NUM_T 5
#define NUM_INC 100000

int counter = 0;

void *func(void *arg)
{
	for (int i = 0; i < NUM_INC; i++)
		counter++;
	return NULL;
}

int main()
{
	pthread_t threads[NUM_T];

	for (int i = 0; i < NUM_T; i++)
		pthread_create(&threads[i], NULL, func, NULL);
	for (int i = 0; i < NUM_T; i++)
		pthread_join(threads[i], NULL);

	printf("Final counter value: %d\n", counter);
	return 0;
}

/*
Race Condition
Birden fazla thread aynı anda bir değişkene erişip 
bu değişkeni değiştirmeye çalıştığında ve bu erişimler arasında
 düzgün bir senkronizasyon sağlanmadığında, sonuçlar 
 beklenmedik olabilir. Her bir thread counter değişkenini 
 artırmaya çalışırken, diğer thread'ler de aynı anda bu değişkene erişip
 onu değiştirmeye çalışıyor. Bu, bazı artışların kaybolmasına 
 neden olabilir.
*/