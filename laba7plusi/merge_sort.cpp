#include "merge_sort.h"

void Merge(std::vector<Student>& students, int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;

	Student* leftArray = new Student[n1];
	Student* rightArray = new Student[n2];

	for (int i = 0; i < n1; i++) {
		leftArray[i] = students[l + i];
	}
	for (int j = 0; j < n2; j++) {
		rightArray[j] = students[m + 1 + j];
	}

	int i = 0;
	int j = 0;
	int k = l;

	// Сливаем разделенные массивы в основной, сортируя пары элементов
	while (i < n1 && j < n2) {
		if (leftArray[i].score >= rightArray[j].score) {
			students[k] = leftArray[i];
			i++;
		}
		else {
			students[k] = rightArray[j];
			j++;
		}
		k++;
	}

	// Если остались элементы в левом массиве, то добавляем оставшиеся в основной
	while (i < n1) {
		students[k] = leftArray[i];
		i++;
		k++;
	}

	// Тоже самое с правым массивом
	while (j < n2) {
		students[k] = rightArray[j];
		j++;
		k++;
	}

	delete[] leftArray;
	delete[] rightArray;
}

void MergeSortStudents(std::vector<Student>& students, int l, int r)
{
	if (l >= r) {
		return;
	}

	int m = l + (r - l) / 2;

	MergeSortStudents(students, l, m);
	MergeSortStudents(students, m + 1, r);

	Merge(students, l, m, r);
}
