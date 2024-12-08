#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
int ALERTS;
int ALERTS_VALUE=5;

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void getConsoleCenter(int* centerX, int* centerY) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	*centerX = width / 2;
	*centerY = height / 2;
}

void alertsettings() {
	system("cls");
	printf("ENTER THE MINIMUM STOCK QUANTITY: ");
	scanf("%d",&ALERTS_VALUE);
	if(ALERTS_VALUE < 0) {
		ALERTS_VALUE = 5;
		system("cls");
		system("color 04");
		printf("UNSUCCESSFUL TO UPDATE SETTINGS '^'\n\n");
		system("pause");
		return;
	}
	getchar();
	system("cls");
	system("color 0a");
	printf("SETTINGS UPDATED SUCCESSFULLY :)\n\n");
	system("pause");

}
void createFile() {
	FILE *f = fopen("PROJECT.bin","ab");
	if(f==NULL) {
		printf("ERROR: FILE NOT FOUND!");
		return;
	}
	fclose(f);
}
int authenticate() {
	int u,v;
	getConsoleCenter(&u,&v);
	v = 2*v/3;
	system("cls && color 0b");
	char user[20],pass[20];
				gotoxy(u-10,v);
				printf("__________________________________");
				gotoxy(u-10,v+1);
				gotoxy(u-10,v+2);
				printf("-----------LOGIN MENU-------------");
				gotoxy(u-10,v+3);
				printf("__________________________________");
	gotoxy(u-10,v+6);
	printf("ENTER USERNAME:  ");
	fgets(user,20,stdin);
	if(user[strlen(user) - 1] == '\n') {
		user[strlen(user)-1] = '\0';
	}
	fflush(stdin);
	gotoxy(u-10,v+8);
	printf("ENTER PASSWORD:  ");
	fgets(pass,20,stdin);
	if(pass[strlen(pass)-1] == '\n') {
		pass[strlen(pass)-1] = '\0';
	}
	fflush(stdin);
	if(pass[0] != '\0' && user[0] != '\0') {
		if(!strcmp(user,"admin") && !strcmp(pass,"pass")) {
			createFile();
			system("cls");
			system("color 0A");
			printf("\nSUCCESSFUL :) ACCESS GRANTED...\n\n");
			system("pause");
			system("cls");
			gotoxy(u-10,v+2);
			printf("PLEASE WAIT ;)");
			gotoxy(u-10,v);
			printf("LOADING");
			Sleep(700);
			Beep(700,200);
			for(int i=0;i<3;i++){	
			printf(".");	
			Sleep(700);
			Beep(700,200);
			}
			
			
			return 1;
		} else {
			system("color 04 && cls");
			printf("ACCESS DENIED...\n\n");
			system("pause");
			system("color 0F");
			return 0;
		}
		return 0;
	}
	return 0;

}
void printStatusupdate(int found,int status) {
	if (found==1 && status == 1) {
		remove("PROJECT.bin");
		rename("TEMP.bin", "PROJECT.bin");
		system("cls");
		system("COLOR 0A");
		printf("\nPRODUCT SUCCESSFULLY UPDATED :) IN INVENTORY!\n\n");
	} else {
		remove("TEMP.bin");
		if (status == 0) {
			system("cls");
			printf("PRODUCT NOT FOUND IN INVENTORY ('^') !\n\n");
			system("color 04");
		}
	}
	system("pause");
	system("color 0e");
}
void printHeaderupdate() {
	system("cls");
	printf("______________________________________________________________________________\n\n");
	printf("--------------------------UPDATE PRODUCT--------------------------------------\n");
	printf("______________________________________________________________________________\n");
}
void printHeadersearch() {
	system("cls");
	printf("______________________________________________________________________________\n\n");
	printf("--------------------------SEARCHING PRODUCTS----------------------------------\n");
	printf("______________________________________________________________________________\n");
}
void printStatussearch() {
	printf("______________________________________________________________________________\n\n");
	printf("%-25s %-15s %-10s %-15s %-10s\n", "PRODUCT NAME", "PRODUCT CODE", "QUANTITY", "CATEGORY", "PRICE");
	printf("______________________________________________________________________________\n\n");
	printf("---------------------------NO RECORD IN INVENTORY-----------------------------\n");
	printf("______________________________________________________________________________\n\n");
}

