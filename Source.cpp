#include <stdio.h>
#include <Windows.h>
#include <utility>
#include <string.h>


bool correctsize(size_t size)
{
	return (size < 0 || INT_MAX < (unsigned)size * sizeof(int)) ? false : true;
}

bool correctposition(int position, int size)
{
	return (position < 0 || position > size) ? false : true;
}

template <typename T>
T** createArray(size_t rowsize, size_t colsize, T max)
{
	if (correctsize(rowsize) && correctsize(colsize))
	{
		T** ptr = (int**)malloc(rowsize * sizeof(T*));
		for (size_t i = 0; i < rowsize; i++)
			ptr[i] = (T*)malloc(colsize * sizeof(T));

		for (size_t i = 0; i < rowsize; i++)
			for (size_t j = 0; j < colsize; j++)
				ptr[i][j] = rand() % max;

		return ptr;
	}
	else
	{
		printf_s("������ ������� �������\n");
		return nullptr;
	}
}






template <typename T>
int** newcoltoArray(T** array, size_t rowsize, size_t* colsize, int position, int max)
/*�������� �������, ����������� ������� ����������� ������� � ��������� �������.*/


{
	if (!correctsize(rowsize) || !correctsize(*colsize))
	{
		printf_s("������ ������� �������\n");
		return array;
	}
	if (!correctposition(position, *colsize + 1))
	{
		printf_s("������ ������� ������ �������\n");
		return array;
	}

	for (size_t i = 0; i < rowsize; i++)
		array[i] = (int*)realloc(array[i], (*colsize + 1) * sizeof(int));

	for (size_t i = 0; i < rowsize; i++)
		for (size_t j = *colsize; j > position; j--)
			std::swap(array[i][j], array[i][j - 1]);
	for (size_t i = 0; i < rowsize; i++)
	{
		size_t j = position;
		array[i][j] = rand() % max;
	}
	*colsize += 1;
	return array;
}

template <typename T>
int** deletecolfromArray(T** array, size_t rowsize, size_t* colsize, int position)
/*�������� �������, ��������� ������� ����������� ������� �� ���������� ������.*/


{
	if (!correctsize(rowsize) || !correctsize(*colsize))
	{
		printf_s("������ ������� �������\n");
		return array;
	}
	if (!correctposition(position, *colsize))
	{
		printf_s("������ ������� �������\n");
		return array;
	}

	for (size_t i = 0; i < rowsize; i++)
		for (size_t j = position; j < *colsize; j++)
			std::swap(array[i][j], array[i][j + 1]);


	for (size_t i = 0; i < rowsize; i++)
		array[i] = (int*)realloc(array[i], (*colsize - 1) * sizeof(int));
	*colsize -= 1;
	return array;
}


template <typename T>
int** transponateArray(T** array, size_t *rowsize, size_t* colsize)
/*�������� �������, �������������� �������.*/


{
	if (!correctsize(*rowsize) || !correctsize(*colsize))
	{
		printf_s("������ ������� �������\n");
		return array;
	}

	if (*rowsize > *colsize)
		for (size_t i = 0; i < *rowsize; i++)
			array[i] = (int*)realloc(array[i], *rowsize * sizeof(int));

	if (*colsize > *rowsize)
	{
		array = (int**)realloc(array, *colsize * sizeof(int*));
		for (size_t i = *rowsize; i < *colsize; i++)
			array[i] = (int*)malloc(*colsize * sizeof(int));
	}


	size_t maxsize = (*rowsize > *colsize) ? *rowsize : *colsize;


	for (size_t i = 0; i < maxsize; i++)
		for (size_t j = i + 1; j < maxsize; j++)
			std::swap(array[i][j], array[j][i]);

	if (*rowsize > *colsize)
	{
		array = (int**)realloc(array, *colsize * sizeof(int*));
		for (size_t i = 0; i < *colsize; i++)
			array[i] = (int*)realloc(array[i], *rowsize * sizeof(int));
	}

	if (*colsize > *rowsize)
	{
		array = (int**)realloc(array, *colsize * sizeof(int*));
		for (size_t i = 0; i < *rowsize; i++)
			array[i] = (int*)realloc(array[i], *rowsize * sizeof(int));
	}

	if (maxsize == *rowsize)
	{
		*rowsize = *colsize;
		*colsize = maxsize;
	}

	else
		if (maxsize == *colsize)
		{
			*colsize = *rowsize;
			*rowsize = maxsize;
		}


	return array;
}



