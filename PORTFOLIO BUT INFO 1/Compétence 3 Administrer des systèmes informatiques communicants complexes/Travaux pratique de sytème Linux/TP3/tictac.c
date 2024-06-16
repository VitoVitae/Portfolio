#include <stdio.h>
#include <unistd.h>

const int BEAUCOUP = 999999;

int main() {
	int loop;

	for (loop = 1; loop < BEAUCOUP; loop++) {
		sleep(1);
		printf("Ca fait %d seconde(s) que je tourne...\n", loop);
	}
}
