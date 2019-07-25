import java.util.LinkedList;

public class LinkedListTest {
    public static void main(String[] args) {
        LinkedList<String> mList = new LinkedList<String>();
        mList.add("1");
        mList.add("2");
        mList.add("3");
        mList.add("4");
        mList.add("5");
        //获取链表的第一个和最后一个元素
        System.out.println("获取链表的第一个和最后一个元素:");
        System.out.println("链表的第一个元素是: " + mList.getFirst());
        System.out.println("链表最后一个元素是: " + mList.getLast());

        //删除链表的第一个和最后一个元素
        System.out.println("删除链表的第一个和最后一个元素:");
        mList.removeFirst();
        mList.removeLast();
        System.out.println("链表的第一个元素是: " + mList.getFirst());
        System.out.println("链表最后一个元素是: " + mList.getLast());

        //使用链表实现栈效果
        System.out.println("使用链表实现栈效果:");
        StackL stack = new StackL();
        for(int i = 0; i < 10; i++) {
            stack.push(i);
            System.out.print("push: " + i + ", ");
        }
        System.out.println();
        System.out.println("pop: " + stack.pop());
        System.out.println("pop: " + stack.pop());
        System.out.println("pop: " + stack.pop());
        System.out.println("pop: " + stack.pop());
        System.out.println("pop: " + stack.pop());

        //使用链表来实现队列效果
        System.out.println("使用链表来实现队列效果:");
        Queue queue = new Queue();
        for(int i = 0; i < 10; i++) {
            queue.put(Integer.toString(i));
            System.out.print("put: " + i + ", ");
        }
        System.out.println();
        while (!queue.isEmpty())
            System.out.println("get: " + queue.get());

        //根据范围删除列表元素
        System.out.println("根据范围删除列表元素:");
        LinkedList<String> nList = new LinkedList<String>();
        nList.add("1");
        nList.add("2");
        nList.add("3");
        nList.add("4");
        nList.add("5");
        System.out.println(nList);
        nList.subList(2, 5).clear();
        System.out.println(nList);

        //查找元素位置
        System.out.println("查找元素位置:");
        LinkedList<String> oList = new LinkedList<String>();
        oList.add("1");
        oList.add("2");
        oList.add("3");
        oList.add("4");
        oList.add("5");
        oList.add("2");
        System.out.println(oList.indexOf("2"));
        System.out.println(oList.lastIndexOf("2"));

    }
}

class StackL {
    private LinkedList list = new LinkedList();
    public void push(Object v) {
        list.addFirst(v);
    }
    public Object top() {
        return list.getFirst();
    }
    public Object pop() {
        return list.removeFirst();
    }
}

class Queue {
    private LinkedList list = new LinkedList();
    public void put(Object v) {
        list.addFirst(v);
    }
    public Object get() {
        return list.removeLast();
    }
    public boolean isEmpty() {
        return list.isEmpty();
    }
}