template <typename T>
int cyclicshiftArray(T** a, size_t rowsize, size_t colsize, int route, int number)
{
	for (int k = 0; k < number; k++)
	{
		switch (route)
		{
		case 1:

			for (int i = 0; i < (rowsize - 1); i++)//�������� �����
				for (int j = 0; j < colsize; j++)
					if (i == 0)
						std::swap(a[i][j], a[rowsize - 1][j]);
					else
						std::swap(a[i][j], a[i - 1][j]);
			break;

		case 2:
			for (int i = (rowsize - 1); i > 0; i--)//�������� ����
				for (int j = 0; j < colsize; j++)
					if (i == rowsize - 1)
						std::swap(a[i][j], a[0][j]);
					else
						std::swap(a[i][j], a[i + 1][j]);
			break;
		case 3:

			for (int i = 0; i < rowsize; i++)//�������� �����
				for (int j = 0; j < (colsize - 1); j++)
					if (j == 0)
						std::swap(a[i][j], a[i][colsize - 1]);
					else
						std::swap(a[i][j], a[i][j - 1]);
			break;
		case 4:
			for (int i = 0; i < rowsize; i++)//�������� ������
				for (int j = (colsize - 1); j > 0; j--)
					if (j == colsize - 1)
						std::swap(a[i][j], a[i][0]);
					else
						std::swap(a[i][j], a[i][j + 1]);

			break;
		default:
			return -EINVAL;
		}
	}
	return 0;

}

template <typename T>
void viewarray(T** array, size_t rowsize, size_t colsize)
{
	for (size_t i = 0; i < rowsize; i++)
	{
		for (size_t j = 0; j < colsize; j++)
		{
			printf_s("%3d ", array[i][j]);
		}
		printf_s("\n");
	}

}

template <typename T>
void deletearray(T** array, size_t rowsize)
{
	for (size_t i = 0; i < rowsize; i++)
		free(array[i]);
	free(array);

}

struct COMPLEX //���������� ���������
{
	double REAL;//����
	double IMAG;
};

COMPLEX summ(COMPLEX first, COMPLEX second)
{
	COMPLEX summ;
	summ.REAL = first.REAL + second.REAL;
	summ.IMAG = first.IMAG + second.IMAG;
	return summ;
}

COMPLEX difference(COMPLEX first, COMPLEX second)
{
	COMPLEX difference;
	difference.REAL = first.REAL - second.REAL;
	difference.IMAG = first.IMAG - second.IMAG;
	return difference;
}

COMPLEX multiply(COMPLEX first, COMPLEX second)
{
	COMPLEX multiply;
	multiply.REAL = first.REAL * second.REAL - first.IMAG * second.IMAG;
	multiply.IMAG = first.REAL * second.IMAG + first.IMAG*second.REAL;
	return multiply;
}

COMPLEX division(COMPLEX first, COMPLEX second)
{
	COMPLEX division;
	division.REAL = (first.REAL * second.REAL + first.IMAG * second.IMAG) / (second.REAL*second.REAL + second.IMAG*second.IMAG);
	division.IMAG = (first.IMAG * second.REAL - first.REAL * second.IMAG) / (second.REAL*second.REAL + second.IMAG*second.IMAG);
	return division;
}
enum class Typeofgearbox { Manual, Automatic };
enum class Colorofcar { White, Black, Yellow, Red, Green };

struct	AUTOMOBILE
{
	int Length;/*������ (��)*/
	int Road_clearance; /*������� (��)*/
	int Engine_capacity; /*����� ��������� (��3)*/
	int Diameter_of_wheels; /*������� ���� (����)*/
	Colorofcar Colour; /*����*/
	Typeofgearbox Typeofgear; /*��� ������� �������*/
};

AUTOMOBILE createauto(int Length, int Road_clearance, int Engine_capacity, int Diameter_of_wheels, Colorofcar Colour, Typeofgearbox Typeofgear)
{

}

