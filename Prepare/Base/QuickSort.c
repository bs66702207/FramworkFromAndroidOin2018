#include <stdio.h>

void swap(int k[], int low, int high)
{
	int temp;
	temp = k[low];
	k[low] = k[high];
	k[high] = temp;
}

int Partition(int k[], int low, int high)
{
	int point;
	point = k[low];
	while(low < high) {
		while(low < high && k[high] >= point) {
			high--;
		}
		swap(k, low, high);

		while(low < high && k[low] <= point) {
			low++;
		}
		swap(k, low, high);
	}
    k[low] = point;

	return low;
}

void QSort(int k[], int low, int high)
{
	int point;
	if(low < high) {
		point = Partition(k, low, high);
		QSort(k, low, point-1);
		QSort(k, point+1, high);
	}
}

int QuickSort(int k[], int n)
{
	QSort(k, 0, n-1);
}

int main()
{
	int i, a[10] = {5, 2, 6, 0, 3, 9, 1, 7, 4, 8};

	QuickSort(a, 10);

	printf("排序后的结果是: ");
	for(i=0; i<10; i++) {
		printf("%d", a[i]);
	}
	printf("\n");

	return 0;
}
