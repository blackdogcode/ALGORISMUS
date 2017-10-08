// https://www.acmicpc.net/problem/1931
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#define MAX_CNT_ROOM 100000
#define INF 0xffffffff

struct Room {
	long long start;
	long long end;

	Room() {}
	Room(long long n_start, long long n_end) : start(n_start), end(n_end) {}
};

Room rooms[MAX_CNT_ROOM + 10];

void merge_sort(int p, int r);
void merge(int p, int q, int r, int s);
int howManyRoomsCanUse(int N);

int main(int argc, char *argv[]) {
	//setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int N; scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		long long start, end;
		scanf("%lld %lld", &start, &end);
		rooms[i] = Room(start, end);
	}

	merge_sort(0, N - 1);

	int ret = howManyRoomsCanUse(N);
	printf("%d\n", ret);

	return 0;
}

void merge_sort(int p, int r) {
	// base condition
	if (p >= r) return;

	// divide
	int q = (p + r) / 2;
	merge_sort(p, q);
	merge_sort(q + 1, r);

	// conquer
	merge(p, q, q + 1, r);
}

void merge(int p, int q, int r, int s) {
	// copy
	Room *left_rooms = new Room[q - p + 2];
	Room *right_rooms = new Room[s - r + 2];
	int i, j;
	for (i = 0; i <= q - p; i++)
		left_rooms[i] = rooms[p + i];
	left_rooms[i] = Room(INF, INF);
	for (j = 0; j <= s - r; j++)
		right_rooms[j] = rooms[r + j];
	right_rooms[j] = Room(INF, INF);

	// sort
	i = j = 0; 
	for (int k = p; k <= s; k++) {
		if (left_rooms[i].end < right_rooms[j].end) {
			rooms[k] = left_rooms[i++];
		}
		else if (left_rooms[i].end == right_rooms[j].end) {
			if (left_rooms[i].start <= right_rooms[j].start)
				rooms[k] = left_rooms[i++];
			else
				rooms[k] = right_rooms[j++];
		}
		else {
			rooms[k] = right_rooms[j++];
		}
	}

	delete[] left_rooms;
	delete[] right_rooms;
}

int howManyRoomsCanUse(int N) {
	int ret = 0;
	long long cur_end = -1;

	for (int i = 0; i < N; i++) {
		if (rooms[i].start >= cur_end) {
			cur_end = rooms[i].end;
			ret++;
		}
	}
	return ret;
}