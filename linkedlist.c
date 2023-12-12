 
// AHMET HAMDİ ÖZEN
// 20360859060

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{

	unsigned long long int number;
	int grade;
	void *name;
	void *bolum;
	struct node *prev;
	struct node *next;
}NODE;

NODE* head = NULL;
NODE* rear = NULL;

void createNode(long long int number, int grade, void *name, void *bolum){

	NODE* newNode;
	newNode = (NODE*)malloc(sizeof(NODE));
	if(newNode){
	newNode->number = number;
	newNode->grade = grade;
	newNode->name = name;
	newNode->bolum = bolum;
	newNode->prev = NULL;
	newNode->next = NULL;

	head = newNode;
	rear = newNode;
	}
	else
		printf("Yeterli hafiza yok");
}

void addNodeFirst(long long int number, int grade, void *name, void *bolum){ // ilk elemana ekleme.

	NODE* newNode;
	newNode = (NODE*)(malloc(sizeof(NODE)));
	if(newNode){
	newNode->number = number;
	newNode->grade = grade;
	newNode->name = name;
	newNode->bolum = bolum;
	newNode->prev = NULL;
	if(head==NULL){ 		// liste boş ise
		newNode->next = NULL;
		rear = newNode;
	}
	else{					// dolu ise
		newNode->next = head;
		head->prev = newNode;
	}
	head = newNode;
	}
}

void addNodeLast(long long int number, int grade, void *name, void *bolum){ // Son elemana ekleme.

	NODE* newNode;
	newNode = (NODE*)(malloc(sizeof(NODE)));
	newNode->number = number;
	newNode->grade = grade;
	newNode->name = name;
	newNode->bolum = bolum;
	rear->next = newNode;
	newNode->prev = rear;
	rear = newNode;
}

void deleteNode(unsigned long long int deger){
	NODE* pos = head;

	while(pos->number!=deger){
		if(pos->next==NULL){
			printf("eleman bulunamadi\n");
		}
			pos = pos->next;
	}
	if(pos->number == deger){
		if(head->number==deger){	// ilk elemani silme
			head = head->next;
			head->prev = NULL;
			free(pos);
			printf("eleman basariyla silindi\n");
		}
		else if(rear->number == deger){	// son elemani silme
			rear = rear->prev;
			rear->next = NULL;
			free(pos);
			printf("eleman basariyla silindi\n");
		}
		else {						// diger elemanlari silme
			pos->next->prev = pos->prev;
			pos->prev->next = pos->next;
			free(pos);
			printf("eleman basariyla silindi\n");
		}
	}
}

void searchNode(unsigned long long int deger){					// girilen degeri ilk bastan baslayarak arıyor.
	NODE* pos = head;
	int sira=0;

	if(pos == NULL){						// listenin ilk elemani bos ise bos liste yazdiriyor.
		printf("bos liste\n");
	}
	while(pos->number!=deger){
		if(pos->next==NULL){				// bulundugu pozisyonun bir sonraki elamani gosteren pointeri NULL ise
			printf("eleman bulunamadi\n");	// listenin sonuna kadar gelmis ve girilen degeri bulamamis demek oluyor.
		}
		pos = pos->next;					// her bulamadiginda hem pozisyonu bir ilerletiyor hem de pozisyonun
		sira++;								// sayisal degerini bir arttiriyor.
	}
	if(pos->number == deger){				// eger bulduysa da buldugu sirayı yazdiriyor.
	printf("girilen deger %d. indiste bulundu.\n", sira);
	printf("[ %lld numarali %s - %d. sinif ogrencisi %s'tir]\n", pos->number, (char*)&pos->bolum, pos->grade, (char*)&pos->name);
	}
}

void display(){
	NODE* pos;
	pos = head;

	if(pos == NULL){						// listenin ilk elemanı bos ise bos liste yazdiriyor.
		printf("bos liste");
	}
	else{									// bos degilse listeyi sirasiyla yazdiriyor.
		while(pos!=NULL){
			printf("[ %lld numarali %s - %d. sinif ogrencisi %s'tir]\n\n\n", pos->number, (char*)&pos->bolum, pos->grade, (char*)&pos->name);
		pos = pos->next;
	}
	}
}

void destroy(){

	NODE* pos = head;
	while(pos!=NULL){
	pos = head;
	head = head->next;
	free(pos);
	}
	free(rear);
	free(head);
	if(pos==NULL){
		printf("liste silinmistir.");
	}
	display();
}

int main(void) {

	unsigned long long int numara;
	int secenek, sinif;
	void* isim;
	void* bolum;
	do{
	printf("...Hangi islemi yapmak istersiniz?...\n");
	printf("1. Yeni bir liste uretme\n");
	printf("2. Listenin basina eleman ekleme\n");
	printf("3. Listenin sonuna eleman ekleme\n");
	printf("4. Girdiginiz degere sahip elemani silme\n");
	printf("5. Girdiginiz degeri listede arama\n");
	printf("6. Listeyi yazdirma\n");
	printf("7. Listeyi silme\n");
	printf("8. Cikis\n");

	scanf("%d", &secenek);

	switch (secenek){
		case 1:
			printf("Eklemek istediginiz kisinin numarasi nedir? OR: 20360859060 \n");
			scanf("%lld",&numara);
			printf("Eklemek istediginiz kisinin sinifi nedir? OR: 2 \n");
			scanf("%d",&sinif);
			printf("Eklemek istediginiz kisinin ismi nedir? OR: AHMET_HAMDI_OZEN \n");
			scanf("%s", (char*)(&isim));
			printf("Eklemek istediginiz kisinin bolumu nedir? OR: BILGISAYAR_MUHENDISLIGI \n");
			scanf("%s", (char*)&bolum);
			createNode(numara, sinif, isim, bolum);
			break;
		case 2:
			printf("Eklemek istediginiz kisinin numarasi nedir? OR: 20360859060 \n");
			scanf("%lld",&numara);
			printf("Eklemek istediginiz kisinin sinifi nedir? OR: 2 \n");
			scanf("%d", &sinif);
			printf("Eklemek istediginiz kisinin ismi nedir? OR: AHMET_HAMDI_OZEN \n");
			scanf("%s", (char*)&isim);
			printf("Eklemek istediginiz kisinin bolumu nedir? OR: BILGISAYAR_MUHENDISLIGI \n");
			scanf("%s", (char*)&bolum);
			addNodeFirst(numara, sinif, isim, bolum);
			break;
		case 3:
			printf("Eklemek istediginiz kisinin numarasi nedir? OR: 20360859060 \n");
			scanf("%lld",&numara);
			printf("Eklemek istediginiz kisinin sinifi nedir? OR: 2 \n");
			scanf("%d",&sinif);
			printf("Eklemek istediginiz kisinin ismi nedir? OR: AHMET_HAMDI_OZEN \n");
			scanf("%s", (char*)&isim);
			printf("Eklemek istediginiz kisinin bolumu nedir? OR: BILGISAYAR_MUHENDISLIGI \n");
			scanf("%s", (char*)&bolum);
			addNodeLast(numara, sinif, isim, bolum);
			break;
		case 4:
			printf("Hangi eleman degerini silmek istiyorsunuz?\n");
			scanf("%lld",&numara);
			deleteNode(numara);
			break;
		case 5:
			printf("Hangi elemani aramak istiyorsunuz?\n");
			scanf("%lld", &numara);
			searchNode(numara);
			break;
		case 6:
			display();
			break;
		case 7:
			destroy();
			break;
		case 8:
			return 0;
		default:
			printf("Gecerli bir sayi giriniz");
		}
	}while(secenek!=8);
	return 0;
}
