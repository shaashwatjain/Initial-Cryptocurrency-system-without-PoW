#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
//#include "block.c"


typedef struct person{
	char name[100];
	int index;
	float balance;
	struct person* link;
}prsn;

typedef struct node{
	prsn* person1;
	prsn* person2;
	time_t timestamp;	//in seconds from January 1,1970
	float amt;
	char* prevhash;
	char* currhash;
	struct node *link;
}node;

void delay(int sec);
void create_person(prsn* admin);
void transaction_verification(prsn* admin);
void get_details(prsn* admin,int index);
int flag=0;
void add_money(prsn* admin,int index);
void withdraw_money(prsn* admin,int index);
prsn* init();

prsn* admin;

void main()
{
	admin = init();
	int in = 1;
	while(in != 0)
	{
		printf("\n1. Create new account\n2. Transfer money\n3. Account details\n4. Add money\n5. Withdraw Money\n");
		scanf("%d",&in);
		switch(in)
		{
			case 1:
				create_person(admin);
				getch();
				break;
			case 2:
				transaction_verification(admin);
				getch();
				break;
			case 3:
				printf("Please enter your id :");
				int id;
				scanf("%d",&id);
				get_details(admin,id);
				getch();
				break;
			case 4:
				printf("Please enter your id :");
				int id2;
				scanf("%d",&id2);
				add_money(admin,id2);
				getch();
				break;
			case 5:
				printf("Please enter your id :");
				int id3;
				scanf("%d",&id3);
				withdraw_money(admin,id3);
				getch();
			default:break;
		}
	}
}

prsn* init()
{
	prsn* temp;
	temp = (prsn*)malloc(sizeof(prsn));
	temp->link = NULL;
	temp->name[0] = 'a';
	temp->balance = 0.0;
	temp->index = 0;
	return temp;
}

void create_person(prsn* admin)
{
	prsn* newperson;
	newperson = (prsn*)malloc(sizeof(prsn));
	prsn* temp = admin;

	while(temp->link != NULL)
		temp = temp->link;

	printf("Enter your name: ");
	scanf("%s",newperson->name);
	fflush(stdin);
	printf("Enter your balance: ");
	scanf("%f",&newperson->balance);
	newperson->index = temp->index + 1;
	newperson->link = NULL;
	temp->link = newperson;
	printf("Your Account Number is : %d\n Please do not forget it !\n",newperson->index);
}

void transaction_verification(prsn* admin)
{
	printf("Please enter your account number:");
	int index;
	scanf("%d",&index);
	printf("Enter amount to be transferred:");
	float amount;
	scanf("%f",&amount);
	prsn* temp = admin;
	if(index != 0)
	{
		while(temp->link != NULL && temp->index != index)
			temp = temp->link;
		if(temp->index == index)
		{
			if(temp->balance > amount)
			{
				printf("Amount transferrable...\n");
				printf("Enter reciever account number:");
				int index2;
				scanf("%d",&index2);
				prsn* temp2 = admin;
				while(temp2->link != NULL && temp2->index != index2)
					temp2 = temp2->link;
				//printf("%d\n",temp2->index);
				if(index2 == temp2->index)
				{
					printf("Reciever Id Found...\n");
					delay(1000);
					printf("Are you sure you want to send %.2f Rs in %d Id's account? 1/0 :",amount,index2);
					int ans;
					scanf("%d",&ans);
					if(ans)
					{
						printf("Transferring money now...\n");
						delay(1000);
						temp->balance = temp->balance - amount;
						temp2->balance = temp2->balance + amount;
						//add_block(temp,temp2,amount);
						printf("Money transferred\nPress enter to return to main menu...\n");
					}
					else
					{
						printf("Aborting now...\nPress enter to return to main menu...\n");
					}
				}
				else
				{
					printf("Reciever Id not found...\n");
					delay(100);
					printf("Press enter to return to main menu...\n\n");
				}
			}
			else
			{
				printf("You do not have enough balance...\n");
				delay(200);
				printf("Current account balance = %.2f\n",temp->balance);
				printf("Press enter to return to main menu...\n\n");
			}
		}
		else
		{
			printf("account number not found...\n");
			delay(100);
			printf("Please create new account or enter correct id...\n");
			printf("Press enter to return to main menu...\n\n");
		}
	}
	else
	{
		printf("Please enter valid account number..\n");
		delay(100);
		printf("account number 0 not allowed...\n");
		printf("Press enter to return to main menu...\n\n");
	}
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds)
        ;
}

void get_details(prsn* admin,int index)
{
	prsn* temp = admin;
	if(index != 0)
	{
		while(temp->link != NULL && temp->index != index)
			temp = temp->link;
		if(index == temp->index)
		{
			printf("Id found...\n");
			printf("Retrieving details now...\n");
			delay(500);
			printf("Name: %s\nId: %d\nBalance: %.2f\nPress enter to return to main menu...\n",temp->name,temp->index,temp->balance);
		}
		else
		{
			printf("Id not found..\nPlease enter correct Id or make new account...\nPress enter to return to main menu...\n");
		}
	}
	else
	{
		printf("Invalid Id 0...\nPress enter to return to main menu...\n");
	}
}

void add_money(prsn* admin,int index)
{
	prsn* temp = admin;
	if(index != 0)
	{
		while(temp->link != NULL && temp->index != index)
			temp = temp->link;
		if(temp->index == index)
		{
			printf("Id found...\n");
			printf("Enter amount to add :");
			float add_money;
			scanf("%f",&add_money);
			//printf("%f",temp->balance);
			//printf("%f",add_money);
			printf("Adding amount to account now...\n");
			delay(1000);
			temp->balance = temp->balance + add_money;
			printf("New account balance is : %2.2f\nPress enter to return to main menu...\n",temp->balance);
		}
		else
		{
			printf("Id not found..\nPlease enter correct Id or make new account...\nPress enter to return to main menu...\n");
		}
	}
	else
	{
		printf("Invalid Id 0...\nPress enter to return to main menu...\n");
	}
}

void withdraw_money(prsn* admin,int index)
{
	prsn* temp = admin;
	if(index != 0)
	{
		while(temp->link != NULL && temp->index != index)
			temp = temp->link;
		if(temp->index == index)
		{
			printf("Id found...\n");
			printf("Enter amount to withdraw :");
			float add_money;
			scanf("%f",&add_money);
			//printf("%f",temp->balance);
			//printf("%f",add_money);
			printf("Withdrawing amount from account now...\n");
			delay(1000);
			temp->balance = temp->balance - add_money;
			printf("New account balance is : %2.2f\nPress enter to return to main menu...\n",temp->balance);
		}
		else
		{
			printf("Id not found..\nPlease enter correct Id or make new account...\nPress enter to return to main menu...\n");
		}
	}
	else
	{
		printf("Invalid Id 0...\nPress enter to return to main menu...\n");
	}
}
