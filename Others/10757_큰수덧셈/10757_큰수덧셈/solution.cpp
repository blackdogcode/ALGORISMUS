// https://www.acmicpc.net/problem/10757
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_LENGTH 10001

struct BigInt {
	BigInt() { for (int i = 0; i < MAX_LENGTH; i++) data[i] = 0; }
	BigInt(const BigInt &other) { for (int i = 0; i < MAX_LENGTH; i++) data[i] = other.data[i]; }
	~BigInt() {}
	friend BigInt operator+(const BigInt &left, const BigInt &right) {
		BigInt result;
		int carry = 0, val;
		for (int i = 0; i < MAX_LENGTH; i++) {
			val = left.data[i] + right.data[i] + carry;
			result.data[i] = val % 10;
			carry = val / 10;
		}
		return result;
	}
	BigInt operator=(const BigInt &other) {
		for (int i = 0; i < MAX_LENGTH; i++) data[i] = other.data[i];
		return *this;
	}
	int data[MAX_LENGTH];
};

int strLength(char *str) {
	int length = 0;
	while (*str != 0) {
		length++; str++;
	}
	return length;
}

void strToNumber(BigInt &number, char *str) {
	int length = strLength(str);
	int i = 0;
	for (int j = length - 1; j >= 0; j--) number.data[i++] = str[j] - '0';
}

void printNumber(BigInt &number) {
	int i = MAX_LENGTH - 1;
	while (number.data[i] == 0) --i;
	while (i >= 0) printf("%d", number.data[i--]);
	puts("");
}

int main(int argc, char *argv[]) {
	//freopen("sample_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	BigInt left, right;
	char input[MAX_LENGTH];
	scanf("%s", &input); strToNumber(left, input);
	scanf("%s", &input); strToNumber(right, input);

	BigInt result = left + right;
	printNumber(result);

	return 0;
}