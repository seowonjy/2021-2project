#include<stdio.h>
#include<string.h>
#include <Windows.h>
#include <stdlib.h> 
#define SIZE 100

typedef struct {
	char ename[20]; //�۾����� �̸�
	char pname[20]; //��ǰ�� �̸�
	int date; //��¥
	int quantity; //�������
	int unquantity; //�ҷ� ����
	double perunquantity; //�ҷ���
}EMPLOYEE;

EMPLOYEE e[SIZE];
int current_Size = 0;

int add_data(); //������ ����Լ�
void menu(); //�޴�
int edit_data(); //������ �����Լ�
int statistics(); // ���������Ȯ�� �Լ�
void stmenu(); // ��������� �޴�
void ename_statistics(); // �۾��� �̸����� ���Ȯ�� �Լ�
void pname_statistics(); // ��ǰ �̸����� ���Ȯ�� �Լ�
void day_statistics(); //�ϰ� ���Ȯ�� �Լ�
void printLine(int iidd); // ������ ��� �Լ�
void printAll(); //��ü ��� ��� �Լ�
int delete_data(); //������ ���� �Լ�
void update(); //������ ���� �˰���

int main(void)
{
	FILE* rfp1 = NULL;

	int select;
	char strTemp[255];
	char* pStr;
	char* context = NULL;
	fopen_s(&rfp1, "employee.txt", "rt");

	while (1) {
		pStr = fgets(strTemp, sizeof(strTemp), rfp1);

		if (pStr == NULL)
			break;

		char* ptr = strtok_s(pStr, " ", &context);
		strcpy_s(e[current_Size].ename, 30, ptr);

		ptr = strtok_s(NULL, " ", &context);
		strcpy_s(e[current_Size].pname, 30, ptr);

		ptr = strtok_s(NULL, " ", &context);
		e[current_Size].date = atoi(ptr);

		ptr = strtok_s(NULL, " ", &context);
		e[current_Size].quantity = atoi(ptr);

		ptr = strtok_s(NULL, " ", &context);
		e[current_Size].unquantity = atoi(ptr);

		ptr = strtok_s(NULL, " ", &context);
		e[current_Size].perunquantity = atof(ptr);

		current_Size++;
	}
	fclose(rfp1);

	while (1) {
		menu();
		printf("�޴��� �Է��ϼ��� : ");
		scanf_s("%d", &select);

		switch (select)
		{
		case 1:
			system("cls");
			add_data();
			break;
		case 2:
			system("cls");
			edit_data();
			system("cls");
			printf("==            �����Ǿ����ϴ�            ==\n");
			printf("==     �ʱ�ȭ������ �̵��Ͽ����ϴ�.     ==\n");
			break;
		case 3:
			system("cls");
			delete_data();
			system("cls");
			printf("==            �����Ǿ����ϴ�            ==\n");
			printf("==     �ʱ�ȭ������ �̵��Ͽ����ϴ�.     ==\n");
			break;
		case 4:
			system("cls");
			statistics();
			break;
		case 5:
			system("cls");
			printAll();
			break;
		case 6:
			system("cls");
			return 0;
			break;
		default:
			printf("��ġ�ϴ� ����̾����ϴ�.");
			break;
		}
	}
	return 0;
}

void menu()
{
	printf("========================================\n");
	printf("||   1. ������ ��� ����Դϴ�.     ||\n");
	printf("||   2. ������ ���� ����Դϴ�.     ||\n");
	printf("||   3. ������ ���� ����Դϴ�.     ||\n");
	printf("||   4. ���Ȯ�� ����Դϴ�.          ||\n");
	printf("||   5. ��ü ��� ��� ����Դϴ�.    ||\n");
	printf("||   6. ����                          ||\n");
	printf("========================================\n");
}

