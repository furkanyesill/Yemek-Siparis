#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

typedef struct List{
	char *foodName;
	int foodWeight;
	float foodPrice;
	struct List *next;
}node;

node *start=NULL,*temp=NULL,*last=NULL,*prev=NULL;
FILE *fp;


int addFood(char *name, int weight, float price) {
	node *add = (node*)malloc(sizeof(node));
		add->foodName=name;
		add->foodWeight=weight;
		add->foodPrice=price;
		
	if(start==NULL) {
		start=add;
		last=add;
		last->next=start;
	} 
	else {
		if(last->foodPrice<=price) {
			last->next=add;
			last=add;
			last->next=start;
		} 
		else {
			temp=start;
			if(start->foodPrice>price){
				add->next=start;
				start=add;
				last->next=start;
			}
			else{
				while(1){
					if(temp->next->foodPrice<price && temp->next->next->foodPrice>price){
						temp=temp->next;
						add->next=temp->next;
						temp->next=add;
						break;
					}
					temp=temp->next;
				}
			}
		}	
	}
}


void deleteFood(char *del){
	temp=start;
	while(temp){
		if(temp->foodName==del) break;
		prev=temp;
		temp=temp->next;	
	}
	if(temp!=NULL){
		if(temp==start){
			if(start==last){
				start=NULL;
				last=NULL;	
			}
			else{
				start=start->next;
			}
		}
		else if(temp==last){
			prev->next=start;
			last=prev;
		}
		else{
			prev->next=temp->next;
		}
	}
	free(temp);
	printf("\nsilme islemi gerceklesti.\n");
}


void show(){
	if(start==NULL){
		printf("Liste bos\n");
	}
	else{
		temp=start;
		while(temp->next!=start){
			printf(" %s %d %.2f\n",&temp->foodName,temp->foodWeight,temp->foodPrice);
			temp=temp->next;
		}
			printf(" %s %d %.2f\n",&temp->foodName,temp->foodWeight,temp->foodPrice);
	}
}


int foodSelection(node *temp) {
	if(temp!=NULL){
		char vote;
		printf("\n %s ",&temp->foodName);
		printf("%d ",temp->foodWeight);
		printf("%.2f ",temp->foodPrice);
		printf("(e/h/a)");	scanf("%s",&vote);
	
		switch(vote){
			case 'e':
				printf("\n%s yemeginiz hazirlaniyor Afiyet olsun...\n",&temp->foodName);
				return 0;
		
			case 'h':
				temp=temp->next;
				foodSelection(temp);
				break;
			
			case 'a':
				system("cls");
				return 0;
			
			default:
				printf("hatali giris yaptiniz");
		}
	}
}
    
    
int getText(){
	int weight;
	float price;
	char *name;
	fp=fopen("menu.txt","r");
	fseek(fp,0,SEEK_SET);
	if(fp==NULL) printf("Dosya Hatasi...");
	
		fscanf(fp,"%s %d %f ",&name,&weight,&price);
		addFood(name,weight,price); 
		
	fclose(fp);	
}


int main(){
	int vote,weight;
	char *name=(char*)malloc(sizeof(char));
	float price;
	char *del;
	
	getText();
		
	while(1){
	printf("\n Gerceklestirmek istediginiz islemi seciniz:\n\n");
	printf(" 1-Ekle\n 2-Sil\n 3-Listele\n 4-Yemek Secimi\n 5-Cikis\n\n");
	scanf("%d",&vote);
	
	switch(vote){
		case 1:
			system("cls");
			printf("Eklemek istediginiz yemegin ismi:"); scanf("%s",&name);
			printf("Eklediginiz yemegin gramaji:"); scanf("%d",&weight);
			printf("Eklediginiz yemegin fiyati:"); scanf("%f",&price);
			addFood(name,weight,price);
			system("cls");
			printf("Yemek listeye eklendi.\n");
			break;
			
		case 2:
			printf("Silmek istediginiz yemegin ismi:"); scanf("%s",&del);
			deleteFood(del);
			break;
			
		case 3:
			system("cls");
			show();
			break;
		case 4:
			system("cls");
			printf("yemek secmek icin 'e'\n");
			printf("bir sonraki yemege gecmek icin 'h'\n");
			printf("ana menuye donmek icin 'a' degerini tuslayiniz.\n");
			temp=start;
			foodSelection(temp);
			break;
		
		case 5:
			return 0;	
			
		default:
			printf("hatali giris yaptiniz");
			return 0;
	}
	}
}
