HashMap的容量是有限的。当经过多次元素插入，使得HashMap达到一定饱和度时，Key映射位置发生冲突的几率会逐渐提高。
这时候，HashMap需要扩展它的长度，也就是进行Resize。
1. Capacity
HashMap的当前长度。上一期曾经说过，HashMap的长度是2的幂。
2. LoadFactor
HashMap负载因子，默认值为0.75f。
衡量HashMap是否进行Resize的条件如下:
HashMap.Size >= Capacity * LoadFactor

HashMap的Resize方法，具体做了什么事情呢?
1. 扩容
创建一个新的Entry空数组，长度是原数组的2倍。
2. ReHash
遍历原Entry数组，把所有的Entry重新Hash到新数组。为什么要重新Hash呢？因为长度扩大以后，Hash的规则也随之改变。
让我们回顾一下Hash公式:
index = HashCode(Key) & (Length - 1)
当原数组长度为8时，Hash运算是和111B做与运算；新数组长度为16，Hash运算是和1111B做与运算。Hash结果显然不同。

但是，HashMap的Rehash操作在多线程环境下会带来问题:
1. 假设一个HashMap已经到了Resize的临界点。此时有两个线程A和B，在同一时刻对HashMap进行Put操作
2. 此时达到Resize条件，两个线程各自进行Rezie的第一步，也就是扩容
线程A和线程B在特定位置挂起、运行等，可能会形成带环链表，程序将会进入死循环！
在高并发场景下，我们通常采用另一个集合类ConcurrentHashMap，这个集合类兼顾了线程安全和性能。

