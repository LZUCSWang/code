int factorsum( int number ) {
	int sum = 1;
	for (int i = 2; i < number; i++) {
		if (number % i == 0)
			sum = sum + i;
	}
	return sum;
}
void PrintPN( int m, int n ) {
	int flag = 0;
	int i;
	for (i = m; i <= n; i++) {
		if (factorsum(i) == i) {
			printf("%d = %d", i, 1);
			for (int j = 2; j < i; j++) {
				if (i % j == 0)
					printf(" + %d", j);
			}
			printf("\n");
			flag = 1;
		}
	}
	if (flag == 0)
		printf("No perfect number");
}
