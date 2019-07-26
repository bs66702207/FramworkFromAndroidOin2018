import java.util.Iterator;
import java.util.LinkedList;
public class LinkedListTraverseDemo {
    public static void main(String[] args) {
        LinkedList<Integer> mList = new LinkedList<Integer>();
        for(int i=0; i<100000; i++)
             mList.addLast(i);
        //通过一般for循环来遍历LinkedList
        long start = System.currentTimeMillis();
        int size = mList.size();
        for(int i=0; i<size; i++) {
            mList.get(i);
        }
        long end = System.currentTimeMillis();
        long total = end - start;
        System.out.println("byCommonFor------>" + total + " ms");
    
        //通过迭代器来遍历LinkedList
        start = System.currentTimeMillis();
        for(Iterator iter = mList.iterator(); iter.hasNext();)
            iter.next();
        end = System.currentTimeMillis();
        total = end - start;
        System.out.println("byIterator------>" + total + " ms");
    
        //通过foreach来遍历LinkedList
        start = System.currentTimeMillis();
        for(Integer integ:mList)
            ;
        end = System.currentTimeMillis();
        total = end - start;
        System.out.println("byForEach------>" + total + " ms");
    }
}