int add_data()
{
	FILE* fp1 = NULL;
	fopen_s(&fp1, "employee.txt", "at");

	printf("<%d �۾������� �Է��ϼ��� >  \n", current_Size + 1);
	printf("<�۾����� �̸� >  \n");
	getchar();
	gets(e[current_Size].ename);
	printf("<��ǰ�� �̸� >  \n");
	gets(e[current_Size].pname);
	printf("<��¥�� �Է��ϼ��� ex)20211202>  \n");
	scanf_s("%d", &e[current_Size].date);
	printf("<���� ������ �Է��ϼ���  >  \n");
	scanf_s("%d", &e[current_Size].quantity);
	printf("<�ҷ� ������ �Է��ϼ���  >  \n");
	scanf_s("%d", &e[current_Size].unquantity);
	e[current_Size].perunquantity = (((double)e[current_Size].unquantity) / ((double)e[current_Size].quantity))*100;
	fprintf(fp1, "%s %s %d %d %d %.9f\n",e[current_Size].ename, e[current_Size].pname, e[current_Size].date, e[current_Size].quantity, e[current_Size].unquantity, e[current_Size].perunquantity);

	fclose(fp1);
	current_Size++;
	system("cls");

	return 0;
}

int delete_data()
{
	int linenumber=0;

	printAll();
	printf("���� �Ͻ� �۾� ��ȣ�� �Է����ּ��� : ");
	scanf_s("%d", &linenumber);
	
	for (int i = linenumber -1; i < current_Size ; i++) {
		strcpy_s(e[linenumber - 1].ename,20, e[linenumber].ename);
		strcpy_s(e[linenumber - 1].pname,20, e[linenumber].pname);
		(e[linenumber - 1].date = e[linenumber].date);
		(e[linenumber - 1].quantity = e[linenumber].quantity);
		(e[linenumber - 1].unquantity = e[linenumber].unquantity);
		(e[linenumber - 1].perunquantity = e[linenumber].perunquantity);
	}
	current_Size--;
	update();
}

void update() {
	FILE* fp2 = NULL;
	fopen_s(&fp2, "employee.txt", "wt");
	for (int i = 0; i < current_Size; i++) {
		fprintf(fp2, "%s %s %d %d %d %.9f\n", e[i].ename, e[i].pname, e[i].date, e[i].quantity, e[i].unquantity, e[i].perunquantity);
	}
	fclose(fp2);
}

int edit_data()
{
	int linenumber = 0;

	printAll();
	printf("���� �Ͻ� �۾� ��ȣ�� �Է����ּ��� : ");
	scanf_s("%d", &linenumber);

	printf("<������ �۾����� �̸��� �Է��ϼ��� >  \n");
	getchar();
	gets(e[linenumber-1].ename);
	printf("<������ ��ǰ�� �̸��� �Է��ϼ��� >  \n");
	gets(e[linenumber - 1].pname);
	printf("<������ ��¥�� �Է��ϼ��� ex)20211202>  \n");
	scanf_s("%d", &e[linenumber - 1].date);
	printf("<������ ���� ������ �Է��ϼ���  >  \n");
	scanf_s("%d", &e[linenumber - 1].quantity);
	printf("<������ �ҷ� ������ �Է��ϼ���  >  \n");
	scanf_s("%d", &e[linenumber - 1].unquantity);
	e[linenumber - 1].perunquantity = (((double)e[linenumber - 1].unquantity) / ((double)e[linenumber - 1].quantity)) * 100;

	update();
}

int statistics()
{
	int _select;
	printf("==     ��������� �̵��Ͽ����ϴ�.     ==\n");
	stmenu();
	printf("Ȯ���ϰ� ���� ��� ȭ�� ��ȣ�� �Է��ϼ��� : ");
	scanf_s("%d", &_select);

	switch (_select)
	{
	case 1:
		system("cls");
		ename_statistics();
		break;
	case 2:
		system("cls");
		pname_statistics();
		break;
	case 3:
		system("cls");
		day_statistics();
		break;
	case 4:
		system("cls");
		break;
	default:
		printf("��ġ�ϴ� ����̾����ϴ�.");
		break;
	}
	return 0;
}