bool submenu()
{
	int submenu;
	printf_s("\n");
	printf_s("1 - ������� � ����\n");
	printf_s("0 - �����\n");
	scanf_s("%d", &submenu);
	return (submenu) ? false : true;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int menu, subsubmenu;
	for (; ;)
	{
		size_t rowsize, colsize;
		COMPLEX X = { 2.0, 5.0 }, Y = { 8.0, 10.5 }, Z;
		double tmp;
		int posofcol;
		int max = 20;
		int route, number;
		int cyclshift;
		char name[100], phonenumber[30];
		name[0] = 0;
		phonenumber[0] = 0;
		int **A;
		char **B;
		printf_s("�������� ������� 8\n");
		printf_s("__________________________________________\n");
		printf_s("�������� ����� ����:\n");
		printf_s("__________________________________________\n");
		printf_s("\n*******������������ �������*******\n");
		printf_s("__________________________________________\n");
		printf_s("1 - �������� ������� � ��������� ������ � ��������� �������\n");
		printf_s("2 - ������� �������  ��������� ������� �� ���������� �������\n");
		printf_s("3 - ����������� ����� �������\n");
		printf_s("4 - ���������������� �������\n");
		printf_s("5 - ��� � ������� � ������������ �������.\n");
		printf_s("__________________________________________\n");
		printf_s("\n*******���������*******\n");
		printf_s("__________________________________________\n");
		printf_s("6 - ����������� �����\n");
		printf_s("7 - ��������� \"����������\"\n");
		printf_s("8 - ��������� \"�����\"\n");
		printf_s("9 - ��������� \"������\"\n");
		printf_s("0 - �����\n");
		scanf_s("%d", &menu);
		switch (menu)
		{
		case 0:
			return 0;
			break;
		case 1:
			printf_s("������� ���-�� ����� �������\n");
			scanf_s("%d", &rowsize);
			printf_s("������� ���-�� �������� �������\n");
			scanf_s("%d", &colsize);
			A = createArray(rowsize, colsize, max);
			printf_s("������ �:\n");
			viewarray(A, rowsize, colsize);
			printf_s("������� ������� ������ �������\n");
			scanf_s("%d", &posofcol);
			A = newcoltoArray(A, rowsize, &colsize, posofcol, max);
			printf_s("������ ����� ���������� ������ �������\n");
			viewarray(A, rowsize, colsize);
			deletearray(A, rowsize);
			if (submenu()) return 0;
			break;
		case 2:
			printf_s("������� ���-�� ����� �������\n");
			scanf_s("%d", &rowsize);
			printf_s("������� ���-�� �������� �������\n");
			scanf_s("%d", &colsize);
			A = createArray(rowsize, colsize, max);
			printf_s("������ �:\n");
			viewarray(A, rowsize, colsize);
			printf_s("������� ������� �������, ������� ����� �������\n");
			scanf_s("%d", &posofcol);
			A = deletecolfromArray(A, rowsize, &colsize, posofcol);
			printf_s("������ ����� �������� �������\n");
			viewarray(A, rowsize, colsize);
			deletearray(A, rowsize);
			if (submenu()) return 0;
			break;
		case 3:
			printf_s("������� ���-�� ����� �������\n");
			scanf_s("%d", &rowsize);
			printf_s("������� ���-�� �������� �������\n");
			scanf_s("%d", &colsize);
			A = createArray(rowsize, colsize, max);
			printf_s("������ �:\n");
			viewarray(A, rowsize, colsize);
			printf_s("\n ������� ����������� ��������:");
			printf_s("\n 1 - �����; \t 2 - ����; \n 3 - �����; \t 4 - ������\n");
			scanf_s("%d", &route);
			printf_s("\n ������� ���������� ��������:\n");
			scanf_s("%d", &number);
			cyclshift = cyclicshiftArray(A, rowsize, colsize, route, number);
			if (cyclshift == -EINVAL)
				printf_s("������� ������� ����������� ��������\n");
			if (cyclshift == 0)
			{
				printf_s("������ ����� ������\n");
				viewarray(A, rowsize, colsize);
			}
			deletearray(A, rowsize);
			if (submenu()) return 0;
			break;
		case 4:
			printf_s("������� ���-�� ����� �������\n");
			scanf_s("%d", &rowsize);
			printf_s("������� ���-�� �������� �������\n");
			scanf_s("%d", &colsize);
			A = createArray(rowsize, colsize, max);
			printf_s("������ �:\n");
			viewarray(A, rowsize, colsize);
			printf_s("����������������� ������:\n");
			A = transponateArray(A, &rowsize, &colsize);
			viewarray(A, rowsize, colsize);
			deletearray(A, rowsize);
			if (submenu()) return 0;
			break;
		case 5:

			B = nullptr;
			for (; ;)
			{
				printf_s("�������� ���������� ��������:\n");
				printf_s("1 - ����(��������������) ������\n");
				printf_s("2 - ����� �� ������ ��������\n");
				printf_s("3 - ����� �� �����\n");
				printf_s("0 - ����� � ������� ����\n");
				scanf_s("%d", &subsubmenu);
				if (subsubmenu == 1)
				{
					printf_s("������� ���\n");
					gets_s(name);
					printf_s("������� �������\n");
					gets_s(phonenumber);
					B = (char**)malloc(2 * sizeof(char*));
					B[0] = (char*)malloc(strlen(name) * sizeof(char));
					B[1] = (char*)malloc(strlen(phonenumber) * sizeof(char));
				}
				if (subsubmenu == 2)
				{
					if (phonenumber[0])
					{
						printf_s("������� ����� ��������:\n");
						gets_s(phonenumber);
						if (!strcmp(phonenumber, B[1]))
							printf_s("\n������� ������\n");
						else
							printf_s("\n������ �������� ���\n");
					}
					else
						printf_s("��� �� ������ ��������\n");
				}
				if (subsubmenu == 3)
				{
					if (name[0])
					{
						printf_s("������� ���:\n");
						gets_s(name);
						if (!strcmp(name, B[0]))
							printf_s("\n��� �������\n");
						else
							printf_s("\n������ ����� ���\n");
					}
					else
						printf_s("��� �� ������ �����\n");
				}
				if (subsubmenu > 3 || subsubmenu < 0)
					printf_s("������ ������. ���������� ��� ���.\n");
				if (subsubmenu == 0)
					break;
			}
			if (B != nullptr)
				deletearray(B, 2);
			if (submenu()) return 0;
			break;

		case 6:
			/*printf_s("\n������� �������������� ����� ������� �����:");
			scanf_s("%lf", &X.REAL);
			printf_s("\n������� ������ ����� ������� �����:");
			scanf_s("%lf", &X.IMAG);
			printf_s("\n������� �������������� ����� ������� �����:");
			scanf_s("%lf", &Y.REAL);
			printf_s("\n������� ������ �����  ������� �����:");
			scanf_s("%lf", &Y.IMAG);*/
			printf_s("\n�������� ��������:");
			printf_s("\n 1 - ������� �����");
			printf_s("\n 2 - ������� �����");
			printf_s("\n 3 - �������� �����");
			printf_s("\n 4 - �������� �����");
			scanf_s("%d", &subsubmenu);

			if (subsubmenu == 1)
			{
				Z = summ(X, Y);
				printf_s("\n (%.2f + i(%.2f)) + (%.2f + i(%.2f))=%.2f + i(%.2f)", X.REAL, X.IMAG, Y.REAL, Y.IMAG, Z.REAL, Z.IMAG);
			}
			if (subsubmenu == 2)
			{
				Z = difference(X, Y);
				printf_s("\n (%f + i%f) - (%f + i%f)=%f + i%f", X.REAL, X.IMAG, Y.REAL, Y.IMAG, Z.REAL, Z.IMAG);
			}
			if (subsubmenu == 3)
			{
				Z = multiply(X, Y);
				printf_s("\n (%f + i%f) * (%f + i%f)=%f + i%f", X.REAL, X.IMAG, Y.REAL, Y.IMAG, Z.REAL, Z.IMAG);
			}
			if (subsubmenu == 4)
			{
				Z = division(X, Y);
				printf_s("\n (%f + i%f) / (%f + i%f)=%f + i%f", X.REAL, X.IMAG, Y.REAL, Y.IMAG, Z.REAL, Z.IMAG);
			}
			
			
			if (subsubmenu > 4 || subsubmenu < 1)
				printf_s("������ ������. ���������� ��� ���.\n");
			if (submenu()) return 0;
			break;
		default:
			printf_s("\n������ ������\n");
			if (submenu()) return 0;
			break;


		}




	}
	system("pause");
	return 0;
}


