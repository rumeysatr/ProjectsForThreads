/*
Üretici thread bir buffer’a veri eklerken, tüketici thread buffer’dan veri çeker.
Buffer’ın senkronizasyonu için mutex kullanılır.
Örneğin, üretici bir diziyi doldururken tüketici bu diziden eleman alır ve ekrana yazdırır.
*/

/*
Üretici-Tüketici problemi, aynı anda çalışan bir üretici ve bir tüketicinin ortak bir buffer üzerinde
çalıştığı klasik bir senkronizasyon problemidir. Üretici buffer'a veri eklerken, tüketici buffer'dan veri çeker.
Buffer dolu olduğunda üretici bekler, boş olduğunda tüketici bekler. 
Bu senkronizasyonu sağlamak için mutex ve koşul değişkenleri kullanılır.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10 // belirlediğim ? buffer boyutu

int buffer[BUFFER_SIZE]; // buffer dizisi
int count = 0;  // buffer'daki eleman sayısı

pthread_mutex_t mutex;
pthread_cond_t full; //buffer dolu koşul değişkeni
pthread_cond_t empty; // buffer boş koşul değişkeni


void* producer(void *arg)
{
    int item;
    while (1)
    {
        item = rand() % 100; // üretilecek veri (0-99 arasından rastgele bir sayı)
        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE)
        {
            pthread_cond_wait(&full, &mutex);  // buffer doluysa bekle
        }

        //buffer'a veri ekle
        buffer[count] = item;
        count++;
        printf("Produced: %d\n", item);

        pthread_cond_signal(&empty); // buffer boş değil koşulunu sinyal ver
        pthread_mutex_unlock(&mutex);

        sleep(1); // üretim hızını yavaşlatmak için beklenir
    }
}

void* consumer (void *arg)
{
    int item;
    while (1)
    {
        pthread_mutex_lock(&mutex);    //mutex kilitleniyor

        while (count == 0)
        { // buffer boşsa bekle
            pthread_cond_wait(&empty, &mutex);
        }

        //buffer'dan veri al
        item = buffer[count - 1];
        count--;
        printf("Consumed: %d\n", item);

        pthread_cond_signal(&full); // buffer dolu değil koşulunu sinyal ver
        pthread_mutex_unlock(&mutex);

        sleep(1); // tüketim hızını yavaşlatmak için beklenir
    }

}


int main()
{
    pthread_t prod_t, cons_t;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL); // koşul değişkenini başlatıyoruz
    pthread_cond_init(&empty, NULL);    //koşul değişkenini başlatıyoruz

    pthread_create(&prod_t, NULL, producer, NULL); //üretici threadi oluşturuyoruz
    pthread_create(&cons_t, NULL, consumer, NULL); // tüketici threadi oluşturulur

    pthread_join(prod_t, NULL);
    pthread_join(cons_t, NULL);

    pthread_mutex_destroy(&mutex); // mutex yok edilir
    pthread_cond_destroy(&full);    //koşul değişkeni yok edilir
    pthread_cond_destroy(&empty); // koşul değişkeni yok edilir

    return 0;
}