void stmenu()
{
	printf("========================================\n");
	printf("||    1. �۾����̸����� ����Դϴ�.   ||\n");
	printf("||    2. ��ǰ �̸� ���� ����Դϴ�.   ||\n");
	printf("||    3. ��¥ ���� ����Դϴ�.        ||\n");
	printf("||    4. �ʱ�ȭ������ �̵�            ||\n");
	printf("========================================\n");
}

void printLine(int iidd) {
	printf("  %10s    |     ", e[iidd].ename);
	printf(" %2s       | ", e[iidd].pname);
	printf("  %8d    | ", e[iidd].date);
	printf("    %4d      | ", e[iidd].quantity);
	printf("     %3d      | ", e[iidd].unquantity);
	printf("  %.9f\n", e[iidd].perunquantity);
}

void printAll() {
	system("cls");
	printf("================================================================================================================\n");
	printf("======================================  ��ü ��� ��� ȭ�� �Դϴ�. ============================================\n");
	printf("================================================================================================================\n");
	printf(" �۾���ȣ |  �۾����� �̸�  |   ��ǰ �̸�   |   ���� ����   |   ���� ����   |   �ҷ� ����   |     �ҷ���  \n");
	printf("================================================================================================================\n");
	for (int idx = 0; idx < current_Size; idx++) {
		printf("  %3d��   | ", idx+1);
		printLine(idx);
	}
	printf("================================================================================================================\n");
}

void day_statistics()
{
	int _date;

	printAll();
	printf("������ �� ��¥�� �Է����ּ���: ");
	scanf_s("%d", &_date);
	system("cls");
	printf("==================================================================================================\n");
	printf("=================================  ��¥ ���� ��� ȭ�� �Դϴ�. ===================================\n");
	printf("==================================================================================================\n");
	printf(" �۾����� �̸�  |   ��ǰ �̸�   |   ���� ����   |   ���� ����   |   �ҷ� ����   |     �ҷ���  \n");
	printf("==================================================================================================\n");
	for (int idx = 0; idx < current_Size; idx++) {
		if (e[idx].date == _date)
			printLine(idx);
	}	
	printf("==================================================================================================\n");
}

void ename_statistics()
{
	char _ename[20];

	printAll();
	printf("������ �� �۾����� �̸��� �Է����ּ��� : ");
	getchar();
	gets(_ename);
	system("cls");
	printf("==================================================================================================\n");
	printf("==============================  �۾��� �̸� ���� ��� ȭ�� �Դϴ�. ===============================\n");
	printf("==================================================================================================\n");
	printf(" �۾����� �̸�  |   ��ǰ �̸�   |   ���� ����   |   ���� ����   |   �ҷ� ����   |     �ҷ���  \n");
	printf("==================================================================================================\n");
	for (int idx = 0; idx < current_Size; idx++)
		if (strcmp(_ename, e[idx].ename) == 0)
			printLine(idx);
	printf("==================================================================================================\n");
}

void pname_statistics()
{
	char _pname[20];

	printAll();
	printf("������ �� ��ǰ�� �̸��� �Է����ּ��� : ");
	getchar();
	gets(_pname);
	system("cls");
	printf("==================================================================================================\n");
	printf("==============================  ��ǰ �̸� ���� ��� ȭ�� �Դϴ�. =================================\n");
	printf("==================================================================================================\n");
	printf(" �۾����� �̸�  |   ��ǰ �̸�   |   ���� ����   |   ���� ����   |   �ҷ� ����   |     �ҷ���  \n");
	printf("==================================================================================================\n");
	for (int idx = 0; idx < current_Size; idx++)
		if (strcmp(_pname, e[idx].pname) == 0)
			printLine(idx);
	printf("==================================================================================================\n");
}