#include<stdio.h>

// number: number to convert
// arr: the array ptr to store the value
// return value: the length of binary number
int toBinary(unsigned int number, char* arr) {
	int i = 0;

	if (number == 0) arr[0] = 0;

	while (number > 0) {
		arr[i] = number % 2;
		number = number / 2;
		i++;
	}

	return i;
}

int main()
{
	char myArray[100];
	int length = toBinary(12, myArray);
	for (int i = 0; i < length; i++)
	{
		printf("%d", myArray[i]);
	}
}