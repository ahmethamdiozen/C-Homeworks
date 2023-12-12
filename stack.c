
//	AHMET HAMDİ ÖZEN - 20360859060

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char data;
	struct node *next;

}STACK;
STACK* top;

void push(char item)
{
    struct node *ptr = malloc(sizeof(struct node));
    ptr->data = item;
    ptr->next = top;
    top = ptr;
    // printf("%c eklendi\n", item);
}

void pop()
{
    if (top == NULL)
    {
        printf("Stack bos.\n");
    }
    else
    {
        struct node *temp;
        temp = top;
        top = top->next;
        // printf("%c silindi\n", temp->data);
        free(temp);
    }
}

void display()
{
    struct node *temp;
    temp = top;
    while (temp != NULL)
    {
        printf("%c\n", temp->data);
        temp = temp->next;
    }
}

int eslesme(char karakter1, char karakter2){		// parantezler birbirlerini karşılıyor mu diye kontrol ediyor.

	if(karakter1 == '(' && karakter2 == ')')
		return 1;
	if(karakter1 == '{' && karakter2 == '}')
		return 1;
	return 0;
}

int parantez(){

	char parantez[100] = { '(', '(', ')', ')', '{', '}'};		// dogru dizilmis olan.
	//char parantez[100] = { '(', '}', '}', '{', ')', '('};		// yanlis dizilmis olan.
	int i =0;													// dongu degiskenimiz.
	int esitlik = 0;											// eslesme fonksiyonunu atayacağımız degisken.

	while(!(parantez[i] == '\0')){								// dizimiz bitene kadar donuyor.

		if(parantez[i] == '(' || parantez[i] == '{')		// parantez "aç parantez" ise direkt stacke atıyor.
			push(parantez[i]);

		if(parantez[i] == ')' || parantez[i] == '}'){			// parantez "kapa parantez" ise stacki kontrol ediyor.
			 if (top == NULL)									// stack bos ise uyusma yoktur ve 0 dondurur.
				 return 0;
			 else{
				 // stack bos degilse stackte en ustte bulunan karakter ile
				 // dizi karakterini eslesme fonksiyonuna gonderiyor.
				 esitlik = eslesme(top->data, parantez[i]);
				 // eslesme fonksiyonunda '(' ile  ')'  mi yoksa,  '{' ile  '}' mi diye kontrol ediyor.
				 // Bu durum saglanırsa esitlik isimli degiskene 1 saglanmazsa 0 atanıyor.
				 if(esitlik){
					 pop();										// esitlik 1'e esitse pop ediyor.
			 }
			 }
		}
		i++;
	}
	if(top == NULL)			// stackte eleman kalmadıysa parantezler dogru eslesmis demektir. Bu sebepten 1 dondurur.
		return 1;
	else					// Diger durumda 0 dondurur.
		return 0;
}

int main() {

	int k = parantez(); 	// fonkisyon calisiyor ve geri donus degerine baglı olarak yazdırıyor.
	if(k==1)
		printf("Parantezler eşleşiyor");
	else
		printf("Parantezler eşleşmiyor");
	return 0;
}
