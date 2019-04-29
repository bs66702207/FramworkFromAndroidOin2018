//Java Number & Math 类, 所有的包装类(Integer、Long、Byte、Double、Float、Short)都是抽象类 Number 的子类。
//Java Character 类, 用于对单个字符进行操作
//Java String 类
//Java StringBuffer 和 StringBuilder 类
/*
当对字符串进行修改的时候，需要使用 StringBuffer 和 StringBuilder 类。
和 String 类不同的是，StringBuffer 和 StringBuilder 类的对象能够被多次的修改，并且不产生新的未使用对象。
StringBuilder 类在 Java 5 中被提出，它和 StringBuffer 之间的最大不同在于 StringBuilder 的方法不是线程安全的(不能同步访问)。
由于 StringBuilder 相较于 StringBuffer 有速度优势，所以多数情况下建议使用 StringBuilder 类。
然而在应用程序要求线程安全的情况下，则必须使用 StringBuffer 类。 
*/

public class BaseToolsDemo {
    public static void main(String args[]) {
        //创建字符串
        char[] helloArray = { 'r', 'u', 'n', 'o', 'o', 'b'};
        String helloString = new String(helloArray);
        System.out.println(helloString);
 
        //字符串长度
        String site = "www.runoob.com";
        int len = site.length();
        System.out.println( "菜鸟教程网址长度 : " + len );

        //连接字符串
        String string1 = "菜鸟教程网址：";
        System.out.println("1、" + string1 + "www.runoob.com");

        float floatVar = 0.2f;
        int intVar = 2;
        String stringVar = "s2";
        //创建格式化字符串
        System.out.printf("浮点型变量的值为 " +
                  "%f, 整型变量的值为 " +
                  "%d, 字符串变量的值为 " +
                  "is %s\n", floatVar, intVar, stringVar);


        String fs;
        fs = String.format("浮点型变量的值为 " +
                  "%f, 整型变量的值为 " +
                  "%d, 字符串变量的值为 " +
                  "is %s", floatVar, intVar, stringVar);
        System.out.println(fs);

        StringBuffer sBuffer = new StringBuffer("菜鸟教程官网：");
        sBuffer.append("www");
        sBuffer.append(".runoob");
        sBuffer.append(".com");
        System.out.println(sBuffer);

    }
}
