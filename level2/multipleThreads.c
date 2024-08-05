/*
Birden Fazla Thread Oluşturma:

Birden fazla thread oluştur ve her birinin farklı bir mesaj yazdırmasını sağla.
Thread’lerin birbirine karışmadan düzgün çalışmasını sağla.
*/

#include <pthread.h>
#include <stdio.h>

void *func(void *arg)
{
	char* message = (char *)arg;
	printf("%s\n", message);
	return NULL;
}

int main()
{
	pthread_t t1, t2;
	char *message1 = "i'm thread 1";
	char *message2 = "i'm thread 2";

	pthread_create(&t1, NULL, func, (void *)message1);
	pthread_create(&t2, NULL, func, (void *)message2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}