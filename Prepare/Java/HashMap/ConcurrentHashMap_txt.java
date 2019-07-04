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









