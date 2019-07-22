一、 ArrayList概述:
    ArrayList是基于数组实现的，是一个动态数组，其容量能自动增长，类似于C语言中的动态申请内存，动态增长内存。
    ArrayList不是线程安全的，只能用在单线程环境下，多线程环境下可以考虑用Collections.synchronizedList(List l)函数返回一个线程安全的ArrayList类，也可以使用concurrent并发包下的CopyOnWriteArrayList类。
    ArrayList实现了Serializable接口，因此它支持序列化，能够通过序列化传输，实现了RandomAccess接口，支持快速随机访问，实际上就是通过下标序号进行快速访问，实现了Cloneable接口，能被克隆。
    每个ArrayList实例都有一个容量，该容量是指用来存储列表元素的数组的大小。它总是至少等于列表的大小。随着向ArrayList中不断添加元素，其容量也自动增长。自动增长会带来数据向新数组的重新拷贝，因此，如果可预知数据量的多少，可在构造ArrayList时指定其容量。在添加大量元素前，应用程序也可以使用ensureCapacity操作来增加ArrayList实例的容量，这可以减少递增式再分配的数量。 
    注意，此实现不是同步的。如果多个线程同时访问一个ArrayList实例，而其中至少一个线程从结构上修改了列表，那么它必须保持外部同步。

二、 ArrayList的实现:
    对于ArrayList而言，它实现List接口、底层使用数组保存所有元素。其操作基本上是对数组的操作。下面我们来分析ArrayList的源代码:
1) 私有属性:
    ArrayList定义只定义类两个私有属性:
        private transient Object[] elementData;
        private int size;
    很容易理解，elementData存储ArrayList内的元素，size表示它包含的元素的数量。
    有个关键字需要解释: transient。
    Java的serialization提供了一种持久化对象实例的机制。当持久化对象时，可能有一个特殊的对象数据成员，我们不想用serialization机制来保存它。为了在一个特定对象的一个域上关闭serialization，可以在这个域前加上关键字transient。
    有点抽象，看个例子应该能明白。
public class UserInfo implements Serializable {
    private static final long serialVersionUID = 996890129747019948L;
    private String name;
    private transient String psw;

    public UserInfo(String name, String psw) {
        this.name = name;
        this.psw = psw;
    }

    public String toString() {
        return "name=" + name + ", psw=" + psw;
    }
}

public class TestTransient {
    public static void main(String[] args) {
        UserInfo userInfo = new UserInfo("张三", "123456");
        System.out.println(userInfo);
        try {
            // 序列化，被设置为transient的属性没有被序列化
            ObjectOutputStream o = new ObjectOutputStream(new FileOutputStream("UserInfo.out"));
            o.writeObject(userInfo);
            o.close();
        } catch (Exception e) {
            // TODO: handle exception
            e.printStackTrace();
        }
        try {
            // 重新读取内容
            ObjectInputStream in = new ObjectInputStream(new FileInputStream("UserInfo.out"));
            UserInfo readUserInfo = (UserInfo) in.readObject();
            //读取后psw的内容为null
            System.out.println(readUserInfo.toString());
        } catch (Exception e) {
            // TODO: handle exception
            e.printStackTrace();
        }
    }
}
    被标记为transient的属性在对象被序列化的时候不会被保存。接着回到ArrayList的分析中......

2) 构造方法:
    ArrayList提供了三种方式的构造器，可以构造一个默认初始容量为10的空列表、构造一个指定初始容量的空列表以及构造一个包含指定collection的元素的列表，这些元素按照该collection的迭代器返回它们的顺序排列的。
    // ArrayList带容量大小的构造函数。
    public ArrayList(int initialCapacity) {
        super();
        if (initialCapacity < 0)
            throw new IllegalArgumentException("Illegal Capacity: "+ initialCapacity);
        // 新建一个数组
        this.elementData = new Object[initialCapacity];   
    }

    // ArrayList无参构造函数。默认容量是10。
    public ArrayList() {
        this(10);
    }

    // 创建一个包含collection的ArrayList
    public ArrayList(Collection<? extends E> c) {
        elementData = c.toArray();
        size = elementData.length;
        if (elementData.getClass() != Object[].class)
            elementData = Arrays.copyOf(elementData, size, Object[].class);
    }

3) 元素存储:
    ArrayList提供了set(int index, E element)、add(E e)、add(int index, E element)、addAll(Collection<? extends E> c)、addAll(int index, Collection<? extends E> c)这些添加元素的方法。下面我们一一讲解:
// 用指定的元素替代此列表中指定位置上的元素，并返回以前位于该位置上的元素。
public E set(int index, E element) {
    RangeCheck(index);
    E oldValue = (E) elementData[index];
    elementData[index] = element;
    return oldValue;
}

// 将指定的元素添加到此列表的尾部
public boolean add(E e) {
    ensureCapacity(size + 1);
    elementData[size++] = e;
    return true;
}

