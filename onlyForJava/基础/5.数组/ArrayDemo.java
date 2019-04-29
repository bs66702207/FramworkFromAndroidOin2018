
public class ArrayDemo {

    public static void printArray(int[] array) {
        for (int i = 0; i < array.length; i++) {
            System.out.print(array[i] + " ");
        }
        System.out.println();
    }

    public static int[] reverse(int[] list) {
        int[] result = new int[list.length];
        for (int i = 0, j = result.length - 1; i < list.length; i++, j--) {
            result[j] = list[i];
        }
        return result;
    }

    public static void main(String[] args) {

        // 数组大小
        int size = 10;
        // 定义数组
        double[] myList = new double[size];
        myList[0] = 5.6;
        myList[1] = 4.5;
        myList[2] = 3.3;
        myList[3] = 13.2;
        myList[4] = 4.0;
        myList[5] = 34.33;
        myList[6] = 34.0;
        myList[7] = 45.45;
        myList[8] = 99.993;
        myList[9] = 11123;
        // 计算所有元素的总和
        double total = 0;
        for (int i = 0; i < size; i++) {
           total += myList[i];
        }
        System.out.println("总和为： " + total);

        System.out.println("**********-***********");

        double[] myList2 = {1.9, 2.9, 3.4, 3.5};
        // 打印所有数组元素
        for (int i = 0; i < myList2.length; i++) {
           System.out.println(myList2[i] + " ");
        }
        // 计算所有元素的总和
        double total2 = 0;
        for (int i = 0; i < myList2.length; i++) {
           total2 += myList2[i];
        }
        System.out.println("Total is " + total2);
        // 查找最大元素
        double max = myList2[0];
        for (int i = 1; i < myList2.length; i++) {
           if (myList2[i] > max) max = myList2[i];
        }
        System.out.println("Max is " + max);

        System.out.println("**********-***********");

        //For-Each 循环
        // 打印所有数组元素
        for (double element: myList) {
           System.out.println(element);
        }
        
        System.out.println("**********-***********");
        printArray(new int[]{3, 1, 2, 6, 4, 2});//数组作为函数的参数
        printArray(reverse(new int[]{3, 1, 2, 6, 4, 2}));//数组作为函数的返回值

        //多维数组
        String str[][] = new String[3][4];
    }
}

