#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct node{
    char data[20];
    struct node *link;
} NODE;

typedef struct queue{
    NODE *front;
    NODE *rear;
    int count;
} QUEUE;

QUEUE* CreateQueue(){
    QUEUE* q = (QUEUE*)malloc(sizeof(QUEUE));
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
    return q;
}

void Enqueue(QUEUE *q, char* dataIn){
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
    strcpy(newNode->data, dataIn);
    newNode->link = NULL;
    if (q->front == NULL)
        q->front = newNode;
    else
        q->rear->link = newNode;
    q->rear = newNode;
    printf("\nKuyruga eklenen veri: %s", dataIn);
    q->count++;
}
void Dequeue(QUEUE *q, char *dataOut){
    NODE *temp = q->front;
    strcpy(dataOut, q->front->data);
    if (q->count == 1)
        q->rear = NULL;
    q->front = q->front->link;
    q->count--;
    free(temp);
}
int QueueCount(QUEUE *q){
    return q->count;
}
void Display(QUEUE *q){
    NODE *pLoc = q->front; // ilk dugum
    printf("\nIfade suna donustu: ");
    while (pLoc != NULL){
        printf("%s ", pLoc->data);
        pLoc = pLoc->link;
    }
    printf("\n");
}

void DestroyQueue(QUEUE *q){
    NODE *temp;
    while (q->front != NULL){
        temp = q->front;
        q->front = q->front->link;
        free(temp);
    }
    free(q);
}

int calculate(char a, int b, int c){
    switch(a){
    case '+':
    	return b+c;
    	break;
    case '-':
        return b-c;
        break;
    case '*':
       	return b*c;
       	break;
    case '/':
      	return b/c;
       	break;
    default:
    	return -1;
    }
}

void StringToCharArray(char data[],char* dataptr){
    int i=0;
    while(*dataptr!='\0'){
        data[i]=*dataptr;
        dataptr++;
        i++;
    }
    data[i]='\0';
}

int calculateExpression(QUEUE *q){
    char data[20], data1[20],data2[20],temp_opr, temp_op1, temp_op2, *dataptr;
    int operand1, operand2, value;
    while ((QueueCount(q)!=1))    {
        Dequeue(q, data);
        temp_opr=data[0];
   if(ispunct(temp_opr)){								// eğer temp_opr +, - , * veya / ise
    dataptr=q->front->data;								//data pointer kuyruktaki 2. elemanı işaret ediyor.
    temp_op1=*dataptr;
    StringToCharArray(data1,dataptr);					// dataptr ile işaret edilen stringi char dizisine atıyor.

    dataptr=q->front->link->data;
    temp_op2=*dataptr;									//data pointer bu seferde de kuyruktaki 3. elemanı işaret ediyor.
    StringToCharArray(data2,dataptr);					// dataptr ile işaret edilen stringi char dizisine çeviriyor.
     if(!ispunct(temp_op1)&&!ispunct(temp_op2)){		// ispunct fonksiyonu verilen parametre *,+,- veya / ise 1 aksi takdirde 0 dondurur.

                operand1= atoi(data1);
                operand2= atoi(data2);
                Dequeue(q, data1);
                Dequeue(q, data2);
                value=calculate(temp_opr,operand1, operand2);
                printf ("\nHesaplamadan sonra: %d %c %d = %d\n",operand1,temp_opr,operand2,value);
                // itoa (value, data, 10);
                sprintf(data,"%d",value);
                dataptr=data;
                   Enqueue(q, dataptr);
                Display(q);
            }
            else{
                dataptr=data;
                Enqueue(q, dataptr);
                Display(q);
            }
        }
        else{
            dataptr=data;
            Enqueue(q, dataptr);
            Display(q);
        }
    }
    Dequeue(q, data);
    return atoi(data);
}

int main(){
    char expr[100] = "- + * 9 + 2 8 * + 4 8 6 3";
    char *sembol;
    int finalvalue;
    QUEUE *q = CreateQueue();
    sembol = expr;
    while ((sembol = strtok(sembol, " "))){
        Enqueue(q, sembol);
        sembol = NULL;
    }
    finalvalue=calculateExpression(q);
    printf("\n\nVerilen ifadenin son degeri %d", finalvalue);
    DestroyQueue(q);
}
