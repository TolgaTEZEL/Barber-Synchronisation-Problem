#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h> 
#include <time.h>



struct Koltuk{ // projede verilen koltuk isimli struct tanımlandı.
int thread_no;
int dolumu;
}koltukDizisi[4]; // koltuklar için istenilen şekilde global array tanımlandı.

int i ; // for döngü değişkeni

pthread_mutex_t anakoltuk; // traş olan kişinin oturacağı koltuk
sem_t lock; // berber salonu için , değişken isimlerinde kafa karısıklığı olmasın diye sizin prog39 de kullandığınız sem_t değişken ismini kullandım hocam. 

void *musterimetod(int name) // müşterilerin gelip dükkana ( semafor ) gireceği metod.
{


	
	sem_wait(&lock); // Semaforun değerini 1 azaltmak için kullanılır.Eğer zaten semafor değeri 1den büyükse direk azaltır ve fonk geri döner. Eğer semafor 0 a eşitse sem_wait fonksiyonu semafor değerinin 1 artmasını bekler artış olduğunda hemen 0 a çeker ve fonk geri döner.
	
      	 

for(int i=1;i<4;i++){ // koltuklara thread nolarını ekleyip doluluk durumlarını 1 ( evet dolu ) yapıyoruz . 1 den başladık cünkü 0. koltuk traş koltuğu
	
           if(koltukDizisi[i].dolumu==0){
		
                koltukDizisi[i].dolumu=1;
                koltukDizisi[i].thread_no=name;

                break;
	
           }

	 }
       
	trasMetod(name);  // traş olma işleminin gerçekleşeceği fonksiyona gönderiyoruz threadi
        
        sem_post(&lock); // Semaforun değerini 1 artırmak için kullanılır. Eğer zaten 0sa ilgili thread uyandırılır. 
	
     
    	
    return NULL;
	
	
}
void trasMetod(int name){ // bu metod threadi koltuğa oturtup kitler ve traş işlemini başlatır.
	
	
	pthread_mutex_lock(&anakoltuk); // traş işlemini gerçekleştirmek için muteximizi kitledik. Yani kritik bölgeye girmeden önce objemizi kitledik. 

	for(int i=1;i<4;i++){ // bu for döngüsü ile güncelleme işlemi yapıyoruz. 
           if(koltukDizisi[i].thread_no==name){ // traş olan threadin koltuğunu boşaltıyoruz.
                koltukDizisi[i].dolumu=0;
                koltukDizisi[i].thread_no=-1;
                break;
           }

        }
koltukDizisi[0].dolumu=1; // daha sonra threadi traş koltuğuna oturtuyoruz.
koltukDizisi[0].thread_no=name;
	// Time_t veri türü, sistem saati değerlerini depolamak için tanımlanan ISO C kitaplığında yer alan bir veri türüdür.
	time_t raw_time; // yine saat için kullandım library metodları
	struct tm *ptr_ts;// temel fonksiyonları kullanıldı. time() kullanılarak saat değerleri döndürülür.

	time ( &raw_time );
	ptr_ts = gmtime ( &raw_time );
	
	printf("Thread T%d <> %2d:%02d:%02d  Traş Koltuğunda traş oluyor. \n ",name , ptr_ts->tm_hour, ptr_ts->tm_min, ptr_ts->tm_sec);
	
	yazdir();
	printf("\n");

	
	sleep(5); // traş süresi  20 dk uzun bir süre olduğu 5 sn olarak ayarladım
	time_t raw_time1;// sistem saatini hesaplamak için time kütüphanesinin
	struct tm *ptr_ts1;

	time ( &raw_time1 );
	ptr_ts1 = gmtime ( &raw_time1 );
	
	
	printf("Thread T%d nin traşı bitti <> %2d:%02d:%02d  \n",name, ptr_ts1->tm_hour, ptr_ts1->tm_min, ptr_ts1->tm_sec); // buraya da ilave ettim aynı traş süresini


	
	sleep(name); // adı kadar uyuyor
for(int i=1;i<4;i++){ // bu for döngüsü ile güncelleme işlemi yapıyoruz. 
           if(koltukDizisi[i].thread_no==name){ // traş olan threadin koltuğunu boşaltıyoruz.
                koltukDizisi[i].dolumu=0;
                koltukDizisi[i].thread_no=-1;
                break;
           }

        }
koltukDizisi[0].dolumu=1; // daha sonra threadi traş koltuğuna oturtuyoruz.
koltukDizisi[0].thread_no=name;
		
yazdir();
printf("\n");



	pthread_mutex_unlock(&anakoltuk);  // mutex serbest bırakıldı.
	
	

	for(int i=1;i<4;i++){
           if(koltukDizisi[i].thread_no==name){
                koltukDizisi[i].dolumu=0;
                koltukDizisi[i].thread_no=-1;
                break;
           }

        }
koltukDizisi[0].dolumu=1;
koltukDizisi[0].thread_no=name;
}



void yazdir(){ // yazdırma işlemi için yarattıgım metod. For döngüsüyle tek tek diziyi gezer.
int b;

for(b=0;b<4;b++){ 
	if(koltukDizisi[b].thread_no ==-1){ // aradaki if elseler sadece görüntü için.
		if(b<3){ 
			printf("K%d[bos] | ",b);
		}
		else{
			printf("K%d[bos] ",b); // son elemana gelince | koymasın diye böyle bir sınırlama getirdim.
			}
	}
	else{ // koltuk boş değilse alt taraftan devam edicek


 	if(b<3){
	printf("K%d[T%d] | ",b,koltukDizisi[b]);
	}
	else{
	printf("K%d[T%d]  ",b,koltukDizisi[b]);
	}

		}
	}
	
printf("\n"); // bir satır boşluk bıraktık.

}


int main(int argc, char **argv)
{
 
for(int i=0;i<4;i++){ // ilk başta tüm koltuklara -1 vererek boş konuma getirdik
                koltukDizisi[i].dolumu=0;
                koltukDizisi[i].thread_no=-1;

        }

  int musterisayi=10;
 
  pthread_t tids[musterisayi];
  void * status;


   if (sem_init(&lock, 0, 4) != 0)  // ilgili semaforun ilklendirilmesi işlemlerini gerçekleştirir . eğer hata olursa semafor init hatası olarak return olur .
    {
        printf("\n semafor init hatasi\n");
        return 1;
    }


  for (int var = 0; var < musterisayi; ++var) { // thread yaratmak ve fonksiyonumuza göndermek için kullandığımız yapı . Aynı yapı prog 37'de de mevcuttur.
	
       pthread_create(tids+var, NULL, musterimetod, var);
	
 	   
  }
 

for (int var = 0; var < musterisayi; ++var) {
     pthread_join(tids[var], &status);
  }

sem_destroy(&lock); // işlemler bittiğinde semaforun sonlandırılmasını sağlar.
exit(0);
return 0;
}
