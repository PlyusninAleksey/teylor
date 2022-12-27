#include <stdio.h>
#include <locale.h>
#define _USE_MATH_DEFINES
#include <math.h>


double expPr(double x, int n)
{
	double sum = 1;
	double a = 1;
	int i;
	for (i = 1; i <= n; i++)
	{
		a = a * x / i;
		sum += a;
	}
	return sum;
}

double sinPr(double x, int n)
{
	double sum = x;
	double a = x;
	int i;
	for (i = 3; i <= n; i += 2)
	{
		a = a * x * x / (i - 1) / i * -1;
		sum += a;
	}
	return sum;
}

double cosPr(double x, int n)
{
	double sum = 1;
	double a = 1;
	int i;
	for (i = 2; i <= n; i += 2)
	{
		a = a * x * x * -1 / i / (i - 1);
		sum += a;
	}
	return sum;
}

double lnPr(double x, int n)
{
	double sum = (x - 1);
	double a = (x- 1);
	int i;
	for (i = 2; i <= n; i++)
	{
		a = a * - 1 * (x - 1) * (i - 1) / i;
		sum += a;
	}
	return sum;
}

void PrintTable(double x, double h, int n, int m, double (*fPr)(double, int), double (*f)(double))
{
	printf("|              |              |              |              |\n");
	printf("|       x      |     f(x)     |    fpr(x)    |    Err(x)    |\n");
	printf("|______________|______________|______________|______________|\n");
	int maxErr;
	int i;
	double max = fabs(f(x) - fPr(x, n));
	for (i = 0; i < m; i++)
	{
		printf("|              |              |              |              |\n");
		printf("|%*.*lf", 14, 4, x + h * i);
		printf("|%*.*lf", 14, 4, f(x + h * i));
		printf("|%*.*lf", 14, 4, fPr(x + h * i, n));
		printf("|%*.*lf", 14, 4, fabs(f(x + h * i) - fPr(x + h * i, n)));
		printf("|\n");
		printf("|______________|______________|______________|______________|\n");
		if (max < fabs(f(x + h * i) - fPr(x + h * i, n)))
		{
			max = fabs(f(x + h * i) - fPr(x + h * i, n));
		}
	}
	printf("Максимальная разница: %.4lf", max);
}



void main()
{
	double x;
	double h;
	int n;
	int m;
	setlocale(LC_ALL, "russian");
	printf("Выберите функцию:\n");
	printf("1.exp\n");
	printf("2.sin\n");
	printf("3.cos\n");
	printf("4.ln\n");
	int number;
	printf("Введите номер: ");
	scanf_s("%d", &number);
	double (*myFunc)(double, int);
	double (*func)(double);
	switch (number)
	{
	case 1:
		myFunc = expPr;
		func = exp;
		break;
	case 2:
		myFunc = sinPr;
		func = sin;
		break;
	case 3:
		myFunc = cosPr;
		func = cos;
		break;
	case 4:
		myFunc = lnPr;
		func = log;
		break;
	default:
		printf("Неверное введён номер");
		return;
	}

	printf("Введите x: ");
	scanf_s("%lf", &x);

	printf("Введите шаг в таблице: ");
	scanf_s("%lf", &h);

	printf("Введите число строк в таблице: ");
	scanf_s("%d", &m);

	printf("Введите значение приближения: ");
	scanf_s("%d", &n);

	PrintTable(x, h, n, m, myFunc, func);

}