/*Linux中双向链表的经典实现*/

//1. Linux中双向链表介绍
Linux双向链表的定义主要涉及到两个文件:
include/linux/types.h
include/linux/list.h

Linux中双向链表的使用思想:
它是将双向链表节点嵌套在其它的结构体中；在遍历链表的时候，根据双链表节点的指针获取"它所在结构体的指针"，从而再获取数据。
我举个例子来说明，可能比较容易理解。假设存在一个社区中有很多人，每个人都有姓名和年龄。通过双向链表将人进行关联的模型图如下:

person代表人，它有name和age属性。为了通过双向链表对person进行链接，我们在person中添加了list_head属性。通过list_head，我们就将person关联起来了。

struct person
{
    int age;
    char name[20];
    struct list_head list;
};

//2. Linux中双向链表的源码分析
(01). 节点定义
struct list_head {
    struct list_head *next, *prev;
};
虽然名称list_head，但是它既是双向链表的表头，也代表双向链表的节点。

(02). 初始化节点
#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}
LIST_HEAD的作用是定义表头(节点)：新建双向链表表头name，并设置name的前继节点和后继节点都是指向name本身。
LIST_HEAD_INIT的作用是初始化节点：设置name节点的前继节点和后继节点都是指向name本身。
INIT_LIST_HEAD和LIST_HEAD_INIT一样，是初始化节点：将list节点的前继节点和后继节点都是指向list本身。

(03). 添加节点
static inline void __list_add(struct list_head *new,
                  struct list_head *prev,
                  struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
    __list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
    __list_add(new, head->prev, head);
}
__list_add(new, prev, next)的作用是添加节点：将new插入到prev和next之间。在linux中，以"__"开头的函数意味着是内核的内部接口，外部不应该调用该接口。
list_add(new, head)的作用是添加new节点：将new添加到head之后，是new称为head的后继节点。
list_add_tail(new, head)的作用是添加new节点：将new添加到head之前，即将new添加到双链表的末尾。
/*ps:遍历链表都是从head开始向下
    所以用list_add建立的链表先访问的是最后插入的节点，类似于栈;
    list_add_tail建立的链表先访问的是最先插入的节地点，类似于FIFO。*/

(04). 删除节点
static inline void __list_del(struct list_head * prev, struct list_head * next)
{
    next->prev = prev;
    prev->next = next;
}

static inline void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
}

static inline void __list_del_entry(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
}

static inline void list_del_init(struct list_head *entry)
{
    __list_del_entry(entry);
    INIT_LIST_HEAD(entry);
}
__list_del(prev, next) 和__list_del_entry(entry)都是linux内核的内部接口。
__list_del(prev, next) 的作用是从双链表中删除prev和next之间的节点。
__list_del_entry(entry) 的作用是从双链表中删除entry节点。
list_del(entry) 和 list_del_init(entry)是linux内核的对外接口。
list_del(entry) 的作用是从双链表中删除entry节点。
list_del_init(entry) 的作用是从双链表中删除entry节点，并将entry节点的前继节点和后继节点都指向entry本身。

(05). 替换节点
static inline void list_replace(struct list_head *old, struct list_head *new)
{
    new->next = old->next;
    new->next->prev = new;
    new->prev = old->prev;
    new->prev->next = new;
}
list_replace(old, new)的作用是用new节点替换old节点。

(06). 判断双链表是否为空
static inline int list_empty(const struct list_head *head)
{
    return head->next == head;
}
list_empty(head)的作用是判断双链表是否为空。它是通过区分"表头的后继节点"是不是"表头本身"来进行判断的。

(07). 获取节点
#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)
list_entry(ptr, type, member) 实际上是调用的container_of宏。
它的作用是：根据"结构体(type)变量"中的"域成员变量(member)的指针(ptr)"来获取指向整个结构体变量的指针。

(08). 遍历节点
#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
        pos = n, n = pos->next)
list_for_each(pos, head)和list_for_each_safe(pos, n, head)的作用都是遍历链表。但是它们的用途不一样！
list_for_each(pos, head)通常用于获取节点，而不能用到删除节点的场景。
list_for_each_safe(pos, n, head)通常删除节点的场景。

输出结果:
==== 1st iterator d-link ====
name:1 , age:10
name:2 , age:20
name:3 , age:30
name:4 , age:40
name:5 , age:50
==== delete node(age:20) ====
==== 2nd iterator d-link ====
name:1 , age:10
name:3 , age:30
name:4 , age:40
name:5 , age:50
