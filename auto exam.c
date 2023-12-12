#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

void cevap_anahtari_uret(char cevap_anahtari[ ], int S);
void cevap_anahtari_yazdir(char cevap_anahtari[ ], int S);
void sinavi_uygula(char ogrenci_cevaplari[ ][100], char cevap_anahtari[ ], int N, int S, double B, double D);
void ogrenci_cevabini_yazdir(char ogrenci_cevaplari[ ][100], int ogrenci_ID, int S);
void ogrencileri_puanla(char ogrenci_cevaplari[ ][100], char cevap_anahtari[ ], double HBN[ ], int N, int S);
double sinif_ortalamasi_hesapla(double HBN[ ], int N);
double standart_sapma_hesapla(double ortalama, double HBN[ ], int N);
void T_skoru_hesapla(double ortalama, double HBN[ ], int N, double std, double T_skoru[ ]);
void harf_notu_hesapla(char harf_notu[ ][10], double T_skoru[ ], double ortalama, int N, char sinif_duzeyi[ ]);
void her_seyi_yazdir(double ortalama, double std, double T_skoru[100], double HBN[100], char harf_notu[ ][10], char sinif_duzeyi[ ], int N);

void cevap_anahtari_uret(char cevap_anahtari[ ], int S){
	srand(time(0));
	char harfler[5] = {'A','B','C','D','E'};
	for(int i=0; i<S; i++)
		cevap_anahtari[i] = harfler[rand()%5];
}

void cevap_anahtari_yazdir(char cevap_anahtari[ ], int S){
	printf("Cevap anahtari:\n");
	for(int i=0; i<S; i++)
			printf("%0.3d:%c | ",i+1, cevap_anahtari[i]);
	printf("\n\n");
}