// 将指定的元素插入此列表中的指定位置。
// 如果当前位置有元素，当前位于该位置的元素以及所有后续元素向后移动，这个位置由新元素插入
public void add(int index, E element) {
    if (index > size || index < 0)
        throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
    // 如果数组长度不足，将进行扩容。
    ensureCapacity(size + 1); // Increments modCount!!
    // 将 elementData中从Index位置开始、长度为size-index的元素，
    // 拷贝到从下标为index+1位置开始的新的elementData数组中。
    // 即将当前位于该位置的元素以及所有后续元素右移一个位置。
    System.arraycopy(elementData, index, elementData, index + 1, size - index);
    elementData[index] = element;
    size++;
}

// 按照指定collection的迭代器所返回的元素顺序，将该collection中的所有元素添加到此列表的尾部。
public boolean addAll(Collection<? extends E> c) {
    Object[] a = c.toArray();
    int numNew = a.length;
    ensureCapacity(size + numNew); // Increments modCount
    System.arraycopy(a, 0, elementData, size, numNew);
    size += numNew;
    return numNew != 0;
}

// 从指定的位置开始，将指定collection中的所有元素插入到此列表中。
public boolean addAll(int index, Collection<? extends E> c) {
    if (index > size || index < 0)
        throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);

    Object[] a = c.toArray();
    int numNew = a.length;
    ensureCapacity(size + numNew); // Increments modCount
 
    int numMoved = size - index;
    if (numMoved > 0)
        System.arraycopy(elementData, index, elementData, index + numNew, numMoved);

    System.arraycopy(a, 0, elementData, index, numNew);
    size += numNew;
    return numNew != 0;
}

    书上都说ArrayList是基于数组实现的，属性中也看到了数组，具体是怎么实现的呢？比如就这个添加元素的方法，如果数组大，则在将某个位置的值设置为指定元素即可，如果数组容量不够了呢？
    看到add(E e)中先调用了ensureCapacity(size+1)方法，之后将元素的索引赋给elementData[size]，而后size自增。例如初次添加时，size为0，add将elementData[0]赋值为e，然后size设置为1(类似执行以下两条语句elementData[0]=e;size=1)。将元素的索引赋给elementData[size]不是会出现数组越界的情况吗？这里关键就在ensureCapacity(size+1)中了。

4) 元素读取:
// 返回此列表中指定位置上的元素。  
public E get(int index) {  
    RangeCheck(index);  
 
    return (E) elementData[index];  
}

5) 元素删除:
    ArrayList提供了根据下标或者指定对象两种方式的删除功能。如下:
// 移除此列表中指定位置上的元素。  
public E remove(int index) {  
    RangeCheck(index);  

    modCount++;  
    E oldValue = (E) elementData[index];  

    int numMoved = size - index - 1;  
    if (numMoved > 0)  
        System.arraycopy(elementData, index+1, elementData, index, numMoved);  
    elementData[--size] = null; // Let gc do its work  

    return oldValue;  
}
    首先是检查范围，修改modCount，保留将要被移除的元素，将移除位置之后的元素向前挪动一个位置，将list末尾元素置空（null），返回被移除的元素。

// 移除此列表中首次出现的指定元素(如果存在)。这是因为ArrayList中允许存放重复的元素。
public boolean remove(Object o) {
    // 由于ArrayList中允许存放null，因此下面通过两种情况来分别处理。
    if (o == null) {
        for (int index = 0; index < size; index++)
            if (elementData[index] == null) {
                // 类似remove(int index)，移除列表中指定位置上的元素。
                fastRemove(index);
                return true;
            }
    } else {
        for (int index = 0; index < size; index++) {
            if (o.equals(elementData[index])) {
                fastRemove(index);
                return true;
            }  
        }  
        return false;  
    } 
}

    首先通过代码可以看到，当移除成功后返回true，否则返回false。remove(Object o)中通过遍历element寻找是否存在传入对象，一旦找到就调用fastRemove移除对象。为什么找到了元素就知道了index，不通过remove(index)来移除元素呢？因为fastRemove跳过了判断边界的处理，因为找到元素就相当于确定了index不会超过边界，而且fastRemove并不返回被移除的元素。下面是fastRemove的代码，基本和remove(index)一致。

private void fastRemove(int index) {
    modCount++;
    int numMoved = size - index - 1;
    if (numMoved > 0)
        System.arraycopy(elementData, index+1, elementData, index, numMoved);
    elementData[--size] = null; // Let gc do its work
}

protected void removeRange(int fromIndex, int toIndex) {
    modCount++;
    int numMoved = size - toIndex;
        System.arraycopy(elementData, toIndex, elementData, fromIndex, numMoved);

    // Let gc do its work
    int newSize = size - (toIndex - fromIndex);
    while (size != newSize)
        elementData[--size] = null;
}
    这个方法是protected，及受保护的方法，为什么这个方法被定义为protected呢?
    先看下面这个例子
ArrayList<Integer> ints = new ArrayList<Integer>(Arrays.asList(0, 1, 2, 3, 4, 5, 6));
    // fromIndex low endpoint (inclusive) of the subList
    // toIndex high endpoint (exclusive) of the subList
    ints.subList(2, 4).clear();  
    System.out.println(ints);
    输出结果是[0, 1, 4, 5, 6]，结果是不是像调用了removeRange(int fromIndex,int toIndex)! 哈哈哈，就是这样的。
    但是为什么效果相同呢？是不是调用了removeRange(int fromIndex,int toIndex)呢?

6) 调整数组容量ensureCapacity:





