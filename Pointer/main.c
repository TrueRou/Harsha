#include<stdio.h>
#include<stdlib.h>

void Increase(int* value) {
	*value = *value + 1;
}

int SumArray(int A[], int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += *(A + i); // this is equals to A[i]
	}
}

// never use int**.
void PrintArray(int array[][3], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d", *(*(array + i) + j));
		}
	}
}

// downgrade the two dimension array into one dimension.
void PrintArray2(int* array, int sizeA, int sizeB)
{
	for (int i = 0; i < sizeA * sizeB; i++)
	{
		printf("%d, ", *(array + i));
	}
	printf("\n");
}

int* SumHeap(int* a, int* b)
{
	int* return_value_ptr = malloc(sizeof(int));
	*return_value_ptr = *a + *b;
	return return_value_ptr;
	// free() at sometime
}

int SortAsc(int a, int b)
{
	return a - b;
}

int SortAbsAsc(int a, int b)
{
	return abs(a) - abs(b);
}

void BubbleSort(int* array, int size, int (*sort)(int, int))
{
	int i, j, temp;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size - 1; j++)
		{
			if (sort(array[j], array[j + 1]) > 0)
			{
				temp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = temp;
			}
		}
	}
}

// two-dim array should never considered as int **
int* SortTwoDimSumArray(int* array, int size1, int size2)
{
	int* newArray = calloc(size1, sizeof(int));
	for (int i = 0; i < size1; i++)
	{
		int sum = 0;
		for (int j = 0; j < size2; j++)
		{
			sum += array[(i * size2) + j];
		}
		newArray[i] = sum;
	}
	BubbleSort(newArray, size1, SortAsc);
	return newArray;
}

// int (*array)[3] is equals to int array[][3] but not equals to int *array[3], 
// int *array[3] means an array of ptr, length = 3
void SortTwoDimSumArray2(int(*array)[3], int size, int* result)
{
	for (int i = 0; i < size; i++)
	{
		int sum = 0;
		for (int j = 0; j < 3; j++)
		{
			sum += array[i][j];
		}
		result[i] = sum;
	}
	BubbleSort(result, size, SortAsc);
}

int main() {
	int A[] = { 1, 0, 7, 4, 3 };

	int size = sizeof(A) / sizeof(A[0]);
	int sum = SumArray(A, size); // A, &A, &A[0], they're the same.
	printf("sum is %d\n", sum);

	char str[6] = "Hello";
	char* str_ptr = &str;
	*(str_ptr + 1) = 'f';
	printf("the second character is %c\n", *(str_ptr + 1));
	printf("the whole str is %s\n", str);

	char str2[6] = "Hello";
	char* str2_ptr = &str2;
	str2_ptr = str_ptr;
	printf("the whole str is %s\n", str2);

	int array[2][3] = { {1, 2, 20}, {4, 5, 8} };
	PrintArray(array, 2);
	PrintArray2(array, 2, 3);
	printf("\n");

	int* ptr = (int*)malloc(3 * sizeof(int)); // without initialization
	int* ptr2 = (int*)calloc(3, sizeof(int)); // with initialization

	int value1 = 6;
	int value2 = 9;
	int* sum_value = SumHeap(&value1, &value2);
	printf("Heap sum value: %d\n", *sum_value);

	BubbleSort(A, 5, SortAsc);
	printf("sorted array: ");
	PrintArray2(A, 5, 1);

	float f_value1 = 1.23e-3;
	printf("f_value1: %.1e\n", f_value1);

	int the_array[2][3] = { {1, 2, 20}, {4, 5, 8} };
	int* sorted = SortTwoDimSumArray(the_array, 2, 3);
	free(sorted);

	int result[2];
	SortTwoDimSumArray2(the_array, 2, result);
	PrintArray2(result, 2, 1);
}

