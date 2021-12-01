#include<stdio.h>
#include<string.h>
#include <Windows.h>
#include <stdlib.h> 
#define SIZE 100

typedef struct {
	char ename[20]; //작업자의 이름
	char pname[20]; //제품의 이름
	int date; //날짜
	int quantity; //생산수량
	int unquantity; //불량 수량
	double perunquantity; //불량률
}EMPLOYEE;

EMPLOYEE e[SIZE];
int current_Size = 0;

int add_data(); //데이터 등록함수
void menu(); //메뉴
int edit_data(); //데이터 수정함수
int statistics(); // 데이터통계확인 함수
void stmenu(); // 데이터통계 메뉴
void ename_statistics(); // 작업자 이름기준 통계확인 함수
void pname_statistics(); // 제품 이름기준 통계확인 함수
void day_statistics(); //일간 통계확인 함수
void printLine(int iidd); // 데이터 출력 함수
void printAll(); //전체 통계 출력 함수
int delete_data(); //데이터 삭제 함수
void update(); //데이터 수정 알고리즘

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
		printf("메뉴를 입력하세요 : ");
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
			printf("==            수정되었습니다            ==\n");
			printf("==     초기화면으로 이동하였습니다.     ==\n");
			break;
		case 3:
			system("cls");
			delete_data();
			system("cls");
			printf("==            삭제되었습니다            ==\n");
			printf("==     초기화면으로 이동하였습니다.     ==\n");
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
			printf("일치하는 기능이없습니다.");
			break;
		}
	}
	return 0;
}

void menu()
{
	printf("========================================\n");
	printf("||   1. 생산기록 등록 기능입니다.     ||\n");
	printf("||   2. 생산기록 수정 기능입니다.     ||\n");
	printf("||   3. 생산기록 삭제 기능입니다.     ||\n");
	printf("||   4. 통계확인 기능입니다.          ||\n");
	printf("||   5. 전체 통계 출력 기능입니다.    ||\n");
	printf("||   6. 종료                          ||\n");
	printf("========================================\n");
}

int add_data()
{
	FILE* fp1 = NULL;
	fopen_s(&fp1, "employee.txt", "at");

	printf("<%d 작업정보를 입력하세요 >  \n", current_Size + 1);
	printf("<작업자의 이름 >  \n");
	getchar();
	gets(e[current_Size].ename);
	printf("<제품의 이름 >  \n");
	gets(e[current_Size].pname);
	printf("<날짜를 입력하세요 ex)20211202>  \n");
	scanf_s("%d", &e[current_Size].date);
	printf("<생산 수량을 입력하세요  >  \n");
	scanf_s("%d", &e[current_Size].quantity);
	printf("<불량 수량을 입력하세요  >  \n");
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
	printf("삭제 하실 작업 번호를 입력해주세요 : ");
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
	printf("수정 하실 작업 번호를 입력해주세요 : ");
	scanf_s("%d", &linenumber);

	printf("<수정할 작업자의 이름을 입력하세요 >  \n");
	getchar();
	gets(e[linenumber-1].ename);
	printf("<수정할 제품의 이름을 입력하세요 >  \n");
	gets(e[linenumber - 1].pname);
	printf("<수정할 날짜를 입력하세요 ex)20211202>  \n");
	scanf_s("%d", &e[linenumber - 1].date);
	printf("<수정할 생산 수량을 입력하세요  >  \n");
	scanf_s("%d", &e[linenumber - 1].quantity);
	printf("<수정할 불량 수량을 입력하세요  >  \n");
	scanf_s("%d", &e[linenumber - 1].unquantity);
	e[linenumber - 1].perunquantity = (((double)e[linenumber - 1].unquantity) / ((double)e[linenumber - 1].quantity)) * 100;

	update();
}

int statistics()
{
	int _select;
	printf("==     통계기능으로 이동하였습니다.     ==\n");
	stmenu();
	printf("확인하고 싶은 통계 화면 번호를 입력하세요 : ");
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
		printf("일치하는 기능이없습니다.");
		break;
	}
	return 0;
}

void stmenu()
{
	printf("========================================\n");
	printf("||    1. 작업자이름기준 통계입니다.   ||\n");
	printf("||    2. 제품 이름 기준 통계입니다.   ||\n");
	printf("||    3. 날짜 기준 통계입니다.        ||\n");
	printf("||    4. 초기화면으로 이동            ||\n");
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
	printf("======================================  전체 통계 출력 화면 입니다. ============================================\n");
	printf("================================================================================================================\n");
	printf(" 작업번호 |  작업자의 이름  |   제품 이름   |   생산 일자   |   생산 수량   |   불량 수량   |     불량률  \n");
	printf("================================================================================================================\n");
	for (int idx = 0; idx < current_Size; idx++) {
		printf("  %3d번   | ", idx+1);
		printLine(idx);
	}
	printf("================================================================================================================\n");
}

void day_statistics()
{
	int _date;

	printAll();
	printf("기준이 될 날짜를 입력해주세요: ");
	scanf_s("%d", &_date);
	system("cls");
	printf("==================================================================================================\n");
	printf("=================================  날짜 기준 출력 화면 입니다. ===================================\n");
	printf("==================================================================================================\n");
	printf(" 작업자의 이름  |   제품 이름   |   생산 일자   |   생산 수량   |   불량 수량   |     불량률  \n");
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
	printf("기준이 될 작업자의 이름을 입력해주세요 : ");
	getchar();
	gets(_ename);
	system("cls");
	printf("==================================================================================================\n");
	printf("==============================  작업자 이름 기준 출력 화면 입니다. ===============================\n");
	printf("==================================================================================================\n");
	printf(" 작업자의 이름  |   제품 이름   |   생산 일자   |   생산 수량   |   불량 수량   |     불량률  \n");
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
	printf("기준이 될 제품의 이름을 입력해주세요 : ");
	getchar();
	gets(_pname);
	system("cls");
	printf("==================================================================================================\n");
	printf("==============================  제품 이름 기준 출력 화면 입니다. =================================\n");
	printf("==================================================================================================\n");
	printf(" 작업자의 이름  |   제품 이름   |   생산 일자   |   생산 수량   |   불량 수량   |     불량률  \n");
	printf("==================================================================================================\n");
	for (int idx = 0; idx < current_Size; idx++)
		if (strcmp(_pname, e[idx].pname) == 0)
			printLine(idx);
	printf("==================================================================================================\n");
}