#include <iostream>
#include <clocale>
#include <chrono>

using namespace std;

//Метод выбора
void sortSelect(int* a, int n, int& g)
{
	int temp;
	int lowindex, lowkey, i, j;
	for (i = 0; i < n - 1; i++)
	{
		lowindex = i;
		lowkey = a[i];
		for (j = i + 1; j < n; j++)
		{
			if (a[j] < lowkey)
			{
				lowkey = a[j];
				lowindex = j;
			}
		}
		temp = a[i];
		a[i] = a[lowindex];
		a[lowindex] = temp;
		g++;
	}
}

//Метод пузырька
void sortBubble(int* a, int n, int& g)
{
	int temp;
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = n - 1; j > i; j--)
		{
			if (a[j] < a[j - 1])
			{
				temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
				g++;
			}
		}
	}
}

//Метод вставки
void sortInsert(int* a, int n, int& g)
{
	int temp;
	int i, j;
	for (i = 2; i < n; i++)
	{
		j = i;
		while (a[j] < a[j - 1])
		{
			temp = a[j];
			a[j] = a[j - 1];
			a[j - 1] = temp;
			j--;
			g++;
		}
	}
}

//Метод Шелла
void sortShell(int* a, int n, int& g)
{
	int d = n, i, j, count;
	d = d / 2;
	while (d > 0)
	{
		for (i = 0; i < n - d; i++)
		{
			j = i;
			while (j >= 0 && a[j] > a[j + d])
			{
				count = a[j];
				a[j] = a[j + d];
				a[j + d] = count;
				j--;
			}
			g++;
		}
		d = d / 2;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int n, m, x;
	int k = 0;
	double sec;
	char s;
	cout << "Введите число n - строк: ";
	cin >> n;
	cout << "Введите число m - столбцов: ";
	cin >> m;

	//Объявление двумерного массива
	int** a = new int* [n];
	for (int i = 0; i < n; i++)
		a[i] = new int[m];

	//Заполнение двумерного массива рандомными значениями
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			a[i][j] = -1000 + rand() % 2001;

	cout << endl << "1 - Сортировка методом ВЫБОРА" << endl;
	cout << "2 - Сортировка методом ПУЗЫРЬКА" << endl;
	cout << "3 - Сортировка методом ВСТАВКА" << endl;
	cout << "4 - Сортировка методом ШЕЛЛА" << endl;
	cout << "Выберите каким методом начать сортировку(цифру): ";
	cin >> x;
	cout << endl << "Вывести массив на экран? (Y/N) = ";
	cin >> s;
	switch (x) {
	case 1: {
		const auto tm = std::chrono::steady_clock::now();
		for (int i = 0; i < n; i++) {
			sortSelect(a[i], m, k);
		}
		const auto dt = std::chrono::steady_clock::now() - tm;
		sec = chrono::duration_cast<chrono::milliseconds>(dt).count();
	}
		  break;
	case 2: {
		const auto tm = std::chrono::steady_clock::now();
		for (int i = 0; i < n; i++) {
			sortBubble(a[i], m, k);
		}
		const auto dt = std::chrono::steady_clock::now() - tm;
		sec = chrono::duration_cast<chrono::milliseconds>(dt).count();
	}
		  break;
	case 3: {
		const auto tm = std::chrono::steady_clock::now();
		for (int i = 0; i < n; i++) {
			sortInsert(a[i], m, k);
		}
		const auto dt = std::chrono::steady_clock::now() - tm;
		sec = chrono::duration_cast<chrono::milliseconds>(dt).count();
	}
		  break;
	case 4: {
		const auto tm = std::chrono::steady_clock::now();
		for (int i = 0; i < n; i++) {
			sortShell(a[i], m, k);
		}
		const auto dt = std::chrono::steady_clock::now() - tm;
		sec = chrono::duration_cast<chrono::milliseconds>(dt).count();
	}
		  break;
	default: {
		cout << "Такой сортировки в списке нет";
	}
		   break;
	}

	//Вывод
	if (s == 'Y') {
		for (int i = 0; i < n; i++, cout << endl)
			for (int j = 0; j < m; j++)
				cout << a[i][j] << "\t";
	}

	for (int i = 0; i < n; i++)
		delete[]a[i];
	delete[] a;

	//Вывод время выполнения
	cout << endl << "Количество перестановок = " << k << endl;
	cout << endl << "Время выполнения сортировки = " << sec << " ms";
	cout << endl << "Время выполнения сортировки = " << sec / 1000 << " sec" << endl;
}
