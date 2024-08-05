/*
Seviye 1: Temel Thread Kullanımı
Basit Thread Oluşturma ve Çalıştırma:

Bir thread oluştur ve basit bir fonksiyon çalıştır (örneğin, "Hello, World!" yazdıran bir fonksiyon).
Thread’in başarılı bir şekilde çalışıp çalışmadığını kontrol et.
*/

#include <pthread.h>
#include <stdio.h>

void *func(void * arg)
{
	printf("Hello World");
	return NULL;
}


int main()
{
	pthread_t th;
	/*
	Linux'ta pthread_t genellikle bir unsigned long int 
	veya bir pointer türü olarak tanımlanabilirken, 
	diğer sistemlerde farklı olabilir. Bu türün tam tanımı, 
	POSIX standardının thread'leri temsil etmek için uygun gördüğü 
	bir veri yapısıdır.
	*/

	pthread_create(&th, NULL, func, NULL);

	pthread_join(th, NULL);
	return 0;
}