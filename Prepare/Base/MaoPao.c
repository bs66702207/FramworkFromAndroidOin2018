#include <stdio.h>

void swap(int k[], int low, int high)
{
    int temp;
    temp = k[low];
    k[low] = k[high];
    k[high] = temp;
}

int MaoPao(int k[], int n) {
    for(int i=0; i<n; i++) {//外循环控制趟数，总趟数为长度
        for(int j=0; j<n-1-i; j++) {//内循环控制当前i趟数，所需要的比较次数
            if(k[j] > k[j+1])
                swap(k, j, j+1);
        }
    }
}

int main()
{
	int i, a[10] = {5, 2, 6, 0, 3, 9, 1, 7, 4, 8};

	MaoPao(a, 10);

	printf("排序后的结果是: ");
	for(i=0; i<10; i++) {
		printf("%d", a[i]);
	}
	printf("\n");

	return 0;
}
