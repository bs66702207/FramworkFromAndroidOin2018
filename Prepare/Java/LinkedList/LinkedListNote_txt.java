    LinkedList也是List接口的实现类，与ArrayList不同的是，他是基于双向链表实现的。ArrayList内部是数组，元素在内存是连续存放的，LinkedList每个元素在内存都是单独存放的！插入和删除元素时速度非常快、但访问元素的速度较慢。
    LinkedList是一个双向链表, 当数据量很大或者操作很频繁的情况下，添加和删除元素时具有比ArrayList更好的性能。但在元素的查询和修改方面要弱于ArrayList。LinkedList类每个结点用内部类Node表示，LinkedList通过first和last引用分别指向链表的第一个和最后一个元素，当链表为空时，first和last都为NULL值。LinkedList数据结构如下图所示:
    只有一个元素的LinkedList
first  last
   ↘  ↙
    ————————————
   | x | 10 | x |
    ————————————
    包含四个元素的LinkedList
first                                                  last
 ↓                                                     ↓
  ————————————  →   ————————————  →   ————————————  →   ————————————
 | x | 10 | x |    | x | 10 | x |    | x | 10 | x |    | x | 10 | x |
  ————————————  ←   ————————————  ←   ————————————  ←   ————————————

    LinkedList类内部的Node结点代码如下:
//存储对象的结构Node，LinkedList的内部类
private static class Node<E> {
    E item;
    Node<E> next;//指向下一个节点
    Node<E> prev;//指向上一个节点

    Node(Node<E> prev, E element, Node<E> next) {
        this.item = element;
        this.next = next;
        this.prev = prev;
    }
}

    Node节点一共有三个属性: item代表节点值，prev代表节点的前一个节点，next代表节点的后一个节点。每个结点都有一个前驱和后继结点，并且在LinkedList中也定义了两个变量分别指向链表中的第一个和最后一个结点。
transient Node<E> first;
transient Node<E> last;

1、添加元素到LinkedList
LinkedList提供了多个添加元素的方法:

boolean add(E e)
在链表尾部添加一个元素，如果成功，返回true，否则返回false。

void addFirst(E e)
在链表头部插入一个元素。

addLast(E e)
在链表尾部添加一个元素。

void add(int index, E element)
在指定位置插入一个元素。

2、从LinkedList中删除元素
LinkedList提供了多个删除元素的方法:

boolean remove(Object o)
从当前链表中移除指定的元素。

E remove(int index)
从当前链表中移除指定位置的元素。

E removeFirst()
从当前链表中移除第一个元素。

E removeLast()
从当前链表中移除最后一个元素。

E remove()
从当前链表中移除第一个元素，同removeLast()相同。

3、从LinkedList中获取元素
LinkedList提供了多个获取元素的方法:

E get(int index)
从当前链表中获取指定位置的元素。

E getFirst()
从当前链表中获取第一个元素。

E getLast()
从当前链表中获取最后一个元素。

4、LinkedList的遍历方法
和其他的集合类遍历方式一样，LinkedList可以通过迭代器、foreach语句、for循环语句等方法遍历集合的所有元素。

    LinkedList存储元素的数据结构是双向链表结构，由存储元素的结点连接而成，每一个节点都包含前一个节点的引用，后一个节点的引用和节点存储的值。当一个新节点插入时，只需要修改其中保持先后关系的节点的引用即可。