// Define the product structure
typedef struct product {
	int code;
	char product_name[30];
	int quantity;
	double price=0;
	char category[20];
} product;
// Function to create a product
product create() {
	product p;
	printf("\nENTER NAME OF PRODUCT:  ");
	fgets(p.product_name, 30, stdin);
	fflush(stdin);
	if (p.product_name[strlen(p.product_name) - 1] == '\n') {
		p.product_name[strlen(p.product_name) - 1] = '\0';
	}
	strcpy(p.product_name, strupr(p.product_name));

	printf("\nENTER CATEGORY OF PRODUCT:  ");
	fgets(p.category, 20, stdin);
	fflush(stdin);
	if (p.category[strlen(p.category) - 1] == '\n') {
		p.category[strlen(p.category) - 1] = '\0';
	}
	strcpy(p.category, strupr(p.category));

	printf("\nENTER ID OF PRODUCT:  ");
	scanf("%d", &p.code);
	getchar();

	printf("\nENTER QTY OF PRODUCT:  ");
	scanf("%d", &p.quantity);
	getchar();

	printf("\nENTER PRICE OF PRODUCT:  ");
	scanf("%lf", &p.price);
	getchar();
	return p;
}
// Function to count the number of records
int noOFrecords() {
	FILE *fptr = fopen("PROJECT.bin", "rb");
	if(fptr == NULL) {
		printf("ERROR: File Opening...");
		return 0;
	}
	fseek(fptr, 0, SEEK_END);
	long size = ftell(fptr) / sizeof(product);
	fclose(fptr);
	return size;
}
// Function to add a product
void add() {
	int toAdd = 1;
	system("cls");
	printf("\n_____________________________________________________________\n");
	printf("\n---------------------ADDING RECORD---------------------------");
	printf("\n_____________________________________________________________\n\n");
	FILE *fptr = fopen("PROJECT.bin", "ab+");
	if (fptr == NULL) {
		printf("ERROR:FILE NOT FOUND!\n");
		system("pause");
		return;
	}
	product P = create();
	product C;
	if (P.category[0] != '\0' && P.product_name[0] != '\0' && P.price > 0 && P.code >= 0 && P.quantity >= 0) {

		while(fread(&C, sizeof(product), 1, fptr)) {
			if (C.code == P.code) {
				system("cls");
				printf("PRODUCT ALREADY EXIST!\n\n");
				fclose(fptr);
				system("pause");
				return;
			}
		}

	} else {
		system("cls");
		toAdd = 0;
		system("color 04");
		printf("INVALID INPUT.... '^' \n\n");
		system("pause");
		system("color 0e");
	}
	fclose(fptr);
	if (toAdd == 1) {
		FILE *fptr2 = fopen("PROJECT.bin", "ab");
		fwrite(&P, sizeof(P), 1, fptr2);
		system("cls");
		system("color 0a");
		printf("PRODUCT ADDED SUCCESSFULLY :) !\n\n");
		system("pause");
		system("color 0e");
		fclose(fptr2);
	}

}
// Function to clear inventory
void clear() {
	system("cls");
	char choice;
	printf("DO YOU WANT TO CLEAR THE INVENTORY? (Y/N):  ");
	scanf("%c", &choice);
	getchar();
	if (choice == 'Y' || choice == 'y') {
		if(!authenticate()) {
			return;
		}
		system("cls");
		FILE *fptr = fopen("PROJECT.bin", "wb");
		if (fptr == NULL) {
			printf("ERROR\n");
			return;
		}
		printf("\nINVENTORY CLEARED.....\n\n");
		system("pause");
		fclose(fptr);
		return;
	}
	printf("\nINVENTORY CLEARED CANCELLED.....\n\n");
	system("pause");
}
// Function to display all products
void displayAll() {
	system("cls");
	FILE *fptr = fopen("PROJECT.bin", "rb");
	int n = noOFrecords();
	printf("_______________________________________________________________________________\n\n");
	printf("--------------------------------ALL PRODUCTS-----------------------------------\n");
	if (n == 0) {
		system("cls");
		printStatussearch();
		system("pause");
		fclose(fptr);
		return;
	}
	product data;
	printf("\n_______________________________________________________________________________\n");
	printf("\n%-25s %-15s %-10s %-15s %-10s\n", "PRODUCT NAME", "PRODUCT CODE", "QUANTITY", "CATEGORY", "PRICE");
	printf("_______________________________________________________________________________\n\n");
	for (int i = 0; i < n; i++) {
		fread(&data, sizeof(product), 1, fptr);
		printf("%-25s %-15d %-10d %-15s %-10.2lf\n\n",
		       data.product_name, data.code, data.quantity,data.category,data.price);
	}
	printf("_______________________________________________________________________________\n\n");
	fclose(fptr);
	system("pause");
}
// Function to search for a product by code
void searchbycode() {
	int found = 0;
	printHeadersearch();
	FILE *fptr = fopen("PROJECT.bin", "rb");
	if (fptr == NULL) {
		printf("ERROR: FILE NOT FOUND\n");
		system("pause");
		return;
	}

	int n = noOFrecords();
	if (n == 0) {
		printStatussearch();
		fclose(fptr);
		system("pause");
		return;
	}

	int code;
	printf("\nENTER THE CODE FOR PRODUCT:  ");
	scanf("%d", &code);
	getchar();
	printf("\n");

	if (code < 0) {
		system("cls");
		printf("INVALID CODE....\n");
		system("pause");
		fclose(fptr);
		return;
	}

	product data;
	printf("______________________________________________________________________________\n\n");
	printf("%-25s %-15s %-10s %-15s %-10s\n", "PRODUCT NAME", "PRODUCT CODE", "QUANTITY", "CATEGORY", "PRICE");
	printf("______________________________________________________________________________\n\n");
	for (int i = 0; i < n; i++) {
		fread(&data, sizeof(product), 1, fptr);
		if (data.code == code) {
			printf("%-25s %-15d %-10d %-15s %-10.2lf\n\n",
			       data.product_name, data.code, data.quantity, data.category, data.price);
			found = 1;
		}
	}

	if (found == 0) {
		printf("--------------------------NO PRODUCT FOUND------------------------------------\n");
	}
	printf("______________________________________________________________________________\n\n");
	fclose(fptr);
	system("pause");
}
//search by product price
void searchbyprice() {

	int found = 0;
	printHeadersearch();
	FILE *fptr = fopen("PROJECT.bin", "rb");
	if (fptr == NULL) {
		printf("ERROR: FILE NOT FOUND\n");
		system("pause");
		return;
	}

	int n = noOFrecords();
	if (n == 0) {
		printStatussearch();
		fclose(fptr);
		system("pause");
		return;
	}

	double price;
	printf("\nENTER THE PRICE FOR PRODUCTS IN RANGE :  ");
	scanf("%lf", &price);
	getchar();
	printf("\n");

	if (price < 0) {
		system("cls");
		printf("INVALID PRICE!!!\n");
		system("pause");
		fclose(fptr);
		return;
	}

	product data;
	printf("______________________________________________________________________________\n\n");
	printf("%-25s %-15s %-10s %-15s %-10s\n", "PRODUCT NAME", "PRODUCT CODE", "QUANTITY", "CATEGORY", "PRICE");
	printf("______________________________________________________________________________\n\n");
	for (int i = 0; i < n; i++) {
		fread(&data, sizeof(product), 1, fptr);
		if (data.price <= price) {
			printf("%-25s %-15d %-10d %-15s %-10.2lf\n\n",
			       data.product_name, data.code, data.quantity, data.category, data.price);
			found = 1;
		}
	}

	if (found == 0) {
		printf("--------------------------NO PRODUCT FOUND------------------------------------\n");
	}
	printf("______________________________________________________________________________\n\n");
	fclose(fptr);
	system("pause");
}
//search by product name
void searchbyname() {
	int found = 0;
	printHeadersearch();
	FILE *fptr = fopen("PROJECT.bin", "rb");
	if (fptr == NULL) {
		printf("ERROR: FILE NOT FOUND\n");
		system("pause");
		return;
	}

	int n = noOFrecords();
	if (n == 0) {
		printStatussearch();
		fclose(fptr);
		system("pause");
		return;
	}

	char name[30];
	printf("\nENTER THE NAME FOR PRODUCT:  ");
	fgets(name,30,stdin);
	fflush(stdin);
	if (name[strlen(name) - 1] == '\n') {
		name[strlen(name) - 1] = '\0';
	}
	strcpy(name, strupr(name));
	printf("\n");

	if(name[0] == '\0') {
		system("cls");
		printf("INVALID INPUT....\n\n");
		system("pause");
		fclose(fptr);
		return;
	}

	product data;
	printf("______________________________________________________________________________\n");
	printf("\n%-25s %-15s %-10s %-15s %-10s\n", "PRODUCT NAME", "PRODUCT CODE", "QUANTITY", "CATEGORY", "PRICE");
	printf("______________________________________________________________________________\n\n");
	for (int i = 0; i < n; i++) {
		fread(&data, sizeof(product), 1, fptr);

		if (strstr(data.product_name,name) != 0) {
			printf("%-25s %-15d %-10d %-15s %-10.2lf\n\n",
			       data.product_name, data.code, data.quantity, data.category, data.price);
			found = 1;
		}
	}

	if (found == 0) {
		printf("-----------------------------NO RECORD FOUND----------------------------------\n");
	}
	printf("______________________________________________________________________________\n\n");
	fclose(fptr);
	system("pause");
}
//search by category
void searchbycategory() {
	int found = 0;
	printHeadersearch();
	FILE *fptr = fopen("PROJECT.bin", "rb");
	if (fptr == NULL) {
		printf("ERROR: FILE NOT FOUND\n");
		system("pause");
		return;
	}

	int n = noOFrecords();
	if (n == 0) {
		printStatussearch();
		fclose(fptr);
		system("pause");
		return;
	}

	char category[20];
	printf("\nENTER THE CATEGORY FOR PRODUCT:  ");
	fgets(category,20,stdin);
	fflush(stdin);
	if (category[strlen(category) - 1] == '\n') {
		category[strlen(category) - 1] = '\0';
	}
	strcpy(category, strupr(category));
	printf("\n");

	if(category[0] == '\0') {
		system("cls");
		printf("INVALID INPUT....\n\n");
		system("pause");
		fclose(fptr);
		return;
	}
	product data;
	printf("______________________________________________________________________________\n");
	printf("\n%-25s %-15s %-10s %-15s %-10s\n", "PRODUCT NAME", "PRODUCT CODE", "QUANTITY", "CATEGORY", "PRICE");
	printf("______________________________________________________________________________\n\n");
	for (int i = 0; i < n; i++) {
		fread(&data, sizeof(product), 1, fptr);

		if (strcmp(data.category,category) == 0) {
			printf("%-25s %-15d %-10d %-15s %-10.2lf\n\n",
			       data.product_name, data.code, data.quantity, data.category, data.price);
			found = 1;
		}
	}

	if (found == 0) {
		printf("-----------------------------NO RECORD FOUND----------------------------------\n");
	}
	printf("______________________________________________________________________________\n\n");
	fclose(fptr);
	system("pause");
}
//Function to show report
void balance() {
	system("cls");
	double sum = 0.00L;
	product data;
	if (noOFrecords() == 0) {
		printStatussearch();
		system("pause");
		return;
	}
	printf("_____________________________________________________________________________________________\n\n");
	printf("%-25s %-15s %-10s %-15s %-10s %-10s\n", "PRODUCT NAME", "PRODUCT CODE", "QUANTITY", "CATEGORY", "PRICE", "TOTAL");
	printf("_____________________________________________________________________________________________\n");
	FILE *fptr = fopen("PROJECT.bin", "rb");
	while(fread(&data, sizeof(product), 1, fptr)){
		
		printf("\n%-25s %-15d %-10d %-15s %-10.2lf %-10.2lf\n",
		       data.product_name, data.code, data.quantity,data.category,data.price,data.quantity * data.price);
		sum += data.quantity * data.price;
	}
	printf("_____________________________________________________________________________________________\n");
	printf("\n                            NO OF PRODUCTS = %d                                      \n", noOFrecords());
	printf("\n                            GRAND TOTAL = RS %.3lf                                    \n", sum);
	printf("_____________________________________________________________________________________________\n\n");
	fclose(fptr);
	system("pause");
}
//update product name
void updatename() {
	printHeaderupdate();
	FILE *fptr = fopen("PROJECT.bin", "rb");
	if (!fptr) {
		printf("Error: Could not open inventory file.\n");
		system("pause");
		return;
	}
	FILE *tempfptr = fopen("TEMP.bin", "wb");
	if (!tempfptr) {
		printf("Error: Could not create temporary file.\n");
		fclose(fptr);
		system("pause");
		return;
	}
	int code;
	printf("\nENTER THE PRODUCT CODE FOR UPDATE: ");
	scanf("%d", &code);
	getchar();
	if (code < 0) {
		printf("\nINVALID INPUT!!!\n");
		fclose(fptr);
		fclose(tempfptr);
		remove("TEMP.bin");
		system("pause");
		return;
	}
	product data;
	int found = 0,status = 0;
	while (fread(&data, sizeof(product), 1, fptr)) {
		if (data.code == code) {
			char newName[20];
			printf("\nENTER THE NEW NAME FOR PRODUCT: ");
			fgets(newName,20,stdin);
			fflush(stdin);
			if(newName[strlen(newName) - 1] == '\n') {
				newName[strlen(newName) - 1] = '\0';
			}
			getchar();
			if (newName[0] != '\0') {
				strcpy(data.product_name, strupr(newName));
				fwrite(&data, sizeof(product), 1, tempfptr);
				found = 1;
				status = 1;
			}
		} else {
			fwrite(&data, sizeof(product), 1, tempfptr);
		}
	}
	fclose(fptr);
	fclose(tempfptr);
	printStatusupdate(found,status);
}
//update product code
void updatecode() {
	printHeaderupdate();
	FILE *fptr = fopen("PROJECT.bin", "rb");
	if (!fptr) {
		printf("Error: Could not open inventory file.\n");
		system("pause");
		return;
	}

	FILE *tempfptr = fopen("TEMP.bin", "wb");
	if (!tempfptr) {
		printf("Error: Could not create temporary file.\n");
		fclose(fptr);
		system("pause");
		return;
	}
	int code;
	printf("\nENTER THE PRODUCT CODE FOR UPDATE: ");
	scanf("%d", &code);
	getchar(); 
	if (code < 0) {
		printf("\nINVALID INPUT!!!\n");
		fclose(fptr);
		fclose(tempfptr);
		remove("TEMP.bin");
		system("pause");
		return;
	}
	product data;
	int found = 0;
	int status = 0;
	while (fread(&data, sizeof(product), 1, fptr)) {
		if (data.code == code) {
			int newCode;
			printf("\nENTER THE NEW CODE FOR PRODUCT: ");
			scanf("%d", &newCode);
			getchar();
			if (newCode >= 0) {
				FILE *fptr2 = fopen("PROJECT.bin", "rb");
				if (!fptr2) {
					printf("Error: Could not reopen inventory file for validation.\n");
					fclose(fptr);
					fclose(tempfptr);
					remove("TEMP.bin");
					system("pause");
					return;
				}

				product check;
				while (fread(&check, sizeof(product), 1, fptr2)) {
					if (check.code == newCode) {
						status = 0;
						system("cls");
						printf("PRODUCT ALREADY EXISTS WITH CODE '%d'\n\n", newCode);
						fclose(fptr2);
						fclose(fptr);
						fclose(tempfptr);
						system("color 04");
						system("pause");
						system("color 0E");
						return;
					}
				}
				fclose(fptr2);
				data.code = newCode;
				fwrite(&data, sizeof(product), 1, tempfptr);
				found = 1;
				status = 1;
			}
		} else {
			fwrite(&data, sizeof(product), 1, tempfptr);
		}
	}
	fclose(fptr);
	fclose(tempfptr);
	printStatusupdate(found,status);
	system("color 0E");
}
//update product category
void updatecategory() {
	printHeaderupdate();
	FILE *fptr = fopen("PROJECT.bin", "rb");
	if (!fptr) {
		printf("Error: Could not open inventory file.\n");
		fclose(fptr);
		system("pause");
		return;
	}
	FILE *tempfptr = fopen("TEMP.bin", "wb");
	if (!tempfptr) {
		printf("Error: Could not create temporary file.\n");
		fclose(fptr);
		fclose(tempfptr);
		system("pause");
		return;
	}
	int code;
	printf("\nENTER THE PRODUCT CODE FOR UPDATE: ");
	scanf("%d", &code);
	getchar();
	getchar();
	if (code < 0) {
		printf("\nINVALID INPUT!!!\n");
		fclose(fptr);
		fclose(tempfptr);
		remove("TEMP.bin");
		system("pause");
		return;
	}
	product data;
	int found = 0;
	int status = 0;
	while (fread(&data, sizeof(product), 1, fptr) == 1) {
		if (data.code == code) {
			char newCategory[20];
			printf("\nENTER THE NEW CATEGORY FOR PRODUCT: ");
			fgets(newCategory,20,stdin);
			fflush(stdin);
			if(newCategory[strlen(newCategory) - 1] == '\n') {
				newCategory[strlen(newCategory) - 1] = '\0';
			}
			getchar();
			if (newCategory[0] != '\0') {
				strcpy(data.category, strupr(newCategory));
				fwrite(&data, sizeof(product), 1, tempfptr);
				found = 1;
				status = 1;
			}
		} else {
			fwrite(&data, sizeof(product), 1, tempfptr);
		}
	}
	fclose(fptr);
	fclose(tempfptr);
	printStatusupdate(found,status);
}
//update product price
void updateprice() {
	printHeaderupdate();
	FILE *fptr = fopen("PROJECT.bin", "rb");
	if (!fptr) {
		printf("Error: Could not open inventory file.\n");
		system("pause");
		return;
	}
	FILE *tempfptr = fopen("TEMP.bin", "wb");
	if (!tempfptr) {
		printf("Error: Could not create temporary file.\n");
		fclose(fptr);
		system("pause");
		return;
	}
	int code;
	printf("\nENTER THE PRODUCT CODE FOR UPDATE: ");
	scanf("%d", &code);
	getchar();
	if (code < 0) {
		printf("\nINVALID INPUT!!!\n");
		fclose(fptr);
		fclose(tempfptr);
		remove("TEMP.bin");
		system("pause");
		return;
	}
	product data;
	int found = 0;
	int status = 0;
	while (fread(&data, sizeof(product), 1, fptr)) {
		if (data.code == code) {
			double newPrice;
			printf("\nENTER THE NEW PRICE FOR PRODUCT: ");
			scanf("%lf", &newPrice);
			getchar();
			if(newPrice<=0) {
				fclose(fptr);
				fclose(tempfptr);
				return;
			}
			data.price = newPrice;
			fwrite(&data, sizeof(product), 1, tempfptr);
			found = 1;
			status = 1;
		} else {
			fwrite(&data, sizeof(product), 1, tempfptr);
		}
	}
	fclose(fptr);
	fclose(tempfptr);
	printStatusupdate(found,status);
}
//Function to quantity
void updatequantity() {
	printHeaderupdate();
	FILE *fptr = fopen("PROJECT.bin", "rb");
	if (!fptr) {
		printf("Error: Could not open inventory file.\n");
		system("pause");
		return;
	}
	FILE *tempfptr = fopen("TEMP.bin", "wb");
	if (!tempfptr) {
		printf("Error: Could not create temporary file.\n");
		fclose(fptr);
		system("pause");
		return;
	}
	int code;
	printf("\nENTER THE PRODUCT CODE FOR UPDATE: ");
	scanf("%d", &code);
	getchar();
	if (code < 0) {
		printf("\nINVALID INPUT!!!\n");
		fclose(fptr);
		fclose(tempfptr);
		remove("TEMP.bin");
		system("pause");
		return;
	}
	product data;
	int found = 0,status = 0;
	while (fread(&data, sizeof(product), 1, fptr)) {
		if (data.code == code) {
			int newQuantity;
			printf("\nENTER THE NEW QUANTITY FOR PRODUCT: ");
			scanf("%d", &newQuantity);
			getchar();
			if(newQuantity < 0) {
				fclose(fptr);
				fclose(tempfptr);
				return;
			}
			getchar();
			data.quantity = newQuantity;
			fwrite(&data, sizeof(product), 1, tempfptr);
			found = 1;
			status = 1;
		} else {
			fwrite(&data, sizeof(product), 1, tempfptr);
		}
	}
	fclose(fptr);
	fclose(tempfptr);
	printStatusupdate(found,status);
}
//function to delete product
void del() {
	system("cls");
	printf("________________________________________________________________________\n\n");
	printf("--------------------------DELETE PRODUCT--------------------------------\n");
	printf("________________________________________________________________________\n");

	FILE *fptr = fopen("PROJECT.bin", "rb");
	if (!fptr) {
		printf("Error: Could not open inventory file.\n");
		system("pause");
		return;
	}

	FILE *tempfptr = fopen("TEMP.bin", "wb");
	if (!tempfptr) {
		printf("Error: Could not create temporary file.\n");
		fclose(fptr);
		system("pause");
		return;
	}
	int code;
	printf("\nENTER THE PRODUCT CODE FOR DELETE :  ");
	scanf("%d", &code);
	getchar();
	if (code < 0) {
		printf("\nINVALID INPUT!!!\n");
		fclose(fptr);
		fclose(tempfptr);
		remove("TEMP.bin");
		system("pause");
		return;
	}

	product data;
	int found = 0,status=0;
	while (fread(&data, sizeof(product), 1, fptr)) {
		if (data.code == code) {
			status = 1;
			found = 1;
		} else {
			fwrite(&data, sizeof(product), 1, tempfptr);
		}
	}
	fclose(fptr);
	fclose(tempfptr);

	printStatusupdate(found,status);

}