void sinavi_uygula(char ogrenci_cevaplari[ ][100], char cevap_anahtari[ ], int N, int S, double B, double D){

	srand(time(0));
	char harfler[5] = {'A','B','C','D','E'};
	for(int i=0;i<N;i++){
		printf("%0.3d. ogrencinin cevaplari:\n", i+1);
		for(int j=0;j<S;j++){
			ogrenci_cevaplari[i][j] = (B>rand()%100)? 'X': (D>rand()%100)? cevap_anahtari[j]: harfler[rand()%5];
			// Burada iki kere rastgele sayi uretiyoruz. Birinci uretilen sayi B'den (bos birakma ihtimalinden)
			// kucukse o soru bos birakiliyor ve X oluyor. Diger uretilen sayi da D (dogru cevaplama ihtimali)
			// ile karsilastiriliyor. D buyukse dogru cevabi isaretliyor. Degilse rastgele bir cevabi isaretliyor.
			printf("%0.3d:%c | ", j+1, ogrenci_cevaplari[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void ogrenci_cevabini_yazdir(char ogrenci_cevaplari[ ][100], int ogrenci_ID, int S){
	//ogrenci_ID 0 ~ N-1 arasında değişen bir indis olarak verilmeli
	for(int i=0;i<S;i++)
	printf("%0.3d:%c | ",i+1, ogrenci_cevaplari[ogrenci_ID][i]);
	printf("\n");
}

void ogrencileri_puanla(char ogrenci_cevaplari[ ][100], char cevap_anahtari[ ], double HBN[ ], int N, int S){

	int dogru_sayisi[100] = {0};		// Her ogrenci icin dogru ve yanlis sayisini tutacak olan bir dizi tanimliyoruz ve ilk degerleri 0 atiyoruz.
	int yanlis_sayisi[100] = {0};
	double soru_degeri = 100/S; 		// 1 sorunun kac puan degerinde olacagini hesapliyoruz

	for(int i=0;i<N;i++){
		for(int j=0;j<S;j++){												// Bu 2 dongu her ogrencinin her sorusu icin donuyor.
			if(ogrenci_cevaplari[i][j] == 'X')								// Soru bos ise diger soruya gecmesi icin continue komutu kullanılıyor.
				continue;
			else if(ogrenci_cevaplari[i][j] == cevap_anahtari[j])			// Soru dogru ise dogru_sayisi dizisinde o ogrenciye ait indisteki sayi bir artiyor.
				dogru_sayisi[i]++;
			else															// Soru yanlis ise yanlis_sayisi dizisinde o ogrenciye ait indisteki sayi bir artiyor.
				yanlis_sayisi[i]++;
		}
	}
	for(int i=0;i<N;i++){													// Buradaki dongude de dogru sayisindan yanlis sayisinin ceyregini cikarip
			HBN[i] = (dogru_sayisi[i] - ((double)(yanlis_sayisi[i])/4.0))*soru_degeri;	// bir sorunun puani ile carpip HBN dizisine atiyoruz.
			if(HBN[i]<0){													// Negatif not varsa onu da 0 olarak aliyoruz.
				HBN[i] = 0;
			}
	}
}

double sinif_ortalamasi_hesapla(double HBN[ ], int N){
	double ortalama = 0;
	for(int i=0;i<N;i++){					// Her ogrencinin notunu ogrenci sayisina bolup her seferinde ortalama adli degiskene ekliyor.
		ortalama+= HBN[i]/N;
	}
	return ortalama;
}

double standart_sapma_hesapla(double ortalama, double HBN[ ], int N){
	double std, temp = 0.0;

	for(int i=0;i<N;i++){						// Burada da verilen standart sapma formulu uygulaniyor.
		temp += pow((HBN[i]-ortalama),2);
	}
	std = sqrt(temp/N);
	return std;

}

void T_skoru_hesapla(double ortalama, double HBN[ ], int N, double std, double T_skoru[ ]){

	for(int i=0;i<N;i++){									// Verilen T skoru formulu uygulaniyor.
		T_skoru[i] = ((((HBN[i]-ortalama)/std)*10)+60);
	}
}

void harf_notu_hesapla(char harf_notu[ ][10], double T_skoru[ ], double ortalama, int N, char sinif_duzeyi[ ]){

	int x = 	((ortalama> 80 )	&& 	(ortalama<=100 ))? 0 	:	\
				((ortalama> 70 )  	&& 	(ortalama<= 80 ))? 2 	:	\
				((ortalama>62.5)	&& 	(ortalama<= 70 ))? 4 	:	\
				((ortalama>57.5)	&& 	(ortalama<=62.5))? 6 	:	\
				((ortalama>52.5)	&& 	(ortalama<=57.5))? 8 	:	\
				((ortalama>47.5)	&& 	(ortalama<=52.5))? 10 	:	\
				((ortalama>42.5)	&& 	(ortalama<=47.5))? 12 	:  14;
	/*
	 * Her sınıf düzeyi değişiminde yukarıdan aşağıya doğru T skorları 2’şer olarak arttığı için bu örüntüyü işine gelecek şekilde kullanıyor.
	 * Tüm harf notlarını tek seferde bir düzene sokmak için x adlı değişkene sınıfın ortalamasına bağlı olarak 0-14 arası 2’şer olarak artan bir değer atıyor.
	 * Buradan sonra tabloda verilen T skorları dağılımında ‘Üstün Başarı’ satırı kullanılarak alınacak harf notunun ilk harfi ve ikinci harfi ayrı ayrı atanıyor.
	 * İlk harfin atanmasında örneğin CC ve CB harf notlarının ilk harfleri aynı olduğu için aynı aralıkta kullanıyor.
	 * İkinci harfin atanmasında da aynı şekilde örneğin CB ve BB harf notlarının ikinci harfleri aynı olduğu için aynı aralıkta kullanıyor.
	 * Diğer satırlarda da aynı işlemin sağlanabiliyor olması için de her değere az önce (0-14 arası) tanımlanan x değişkeni ekleniyor.
	 * Örnek olarak sınıf düzeyi ‘İyi’ olduğu durumda x değeri 6 olacaktır ve tüm T skoru değer aralıkları da 6’şar artmış olacaktır.
	 */

	for(int i=0;i<N;i++){

		harf_notu[i][0] = 	(T_skoru[i]<36.99+x)?	'F'	:	\
							((T_skoru[i]>=37+x)	&&	(T_skoru[i]<=46.99+x))?	'D'	:	\
							((T_skoru[i]>=47+x)	&&	(T_skoru[i]<=56.99+x))?	'C'	:	\
							((T_skoru[i]>=57+x)	&&	(T_skoru[i]<=66.99+x))?	'B'	:	'A'	;

		harf_notu[i][1] = 	(T_skoru[i]<32+x)?	'F'	:	\
							((T_skoru[i]>=32+x)	&&	(T_skoru[i]<=41.99+x))?	'D'	:	\
							((T_skoru[i]>=42+x)	&&	(T_skoru[i]<=51.99+x))?	'C'	:	\
							((T_skoru[i]>=52+x)	&&	(T_skoru[i]<=61.99+x))?	'B'	:	'A'	;
	}

	// Az once tanımlanan x değeri üzerinden sinif düzeyini tanımlıyor.

	switch(x){
	case 0:
		strcpy(sinif_duzeyi,"Ustun basari");
		break;
	case 2:
		strcpy(sinif_duzeyi,"Mukemmel");
			break;
	case 4:
		strcpy(sinif_duzeyi,"Cok Iyi");
			break;
	case 6:
		strcpy(sinif_duzeyi,"Iyi");
			break;
	case 8:
		strcpy(sinif_duzeyi,"Ortanin ustu");
			break;
	case 10:
		strcpy(sinif_duzeyi,"Orta");
			break;
	case 12:
		strcpy(sinif_duzeyi,"Zayif");
			break;
	case 14:
		strcpy(sinif_duzeyi,"Kotu");
		break;
	}
}

void her_seyi_yazdir(double ortalama, double std, double T_skoru[100], double HBN[100], char harf_notu[ ][10], char sinif_duzeyi[ ], int N){

	// Diğer fonksiyonlarda üretilen her şeyi yazdırıyor.

	printf("Sinif ortalamasi: %.2lf, standart sapma: %.2lf\nSinif duzeyi: %s\n\n",ortalama, std, sinif_duzeyi);
	printf("Ogrenci notlari:\n");
		for(int i=0;i<N;i++){
			printf("%0.3d. ogrencinin HBN: %.2lf, T-skoru: %.2lf, harf notu: %c%c  \n", i+1, HBN[i], T_skoru[i], harf_notu[i][0], harf_notu[i][1]);
		}
		printf("\n\n");
}
int main(void) {

	double B;
	double D;
	int N;
	int S;
	char cevap_anahtari[100];
	char ogrenci_cevaplari[100][100];
	double HBN[100];
	double ortalama = 0.0;
	double std = 0.0;
	double T_skoru[100];
	char harf_notu[100][10];
	char sinif_duzeyi[30];

	printf("Ogrenci sayisini giriniz (max 100):\n");
	scanf("%d", &N);
	printf("Soru sayisini giriniz (max 100):\n");
	scanf("%d", &S);
	printf("Herhangi bir sorunun boş bırakılma ihtimalini giriniz (0.0 ~ 1.0):\n");
	scanf("%lf", &B);
	printf("Herhangi bir sorunun doğru cevaplanma ihtimalini giriniz (0.0 ~ 1.0):\n");
	scanf("%lf", &D);
	B = 100*B;
	D = 100*D;

	cevap_anahtari_uret(cevap_anahtari, S);
	cevap_anahtari_yazdir(cevap_anahtari, S);
	sinavi_uygula(ogrenci_cevaplari, cevap_anahtari, N, S, B, D);
	ogrencileri_puanla(ogrenci_cevaplari,cevap_anahtari,HBN,N,S);
	ortalama = sinif_ortalamasi_hesapla(HBN, N);
	std = standart_sapma_hesapla(ortalama,HBN,N);
	T_skoru_hesapla(ortalama,HBN,N,std,T_skoru);
	harf_notu_hesapla(harf_notu, T_skoru, ortalama, N, sinif_duzeyi);
	her_seyi_yazdir(ortalama, std, T_skoru, HBN, harf_notu, sinif_duzeyi, N);
//	ogrenci_cevabini_yazdir(ogrenci_cevaplari, 8, S);

	return 0;
}
