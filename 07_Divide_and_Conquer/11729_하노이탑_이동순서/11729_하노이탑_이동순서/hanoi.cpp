#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>

void hanoi(int from, int mid, int to, int N) {
	if (N == 1) {
		printf("%d %d\n", from, to);
		return;
	}
	hanoi(from, to, mid, N - 1);
	hanoi(from, mid, to, 1);
	hanoi(mid, from, to, N - 1);
}

int main(int argc, char *argv[]) {
	int numOfBlocks; scanf("%d", &numOfBlocks);
	
	int cntMove = 1;
	for (register int i = 2; i <= numOfBlocks; ++i) cntMove = 2 * cntMove + 1;
	printf("%d\n", cntMove);

	int from = 1, mid = 2, to = 3;
	hanoi(from, mid, to, numOfBlocks);

	return 0;
}