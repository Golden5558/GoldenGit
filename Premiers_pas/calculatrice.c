#include <stdio.h>

int main() {

	float a, b;
	char operation;
	float c;

	printf("Entrez le premier nombre : ");
	scanf("%f", &a);

	printf("Entrez le deuxième nombre : ");
	scanf("%f", &b);

	printf("Choissisez une opération (+, -, *, /) : ");
	scanf(" %c", &operation);

	if (operation == '+') {
		c = a + b;
	} else if (operation == '-') {
		c = a - b;
	} else if (operation == '*') {
		c = a * b;
	} else if (operation == '/') {
		if (b != 0) {
			c = a / b;
		} else {
			printf("Erreur : Division par zéro");
			return 1;
		}
	} else {
		printf("Opération invalide. \n");
		return 1;
	
	}

	printf ("Le résultat de %f %c %f est : %f\n", a, operation, b, c);

	return 0;

	}

	
