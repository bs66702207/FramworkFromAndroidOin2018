/*
由于ArrayList只能存储对象，不能存储原生数据类型数据，下面的代码是错误的：
ArrayList<int> list = new ArrayList<>(); 错误！！！！！
只能写成：
ArrayList<Integer> list = new ArrayList<>();
*/
import java.util.ArrayList;
import java.util.Iterator;
public class ArrayListDemo {
    public static void main(String[] args) {
        // Create a list to store cities
        ArrayList<String> cityList = new ArrayList<String>();

        // Add some cities in the list
        cityList.add("London");
        // cityList now contains [London]

        cityList.add("Denver");
        // cityList now contains [London, Denver]

        cityList.add("Paris");
        // cityList now contains [London, Denver, Paris]

        cityList.add("Miami");
        // cityList now contains [London, Denver, Paris, Miami]

	    cityList.add("Seoul");
        // Contains [London, Denver, Paris, Miami, Seoul]

        cityList.add("Tokyo");
        // Contains [London, Denver, Paris, Miami, Seoul, Tokyo]

        System.out.println("List size? " + cityList.size());  // 6
        System.out.println("Is Miami in the list? " + cityList.contains("Miami"));  // true
        System.out.println("The location of Denver in the list? " + cityList.indexOf("Denver")); // 1 返回索引，如果不在list中，返回-1
        System.out.println("Is the list empty? " + cityList.isEmpty()); // Print false

        // Insert a new city at index 2
        cityList.add(2, "Xian");
        // Contains [London, Denver, Xian, Paris, Miami, Seoul, Tokyo]

        // Remove a city from the list
        cityList.remove("Miami");
        // Contains [London, Denver, Xian, Paris, Seoul, Tokyo]

        // Remove a city at index 1
        cityList.remove(1);
        // Contains [London, Xian, Paris, Seoul, Tokyo]

        // Display the contents in the list
        System.out.println(cityList.toString());
        System.out.println("------------------------------");
        System.out.println(cityList);

        // Display the contents in the list in reverse order
        for (int i = cityList.size() - 1; i >= 0; i--)
            System.out.print(cityList.get(i) + " ");
        System.out.println();

        Iterator it = cityList.iterator();
        while(it.hasNext()) {
            System.out.print(it.next()+" .... ");
        }
        System.out.println();
    }
}
