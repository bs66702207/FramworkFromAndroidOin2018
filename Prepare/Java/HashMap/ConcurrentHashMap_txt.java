//1
想要避免Hashmap的线程安全问题有很多办法，比如改用HashTable或者Collections.synchronizedMap。
但是，这两者有着共同的问题: 性能。无论读操作还是写操作，它们都会给整个集合加锁，导致同一时间的其他操作为之阻塞。
在并发场景下，如何能够兼顾线程安全和运行效率呢? 这时候ConcurrentHashMap就应运而生了。
ConcurrentHashMap最关键是要理解一个概念: [Segment]。

Segment是什么呢? Segment本身就相当于一个HashMap对象。
同HashMap一样，Segment包含一个HashEntry数组，数组中的每一个HashEntry既是一个键值对，也是一个链表的头节点。
单一的Segment结构如下:
  0        1        2        3
[Entry3] [null] [Entry6] [Entry5]
                   ↓ next
                [Entry1]
像这样的Segment对象，在ConcurrentHashMap集合中有多少个呢? 有2的N次方个，共同保存在一个名为segments的数组当中。

//2
因此整个ConcurrentHashMap的结构如下:
[Segment1] [null] [Segment2] [null]

[Segment1]:
  0        1      2       3
[null] [Entry1] [null] [Entry3]
          ↓ next
       [Entry2]

[Segment2]:
  0        1       2       3
[null] [Entry1] [Entry3] [null]
                  ↓ next
                [Entry2]
可以说，ConcurrentHashMap是一个二级哈希表。在一个总的哈希表下面，有若干个子哈希表。

//3
ConcurrentHashMap这样的涉及有什么好处呢?
ConcurrentHashMap优势就是采用了"锁分段技术"，每一个Segment就好比一个自治区，读写操作高度自治，Segment之间互不影响。
下面我们来看看ConcurrentHashMap并发读写的几种情形:
Case1: 不同Segment的并发写入
[Segment1] [null] [Segment2] [null]
    ↑                 ↑
线程A Put          线程B Put
(执行中)           (执行中)

Case2: 同一Segment的一写一读
    [Segment1] [null] [Segment2] [null]
    ↗       ↖
线程A Put  线程B Get
(执行中)   (执行中)
同一Segment的写和读是可以并发执行的。

Case3: 同一Segment的并发写入
    [Segment1] [null] [Segment2] [null]
    ↗       ↖
线程A Put  线程B Put
(执行中)   (阻塞)
Segment的写入是需要上锁的，因此对同一Segment的并发写入会被阻塞。
由此可见，ConcurrentHashMap当中每个Segment各自持有一把锁。在保证线程安全的同时降低了锁的粒度，让并发操作效率更高。

//4
我们来看一下ConcurrentHashMap读写的详细过程:
Get方法:
1. 为输入的Key做Hash运算，得到hash值
2. 通过hash值，定位到对应的Segment对象
3. 再次通过hash值，定位到Segment当中数组的具体位置

Put方法:
1. 为输入的Key做Hash运算，得到hash值
2. 通过hash值，定位到对应的Segment对象
3. 获取可重入锁
4. 再次通过hash值，定位到Segment当中数组的具体位置
5. 插入或覆盖HashEntry对象
6. 释放锁
从步骤可以看出，ConcurrentHashMap在读写时都需要二次定位。首先定位到Segment，之后定位到Segment内的具体数组下标。

//5
既然每一个Segment都各自加锁，那么在调用Size方法的时候，怎么解决一致性的问题呢?
Size方法的目的是统计ConcurrentHashMap的总元素数量，自然需要把各个Segment内部的元素数量汇总起来。
但是，如果在统计Segment元素数量的过程中，已统计过的Segment瞬间插入新的元素，这时候该怎么办呢?
 线程A:3个
[Segment1] [null] [Segment2] [null]

线程B: Put          线程A:3个
[Segment1] [null] [Segment2] [null]

结果线程A计算Size之后是总Size=3+3?
我们来看看Size的操作流程:
ConcurrentHashMap的Size方法是一个嵌套循环，大体逻辑如下：
1. 遍历所有的Segment。
2. 把Segment的元素数量累加起来。
3. 把Segment的修改次数累加起来。
4. 判断所有Segment的总修改次数是否大于上一次的总修改次数。如果大于，说明统计过程中有修改，重新统计，尝试次数+1；如果不是。说明没有修改，统计结束。
5. 如果尝试次数超过阈值，则对每一个Segment加锁，再重新统计。
6. 再次判断所有Segment的总修改次数是否大于上一次的总修改次数。由于已经加锁，次数一定和上次相等。
7. 释放锁，统计结束。

为什么这样设计呢? 这种思想和乐观锁悲观锁的思想如出一辙。
为了尽量不锁住所有Segment，首先乐观地假设Size过程中不会有修改。当尝试一定次数，才无奈转为悲观锁，锁住所有Segment保证强一致性。

