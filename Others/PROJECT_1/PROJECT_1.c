// PROJECT_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#pragma warning (disable : 4996)

#define CNT_LOTTO 6

int game_cnt = 1;
int chk;
int true_array[CNT_LOTTO];

// lotto fucntions
void gen_lotto(int* lotto);
void gen_my_lotto(int* my_lotto);
int check_lotto(int* lotto, int* my_lotto);
void print_result(int* lotto, int* my_lotto, int result, FILE* fid);

// helper fucntion
void current_time();

int main(int argc, char* argv[])
{
	FILE* fid;
	if ((fid = fopen("result.txt", "w")) == NULL) {
		printf("파일이 열리지 않습니다.\n"); exit(1);
	}
	current_time(fid);
	
	int* my_lotto = (int*)malloc((CNT_LOTTO) * sizeof(int));
	gen_my_lotto(my_lotto);

	int* lotto = (int*)malloc((CNT_LOTTO + 1) * sizeof(int));
	int goal; printf("목표 등수를 정하시오 [1-5] : "); scanf("%d", &goal);

	srand(time(NULL));
	do {
		// init
		for (int i = 0; i < CNT_LOTTO; ++i) true_array[i] = 0;
		gen_lotto(lotto);
		fprintf(fid, "[game #%d] ====================================\n", game_cnt);
		int result = check_lotto(my_lotto, lotto);
		print_result(my_lotto, lotto, result, fid);
		if (result == goal) break;
		++game_cnt;
	} while (1);

	fprintf(fid, "======================================================\n");
	fprintf(fid, "종료, 1 번째 선택한 번호가 %d 주차 로또에 당첨 되었습니다\n", game_cnt);
	fprintf(fid, "======================================================\n");
	
	fclose(fid);
	free(my_lotto); free(lotto);

	return 0;
}

void gen_lotto(int* lotto) {
	for (int i = 0; i < CNT_LOTTO + 1; ++i) lotto[i] = 0; // + 1 is reserved for bonus number
	const int lower = 1, upper = 45;
	int cnt = 0;
	while (cnt < CNT_LOTTO + 1) {
		int num = rand() % (upper - lower + 1) + lower;
		int chk = 1;
		for (int i = 0; i < CNT_LOTTO + 1; ++i) {
			if (lotto[i] == num) {
				chk = 0; break;
			}
		}
		if (chk == 1) lotto[cnt++] = num;
	}
}

void gen_my_lotto(int* my_lotto) {
	int i = 0, duplicated;
	while(i < CNT_LOTTO) {
		printf("\t[1] 로또 번호 입력 : ");
		int num; scanf("%d", &num);
		if (num <= 0 || num > 45) {
			printf("1-45 사이의 번호를 입력해주십시오");
			continue;
		}
		duplicated = 0;
		for (int j = 0; j < CNT_LOTTO; ++j) {
			if (my_lotto[j] == num) {
				duplicated = 1; break;
			}
		}
		if (duplicated == 1) {
			printf("%d는 이미 입력한 번호입니다.\n", num);
			continue;
		}
		my_lotto[i++] = num;
	}
	printf("\n\n"); printf("\t번호 선택 결과 : ");
	for (int i = 0; i < CNT_LOTTO; ++i) {
		printf("%d ", my_lotto[i]);
	}
	printf("\n\n");
}

int check_lotto(int* my_lotto, int* lotto) {
	chk = 0;
	for (int i = 0; i < CNT_LOTTO; ++i) {
		for (int j = 0; j < CNT_LOTTO; ++j) {
			if (my_lotto[i] == lotto[j]) {
				true_array[i] = 1; ++chk; break;
			}
		}
	}
	if (chk < 3) return 0;
	else if (chk == 3) return 5;
	else if (chk == 4) return 4;
	else if (chk == 5) {
		for (int i = 0; i < CNT_LOTTO; ++i) {
			if (my_lotto[i] == lotto[CNT_LOTTO]) {
				true_array[i] = 1; ++chk; return 2;
			}
		}
		return 3;
	}
	else if (chk == 6) return 1;
	else return -1; // invalid
}

void print_result(int* my_lotto, int* lotto, int result, FILE* fid) {
	fprintf(fid, "%d 주차 담청 번호 : ", game_cnt);
	for (int i = 0; i < CNT_LOTTO; ++i) fprintf(fid, "%d ", lotto[i]); fprintf(fid, " + 보너스 %d\n\n", lotto[CNT_LOTTO]);
	fprintf(fid, "[1] 로또 선택 번호 : ");
	for (int i = 0; i < CNT_LOTTO; ++i) fprintf(fid, "%d ", my_lotto[i]);
	fprintf(fid, "\n");
	fprintf(fid, "    당첨번호 갯수  : %d\n", chk);
	fprintf(fid, "    당첨된 번호   : ");
	if (chk == 0) { fprintf(fid, "없음"); }
	else {
		for (int i = 0; i < CNT_LOTTO; ++i) {
			if (true_array[i] == 1) fprintf(fid, "%d ", my_lotto[i]);
		}
	}
	fprintf(fid, "\n");
	fprintf(fid, "    이번주 로또 추첨 결과 %d등입니다.\n\n", result);
}

void current_time() {
	time_t now;
	struct tm now_tm;
	char buf[256];

	setlocale(LC_ALL, "Korean");
	time(&now);
	localtime_s(&now_tm, &now);

	strftime(buf, sizeof(buf), "%Y년 %m월 %d일 %p %I:%M:%S\n", &now_tm);
	printf("=================================================\n");
	printf("프로그램 시작 : %s", buf);
	printf("=================================================\n");
}

void reset_array(int* correct_lotto) {
	for (int i = 0; i < CNT_LOTTO; ++i) correct_lotto = 0;
}