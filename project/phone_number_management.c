/* Phone number management program */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 50
#define NOMATCH_FORMAT "No match found \n\n"
#define OUTPUT_FORMAT "Name: %-10sTel: %-10s \n"

/* structs */
typedef struct {
	char name[MAX];
	char pnum[MAX];
} Person;

/* function prototypes */
void print_menu();
void clear_data(Person *data, size_t start, size_t end);
int isempty(Person *data, int index);
int issame(Person *data, char *delname, int index);
void insert(Person *data, size_t datasize);
void del(Person *data, size_t datasize);
void search(Person *data, size_t datasize);
void print_all(Person *data, size_t datasize);

int main(void)
{
	int len_init = 10;
	Person *data = (Person *)malloc(sizeof(Person)*len_init);
	clear_data(data, 0, len_init);
	int input = 0;

	do {
		print_menu();
		fscanf(stdin, "%d", &input);
		getchar();
		
		switch (input) {
		case 1:
			insert(data, _msize(data) / sizeof(Person));
			break;
		case 2:
			del(data, _msize(data) / sizeof(Person));
			break;
		case 3:
			search(data, _msize(data) / sizeof(Person));
			break;
		case 4:
			print_all(data, _msize(data) / sizeof(Person));
			break;
		default:
			printf("\n";
			break;
		}

	} while (input != 5);

	free(data);
	return 0;
}

void print_menu()
{
	printf("***** MENU ***** \n");
	printf("1. Insert \n");
	printf("2. Delete \n");
	printf("3. Search \n");
	printf("4. Print All \n");
	printf("5. Exit \n");
	printf("Choose the item: ");
}

void clear_data(Person *data, size_t start, size_t end)
{
	size_t i;

	for (i = start; i < end; ++i) {
		data[i].name[0] = '\0';
		data[i].pnum[0] = '\0';
	}
}

int isempty(Person *data, int index)
{
	enum {FALSE, TRUE};

	if (strlen(data[index].name) == 0 && strlen(data[index].pnum) == 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

int issame(Person *data, char *delname, int index)
{
	enum {FALSE, TRUE};

	if (strcmp(data[index].name, delname) == 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void insert(Person *data, size_t datasize)
{
	int i;
	enum {FALSE, TRUE};

	for (i = 0; isempty(data, i) == FALSE; ++i) {				// finds an empty place of the least index
		if (i > datasize - 1) {						// allocates additional memory if it is needed
			datasize += 5;
			data = (Person *)realloc(data, sizeof(Person)*datasize);
			clear_data(data, datasize - 5, datasize);
		}
	}							

	printf("\n[INSERT] \n");

	printf("Input Name: ");
	fgets(data[i].name, MAX, stdin);
	data[i].name[strlen(data[i].name) - 1] = '\0';

	printf("Input Tel Number: ");
	fgets(data[i].pnum, MAX, stdin);
	data[i].pnum[strlen(data[i].pnum) - 1] = '\0';

	printf("Data Inserted \n\n");
}

void del(Person *data, size_t datasize)
{
	enum { FALSE, TRUE };
	char delname[MAX];
	int delflag = FALSE;
	int i;

	printf("\n[DELETE] \n");
	printf("Input Name or \"all\": ");
	fgets(delname, MAX, stdin);
	delname[strlen(delname) - 1] = '\0';
	
	if (strcmp(delname, "all") == 0 || strcmp(delname, "All") == 0) {
		clear_data(data, 0, datasize);
		delflag = TRUE;
	}
	else {
		for (i = 0; i < datasize; ++i) {
			if (issame(data, delname, i) == TRUE) {
				data[i].name[0] = '\0';
				data[i].pnum[0] = '\0';
				delflag = TRUE;
			}
		}
	}

	if (delflag == TRUE) {
		printf("Data Deleted \n\n");
	}
	else {
		printf(NOMATCH_FORMAT);
	}
}

void search(Person *data, size_t datasize)
{
	enum { FALSE, TRUE };
	char srchname[MAX];
	int srchflag = FALSE;
	int i;

	printf("\n[SEARCH] \n");
	printf("Input Name: ");
	fgets(srchname, MAX, stdin);
	srchname[strlen(srchname) - 1] = '\0';

	for (i = 0; i < datasize; ++i) {
		if (issame(data, srchname, i) == TRUE) {
			printf(OUTPUT_FORMAT, data[i].name, data[i].pnum);
			srchflag = TRUE;
		}
	}

	if (srchflag == TRUE) {
		printf("Data Searched \n\n");
	}
	else {
		printf(NOMATCH_FORMAT);
	}
}

void print_all(Person *data, size_t datasize)
{
	int i;
	enum {FALSE, TRUE};

	printf("\n[Print All Data] \n");
	for (i = 0; i < datasize; ++i) {
		if (isempty(data, i) == TRUE) {
			continue;
		}

		printf(OUTPUT_FORMAT, data[i].name, data[i].pnum);
	}
	printf("\n");
}
