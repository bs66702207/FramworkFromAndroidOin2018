#include <iostream>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <stdio.h>

using namespace std;

//mini demo
void f(int n) {
    printf("Level %d : n location %p\n",n, &n); /* #1 */
    if(n < 4) {
        //f(++n);
        f(n+1);
    }
    printf("Level %d : n location %p\n",n, &n); /* #2 */
}

/*
前四句很好理解
Level 1 : n location 0x7ffca535600c
Level 2 : n location 0x7ffca5355fec
Level 3 : n location 0x7ffca5355fcc
Level 4 : n location 0x7ffca5355fac

后四句的理解体现了递归的根本: 当某一级递归结束，则该级函数马上将程序的控制权交给该函数的调用函数
因为n已经等于4，所以不再调用f(n+1)，输出语句2，结束，控制权交给第三级调用
Level 4 : n location 0x7ffca5355fac
第三级调用函数中前一个执行过的语句是在if语句中进行第四级调用，因此，当第三级调用获得第四级给它的控制权时，它继续执行后面的代码，即执行打印语句#2
Level 3 : n location 0x7ffca5355fcc
第二级调用也执行语句#2
Level 2 : n location 0x7ffca5355fec
第二级调用也执行语句#1
Level 1 : n location 0x7ffca535600c
*/
//通过输出语句中n的地址，我们可以得出结论: 每一级的递归都是用它自己的私有变量n。关键点在于调用Level1地址和返回时的Level1地址是相同的。
/*
递归的基本原理
第一：每一级的函数调用都有它自己的变量。
第二：每一次函数调用都会有一次返回，并且是某一级递归返回到调用它的那一级，而不是直接返回到main()函数中的初始调用部分。
第三：递归函数中，位于递归调用前的语句和各级被调函数具有相同的执行顺序。例如在上面的程序中，打印语句#1位于递归调用语句之前，它按照递归调用的顺序被执行了4次，即依次为第一级、第二级、第三级、第四级。
第四：递归函数中，位于递归调用后的语句的执行顺序和各个被调函数的顺序相反。例如上面程序中，打印语句#2位于递归调用语句之后，其执行顺序依次是：第四级、第三级、第二级、第一级。(递归调用的这种特性在解决涉及到反向顺序的编程问题中很有用，下文会说到)
第五：虽然每一级递归都有自己的变量，但是函数代码不会复制。
第六：递归函数中必须包含终止递归的语句。通常递归函数会使用一个if条件语句或其他类似语句一边当函数参数达到某个特定值时结束递归调用，如上面程序的if(n > 4)。
*/

// 顺序打印
void printfNumber(std::vector<int>array, int i) {

    if(i == array.size()) {//正确退出递归
        printf("\n");
        return;
    }
    printf("%d",array[i++]);
    printfNumber(array, i);
}

// 逆序打印
void reversePrintNumber(std::vector<int>array, int i) {

    printf("%s: &:0x%p, %d\n", __func__, &i, i);
    if(i == array.size()) {
        return;
    }
/* 在循环调用中
   1. 递归语句前面的函数都是按顺序执行，
   2. 递归语句后面的函数都是逆序执行，
   3. 也就是在最后一个循环的语句反而最先被调用 */
    i++;//第8级调用到第9级的时候，8自己加一变成了9
    reversePrintNumber(array, i);
    i--;//9-- = 8
    printf("&:0x%p, %d, array: %d\n", &i, i, array[i]);//参考mini demo的讲解，这里的最近一次控制权是打印9，array[8]
    if(i == 0) printf("\n");
}

/*
递归式和递归边界
编写一个函数将一个十进制整数准换成二进制
递归式: to_binary(n/2)
递归边界: n<2
*/

void to_binary(int n) {
    int r = n%2;
    if(n>=2) {
        to_binary(n/2);
    }
    printf("%d", r);
    return;
}

int main(int argc, const char * argv[]) {
    f(1);
    std::vector<int>array = {1,2,3,4,5,6,7,8,9};
    //printfNumber(array, 0); //输出结果:123456789
    reversePrintNumber(array, 0);
    to_binary(0xa5);printf("\n");
    return 0;
}