void alerts() {
	ALERTS = 0;
	int qty = ALERTS_VALUE,found = 0;

	system("cls");
	printf("_____________________________________________________________________________________________\n\n");
	printf("-----------------------------------INVENTORY ALERTS------------------------------------------\n");
	printf("_____________________________________________________________________________________________\n");
	FILE *fptr = fopen("PROJECT.bin", "rb");
	if (fptr == NULL) {
		printf("ERROR: FILE NOT FOUND\n");
		system("pause");
		return;
	}

	int n = noOFrecords();
	if (n == 0) {
		printf("_____________________________________________________________________________________________\n\n");
		printf("%-25s %-15s %-10s %-15s %-10s %-15s\n", "PRODUCT NAME", "PRODUCT CODE", "QUANTITY", "CATEGORY", "PRICE","STATUS");
		printf("_____________________________________________________________________________________________\n\n");
		printf("---------------------------NO ALERTS FOR INVENTORY-------------------------------------------\n");
		printf("_____________________________________________________________________________________________\n\n");
		fclose(fptr);
		system("pause");
		return;
	}

	product data;
	printf("_____________________________________________________________________________________________\n\n");
	printf("%-25s %-15s %-10s %-15s %-10s %-15s\n", "PRODUCT NAME", "PRODUCT CODE", "QUANTITY", "CATEGORY", "PRICE","STATUS");
	printf("_____________________________________________________________________________________________\n\n");

	while(fread(&data, sizeof(product), 1, fptr)) {
		if (data.quantity <= qty) {
			char message[13];
			if(data.quantity == 0) {
				strcpy(message,"OUT OF STOCK");
			} else {
				strcpy(message,"LOW STOCK");
			}
			printf("%-25s %-15d %-10d %-15s %-10.2lf %-15s\n\n",
			       data.product_name, data.code, data.quantity, data.category, data.price,message);
			ALERTS++;
			found = 1;
		}
	}

	if (found == 0) {
		printf("--------------------------NO ALERTS------------------------------------------------------\n");
	}
	printf("_____________________________________________________________________________________________\n\n");
	fclose(fptr);
	system("pause");
}

