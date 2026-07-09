#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 1001

int main() {
	int data[MAX_NUMBERS];  // input numbers (unsorted)
    int sorted_data[MAX_NUMBERS];  // numbers in sorted order
	int cnt = 0;  // count of numbers entered
	int buf;  // buffer for new input
	int i;

	while (1) {
		printf("Enter a number: ");
		scanf("%d", &buf);

        /* insert buf into sorted_data at correct position */
		for (i = cnt - 1; i >= 0; i--) {
			if (sorted_data[i] > buf) {
				sorted_data[i + 1] = sorted_data[i];
			}
			else {
				sorted_data[i + 1] = buf;
				break;
			}
		}
		if (i < 0) {
			sorted_data[0] = buf;
		}

		data[cnt] = buf;  // keep unsorted copy
		cnt++;

        /* print unsorted list */
		printf("unsorted: ");
		for (i = 0; i < cnt; i++) {
			printf("%d ", data[i]);
		}
		printf("\n");

        /* print sorted list */
		printf("sorted: ");
		for (i = 0; i < cnt; i++) {
			printf("%d ", sorted_data[i]);
		}
		printf("\n");
	}

	return 0;
}
