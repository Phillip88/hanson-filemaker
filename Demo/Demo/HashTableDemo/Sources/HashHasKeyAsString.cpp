#include <stdio.h>
#include <conio.h>
#include <string.h>

#define MAX 50

struct Entry
{
	char key[30];
	char licenseType[30];
	char fullname[100];
	char address[500];
	char phone[50];
};

typedef struct Entry* License;
License licenseList[MAX];
int listSize;

int h(char *key);
int add(License li);
void search(char *key);
void displayElement(int d);
void showList();
void init();
void initSomeEntry();

void main()
{
	init();
	initSomeEntry();
	showList();
	getch();
}

int h(char *key)
{
    char *c = key;
    int t = 0;
    while (*c!=0)
    {
		t += *c;
        c++;
    }
    return t;
}

int add(License li)
{
    int d = h(li->key);
    if (listSize >= MAX - 1)
       return 0;
    while(licenseList[d] != NULL){
        d = (d+1)%MAX;
    };    
    licenseList[d] = li;
	listSize++;
    return 1;
}

void search(char *key)
{
    int d = h(key), c = 0;
    while (licenseList[d]!=NULL)
    {
      if (!strcmp(licenseList[d]->key, key)){
           //action(d);
           c++;
      }
      d = (d+1) %MAX;        
    }
    printf("So ket qua: %d\n");
}

void displayElement(int d)
{
	//printf("%30s %20s %20s\n", licenseList[d]->key, licenseList[d]->licenseType, licenseList[d]->fullname);
	printf("%30s %20s\n", licenseList[d]->key, licenseList[d]->licenseType);
}

void showList()
{
	printf(" Key                     ||LicenseType                   ||Fulllname\n");
    for (int i=0; i< MAX; i++)
    {
        if (licenseList[i]!=NULL)
           displayElement(i);
    }
}

void init()
{
	listSize = 0;
     for (int i=0; i< MAX; i++)
     {
		 licenseList[i] = NULL;
     }
}

void initSomeEntry()
{
	License li = NULL;
	char *key[4] = {"0XASD-12SS3-4512R-456AW-A2B56",
				    "AB456-21ASD-5ASF2-12DGD-ASDFS",
				    "CD12A-LKHE2-HFR34-23DGD-12SFF",
					"12QWA-AKSH1-23DGR-SDFHF-FDGF2"};

	char *lt[4] = {"Single-User","Single-User",
				   "Multi-User","Multi-User"};
	char *fm[4] = {"Phillip VU","Tommy NGO",
				   "David LIM","Edward YOKOP"};
	char *address[4] = {"Danang", "Danang", "KL", "KL"};
	char *phone[4] = {"1215515155", "2652145555", "6522564566", "98554881211"};

	for (int i=0; i< 4; i++)
	{
		li = new Entry;
		strcpy(li->key, key[i]);
		strcpy(li->licenseType, lt[i]);
		strcpy(li->fullname, fm[i]);
		strcpy(li->address, address[i]);
		strcpy(li->phone, phone[i]);
		add(li);
	}
}