void calcALERTS() {
	ALERTS = 0;
	int qty = ALERTS_VALUE;
	FILE *fptr = fopen("PROJECT.bin", "rb");
	if (fptr == NULL) {
		return;
	}
	product data;
	while(fread(&data, sizeof(product), 1, fptr)) {
		if (data.quantity <= qty) {
			ALERTS++;
		}
	}
	fclose(fptr);
}

int main() {


	while(!authenticate());
	system("COLOR 0E");
	int x,y;
	getConsoleCenter(&x,&y);
	calcALERTS();
	system("cls");
	int choice=-1;
	while (choice !=0) {
		calcALERTS();
		system("cls");
		int u=x-20;
		int v=0;
		gotoxy(u,v);
		printf("************************************************\n");
		gotoxy(u, v += 1);
		printf("*                                              *\n");
		gotoxy(u, v += 1);
		printf("*   =======================================    *\n");
		gotoxy(u, v += 1);
		printf("*   ||        INVENTORY MANAGEMENT       ||    *\n");
		gotoxy(u, v += 1);
		printf("*   ||              SYSTEM               ||    *\n");
		gotoxy(u, v += 1);
		printf("*   =======================================    *\n");
		gotoxy(u, v += 1);
		printf("*                                              *\n");
		gotoxy(u, v += 1);
		printf("************************************************\n");
		gotoxy(u,v+=2);
		printf("1.ADD PRODUCT");
		gotoxy(u,v+=2);
		printf("2.DELETE PRODUCT");
		gotoxy(u,v+=2);
		printf("3.UPDATE PRODUCTS");
		gotoxy(u,v+=2);
		printf("4.VIEW PRODUCTS");
		gotoxy(u,v+=2);
		printf("5.SEARCH PRODUCTS");
		gotoxy(u,v+=2);
		printf("6.PRODUCTS REPORT");
		gotoxy(u,v+=2);
		printf("7.STOCKS ALERTS(%d)",ALERTS);
		gotoxy(u,v+=2);
		printf("8.STOCK ALERTS SETTINGS");
		gotoxy(u,v+=2);
		printf("9.CLEAR INVENTORY");
		gotoxy(u,v+=2);
		printf("0.EXIT");
		gotoxy(u,v+=2);
		printf("ENTER YOUR CHOICE: ");
		v=0;
		scanf("%d", &choice);
		getchar();
		switch (choice) {
			case 0:
				gotoxy(++u,v+=10);
				system("cls");
				gotoxy(u,v+=2);
				printf("THANK YOU <3 FOR VISITING IMS!!! :)");
				gotoxy(u,v+=2);
				printf("POWERED BY:");
				gotoxy(u,v+=2);
				printf("MUZAMIL SULEMAN 24K-1023");
				gotoxy(u,v+=2);
				printf("HASHEEM SHUJA 24K-0521");
				gotoxy(u,v+=2);
				printf("SYED MUZAMMIL ZAIDI 24K-0887");
				gotoxy(u,v+=2);
				printf("ALI ASGHAR 24K-0780");
				gotoxy(u,v+=2);
				getch();
				break;
			case 1:
				add();
				break;
			case 2:
				del();
				break;
			case 3:
				system("cls");
				int c;
				v = 5;
				gotoxy(u,v);
				printf("________________________________________________");
				gotoxy(u,v+=2);
				printf("-------------------UPDATE MENU------------------");
				gotoxy(u,v+=2);
				printf("________________________________________________");
				gotoxy(u,v+=2);
				printf("1.UPDATE: PRODUCT NAME");
				gotoxy(u,v+=2);
				printf("2.UPDATE: PRODUCT CODE");
				gotoxy(u,v+=2);
				printf("3.UPDATE: PRODUCT QUANTITY");
				gotoxy(u,v+=2);
				printf("4.UPDATE: PRODUCT PRICE");
				gotoxy(u,v+=2);
				printf("5.UPDATE: PRODUCT CATEGORY");
				gotoxy(u,v+=2);
				printf("0.EXIT");
				gotoxy(u,v+=2);
				v=0;
				printf("ENTER YOUR CHOICE:   ");
				scanf("%d",&c);
				getchar();
				switch(c) {
					case 1: {
						updatename();
						break;
					}
					case 2: {
						updatecode();
						break;
					}
					case 3:
						updatequantity();
						break;
					case 4:
						updateprice();
						break;
					case 5:
						updatecategory();
						break;
					case 0:
						break;
				}
				break;
			case 4:
				displayAll();
				break;
			case 5:
				system("cls");
				int ch;
				v = 5;
				gotoxy(u,v);
				printf("________________________________________________");
				gotoxy(u,v+=2);
				printf("-------------------SEARCH MENU------------------");
				gotoxy(u,v+=2);
				printf("________________________________________________");
				gotoxy(u,v+=2);
				printf("1.SEARCH BY PRODUCT NAME");
				gotoxy(u,v+=2);
				printf("2.SEARCH BY PRODUCT CODE");
				gotoxy(u,v+=2);
				printf("3.SEARCH BY PRODUCT CATEGORY");
				gotoxy(u,v+=2);
				printf("4.SEARCH BY PRODUCT PRICE");
				gotoxy(u,v+=2);
				printf("0.EXIT");
				gotoxy(u,v+=2);
				v=0;
				printf("ENTER YOUR CHOICE:   ");
				scanf("%d",&ch);
				getchar();
				switch(ch) {
					case 1: {
						searchbyname();
						break;
					}
					case 2: {
						searchbycode();
						break;
					}
					case 3:
						searchbycategory();
						break;
					case 4:
						searchbyprice();
						break;
					case 0:
						break;
				}
				break;
			case 6:
				balance();
				break;
			case 7:
				alerts();
				break;
			case 8:
				alertsettings();
				system("color 0E");
				break;
			case 9:
				clear();
				system("color 0E");
				break;
			default:
				printf("\nINVALID CHOICE!!!\n\n");
				system("pause");
				break;
		}
	}
	return 0;
}
