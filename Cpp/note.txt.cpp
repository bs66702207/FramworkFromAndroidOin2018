
//实现自己的智能指针
Cpp/cpp_projects/19th_smartpointer/person2.cpp //test_func里面new完，但是没有delete导致内存泄漏
Cpp/cpp_projects/19th_smartpointer/person3.cpp //sp为局部栈变量，里面维护堆上的person，没有引用计数
Cpp/cpp_projects/19th_smartpointer/person4.cpp //sp other = new Person();失败分析
Cpp/cpp_projects/19th_smartpointer/person5.cpp //加入sp(const sp &other)修复person4，编译器帮忙做了些优化，重复析构sp，导致sp维护的对象delete两次，所以需要加入引用计数
Cpp/cpp_projects/19th_smartpointer/person6.cpp //加入引用计数机制
Cpp/cpp_projects/19th_smartpointer/person7.cpp //加入(*sp).XXX操作
Cpp/cpp_projects/19th_smartpointer/person8.cpp //将计数机制抽离出来class RefBase，让Person来继承
Cpp/cpp_projects/19th_smartpointer/person9.cpp //变成类模板，不仅仅可以指向Person

//Android的轻量级智能指针
Cpp/cpp_projects/20th_light_smartpointer/
//与自己实现不同的是它对引用计数进行了线程安全操作，但是引用计数为0时
inline void decStrong(__attribute__((unused)) const void* id) const {
    if (__sync_fetch_and_sub(&mCount, 1) == 1) {
        //执行删除对象操作时，被其他线程切换出去了，而其他线程进行了+1操作，那么切换回来时这里就不应该删除了，所以需要使用者保证线程的同步
        delete static_cast<const T*>(this);
    }
}

//强指针/强引用: A指向B，A决定B的生死
//弱指针/弱引用: A指向B，A不能决定B的生死
//强引用计数 始终小于等于 弱引用计数
Cpp/cpp_projects/21th_strongpointer_weakpointer/01th/ //相互引用增加各自的计数导致无法析构
Cpp/cpp_projects/21th_strongpointer_weakpointer/02th/ //system/core/util cutil和RefBase.cpp的移植编译，但是无法析构的问题依然存在
Cpp/cpp_projects/21th_strongpointer_weakpointer/03th/ //sp->wp，解决“死锁”导致无法析构的问题
Cpp/cpp_projects/21th_strongpointer_weakpointer/04th/ //wp没有重载 "->" "*"，如果向使用s->或者(*s)->，需要升级为强指针
Cpp/cpp_projects/21th_strongpointer_weakpointer/05th/ //弱指针升级强指针的应用

class RefBase {
    class weakref_impl;
    weakref_impl* const mRefs;//efBase类包含了一个weakref_impl类指针mRefs
}

class RefBase::weakref_impl : public RefBase::weakref_type {//weakref_type提供一些计数接口等
public:
    volatile int32_t    mStrong;//强引用计数
    volatile int32_t    mWeak;//弱引用计数
    RefBase* const      mBase;//指向它的宿主类RefBase
    volatile int32_t    mFlags;//mFlags是一个标志位，它指示了维护对象引用计数所使用的策略
}

//! Flags for extendObjectLifetime()
enum {
    OBJECT_LIFETIME_STRONG  = 0x0000,
    OBJECT_LIFETIME_WEAK    = 0x0001,
    OBJECT_LIFETIME_MASK    = 0x0001
};

    查看"Android强弱智能指针UML.jpeg"之后，每一个RefBase对象包含了一个weakref_impl对象，而weakref_impl对象实现了weakref_type接口，
同时它可以包含多个ref_entry对象，ref_entry是调试用的一个结构体，实际使用中可以不关注。

//*****  a 强引用计数  *****/
//sp类
class sp {
private:
    T* m_ptr;
}

//sp的构造函数
template<typename T>
sp<T>::sp(const sp<T>& other)//这里传进来的参数other一定是继承于RefBase类的，因此，在函数的内部，它调用的是RefBase类的incStrong函数
        : m_ptr(other.m_ptr) {
    if (m_ptr)
        m_ptr->incStrong(this);
}

//RefBase
void RefBase::incStrong(const void* id) const

RefBase::RefBase()//成员变量mRefs是在RefBase类的构造函数中创建的
    : mRefs(new weakref_impl(this))
{
}

//在这个incStrong函数中，主要做了三件事情：
//一是增加弱引用计数：
refs->addWeakRef(id);
refs->incWeak(id);

//二是增加强引用计数：
refs->addStrongRef(id);
const int32_t c = android_atomic_inc(&refs->mStrong);

//三是如果发现是首次调用这个对象的incStrong函数，就会调用一个这个对象的onFirstRef函数，让对象有机会在对象被首次引用时做一些处理逻辑：
//这里的c返回的是refs->mStrong加1前的值，如果发现等于INITIAL_STRONG_VALUE，
//就说明这个对象的强引用计数是第一次被增加，因此，refs->mStrong就是初始化为INITIAL_STRONG_VALUE的，它的值为：#define INITIAL_STRONG_VALUE (1<<28)
if (c != INITIAL_STRONG_VALUE) {
    return;
}
android_atomic_add(-INITIAL_STRONG_VALUE, &refs->mStrong);
refs->mBase->onFirstRef();
//这个值加1后等于1<<28 + 1，不等于1，因此，后面要再减去-INITIAL_STRONG_VALUE，于是，refs->mStrong就等于1了，
//就表示当前对象的强引用计数值为1了，这与这个对象是第一次被增加强引用计数值的逻辑是一致的。

//*****  b 弱引用计数  *****/
//首先是调用weakref_impl类的addWeakRef函数，我们知道，在Release版本中，这个函数也不做，
//而在Debug版本中，这个函数增加了一个ref_entry对象到了weakref_impl对象的mWeakRefs列表中，表示此weakref_impl对象的弱引用计数被增加了一次。
//接着又调用了weakref_impl类的incWeak函数，真正增加弱引用计数值就是在这个函数实现的了，weakref_impl类的incWeak函数继承于其父类weakref_type的incWeak函数
void RefBase::weakref_type::incWeak(const void* id)
{
    weakref_impl* const impl = static_cast<weakref_impl*>(this);
    impl->addWeakRef(id);
    const int32_t c __unused = android_atomic_inc(&impl->mWeak);//增加弱引用计数
    ALOG_ASSERT(c >= 0, "incWeak called on %p after last weak ref", this);
}

//*****  c 强指针类的析构函数  *****/
template<typename T>
sp<T>::~sp() {
    if (m_ptr)
        m_ptr->decStrong(this);
}
//同样，这里的m_ptr指向的目标对象一定是继承了RefBase类的，因此，这里调用的是RefBase类的decStrong函数
void RefBase::decStrong(const void* id) const
{
    weakref_impl* const refs = mRefs;
    refs->removeStrongRef(id);
    const int32_t c = android_atomic_dec(&refs->mStrong);//真正实现强引用计数减1的操作是下面语句
#if PRINT_REFS
    ALOGD("decStrong of %p from %p: cnt=%d\n", this, id, c);
#endif
    ALOG_ASSERT(c >= 1, "decStrong() called on %p too many times", refs);
    //如果发现减1前，此对象的强引用计数为1，就说明从此以后，就再没有地方引用这个目标对象了，这时候，就要看看是否要delete这个目标对象了
    if (c == 1) {
        refs->mBase->onLastStrongRef(id);
//在强引用计数为0的情况下，如果对象的标志位OBJECT_LIFETIME_WEAK被设置了，就说明这个对象的生命周期是受弱引用计数所控制的，
//因此，这时候就不能delete对象，要等到弱引用计数也为0的情况下，才能delete这个对象
        if ((refs->mFlags&OBJECT_LIFETIME_MASK) == OBJECT_LIFETIME_STRONG) {
            delete this;
        }
    }
    refs->decWeak(id);
}

void RefBase::weakref_type::decWeak(const void* id)
{
    weakref_impl* const impl = static_cast<weakref_impl*>(this);
    impl->removeWeakRef(id);
    const int32_t c = android_atomic_dec(&impl->mWeak);//实现弱引用计数减1
    ALOG_ASSERT(c >= 1, "decWeak called on %p too many times", this);
    //减1前如果发现不等于1，那么就什么也不用做就返回了，如果发现等于1，就说明当前对象的弱引用计数值为0了，这时候，就要看看是否要delete这个对象了
    if (c != 1) return;
    if ((impl->mFlags&OBJECT_LIFETIME_WEAK) == OBJECT_LIFETIME_STRONG) {//A 如果目标对象的生命周期是不受弱引用计数控制的，就执行下面语句：
        //场景A1: 增加对象的强引用计数的时候，会同时增加对象的弱引用计数
        //场景A2: 当我们使用一个弱指针来指向对象时，在弱指针对象的构造函数里面，也会增加对象的弱引用计数，不过这时候，就只是增加对象的弱引用计数了，并没有同时增加对象的强引用计数
        if (impl->mStrong == INITIAL_STRONG_VALUE) {//场景A2
            delete impl->mBase;
        } else {//场景A1 delete掉weakref_impl，但是不delete具体对象
            delete impl;
        }
    } else {//B 反之受引用计数控制，delete具体对象
        impl->mBase->onLastWeakRef(id);
        if ((impl->mFlags&OBJECT_LIFETIME_MASK) == OBJECT_LIFETIME_WEAK) {
            delete impl->mBase;
        }
    }
}

//场景1讨论：为什么要在这里delete这个weakref_impl对象呢？这里的weakref_impl对象是在RefBase的构造函数里面new出来的，理论上说应该在在RefBase的析构函数里delete掉这个weakref_impl对象的。在RefBase的析构函数里面，的确是会做这件事情：
RefBase::~RefBase()
{
    if (mRefs->mStrong == INITIAL_STRONG_VALUE) {
        delete mRefs;
    } else {
        if ((mRefs->mFlags & OBJECT_LIFETIME_MASK) != OBJECT_LIFETIME_STRONG) {
            if (mRefs->mWeak == 0) {
                delete mRefs;
            }
        }
    }
    const_cast<weakref_impl*&>(mRefs) = NULL;
}
//但是不要忘记，在这个场景下，目标对象是前面的RefBase::decStrong函数delete掉的，这时候目标对象就会被析构，但是它的弱引用计数值尚未执行减1操作，因此，这里的mRefs->mWeak == 0条件就不成立，于是就不会delete这个weakref_impl对象，因此，就延迟到执行这里decWeak函数时再执行。
//如果场景2，这里的impl->mStrong值就等于INITIAL_STRONG_VALUE了，这时候由于没有地方会负责delete目标对象，因此，就需要把目标对象（imp->mBase）delete掉了，否则就会造成内存泄漏。在delete这个目标对象的时候，就会执行RefBase类的析构函数，这时候目标对象的弱引用计数等于0，于是，就会把weakref_impl对象也一起delete掉了。

//回到外层的if语句中 else B分支，如果目标对象的生命周期是受弱引用计数控制的，就delete impl->mBase;
//理论上说，如果目标对象的生命周期是受弱引用计数控制的，那么当强引用计数和弱引用计数都为0的时候，这时候就应该delete目标对象了，但是这里还有另外一层控制，我们可以设置目标对象的标志值为OBJECT_LIFETIME_FOREVER，即目标对象的生命周期完全不受强引用计数和弱引用计数控制，在这种情况下，即使目标对象的强引用计数和弱引用计数都同时为0，这里也不能delete这个目标对象，那么，由谁来delete掉呢？当然是谁new出来的，就谁来delete掉了，这时候智能指针就完全退化为普通指针了，这里的智能指针设计的非常强大。

//分析到这里，有必要小结一下：
#define A. 如果对象的标志位被设置为0，那么只要发现对象的强引用计数值为0，那就会自动delete掉这个对象；
#define B. 如果对象的标志位被设置为OBJECT_LIFETIME_WEAK，那么只有当对象的强引用计数和弱引用计数都为0的时候，才会自动delete掉这个对象；
#define C. 如果对象的标志位被设置为OBJECT_LIFETIME_FOREVER，那么对象就永远不会自动被delete掉，谁new出来的对象谁来delete掉。

//*****  d 弱指针  *****/
class wp
{
    T*              m_ptr;
    weakref_type*   m_refs;
}
//弱指针所使用的引用计数类与强指针一样，都是RefBase类，因此，这里就不再重复介绍了，我们直接来弱指针的实现
//与强指针类相比，它们都有一个成员变量m_ptr指向目标对象，但是弱指针还有一个额外的成员变量m_refs，它的类型是weakref_type指针，下面我们分析弱指针的构造函数时再看看它是如果初始化的。这里我们需要关注的仍然是弱指针的构造函数和析构函数。
template<typename T>
wp<T>::wp(T* other)
    : m_ptr(other)
{
    if (other) m_refs = other->createWeak(this);//这里的参数other一定是继承了RefBase类，因此，这里调用了RefBase类的createWeak函数
}

//这里的成员变量mRefs的类型为weakref_impl指针，weakref_impl类的incWeak函数我们在前面已经看过了，它的作用就是增加对象的弱引用计数。函数最后返回mRefs，于是，弱指针对象的成员变量m_refs就指向目标对象的weakref_impl对象了。
RefBase::weakref_type* RefBase::createWeak(const void* id) const
{
    mRefs->incWeak(id);
    return mRefs;
}

//再来看析构函数：
template<typename T>
wp<T>::~wp()
{
    if (m_ptr) m_refs->decWeak(this);
}
//这里，弱指针在析构的时候，与强指针析构不一样，它直接就调用目标对象的weakref_impl对象的decWeak函数来减少弱引用计数了，当弱引用计数为0的时候，就会根据在目标对象的标志位（0、OBJECT_LIFETIME_WEAK或者OBJECT_LIFETIME_FOREVER）来决定是否要delete目标对象，前面我们已经介绍过了，这里就不再介绍了。

//分析到这里，弱指针还没介绍完，它最重要的特性我们还没有分析到。前面我们说过，弱指针的最大特点是它不能直接操作目标对象，这是怎么样做到的呢？秘密就在于弱指针类没有重载*和->操作符号，而强指针重载了这两个操作符号。但是，如果我们要操作目标对象，应该怎么办呢，这就要把弱指针升级为强指针了：
template<typename T>
sp<T> wp<T>::promote() const
{
    sp<T> result;
    if (m_ptr && m_refs->attemptIncStrong(&result)) {
        result.set_pointer(m_ptr);
    }
    return result;
}
//升级的方式就使用成员变量m_ptr和m_refs来"构造"一个强指针sp，升级成功与否就要看refs->attemptIncStrong函数的返回结果了
//这个函数的作用是试图增加目标对象的强引用计数，但是有可能会失败，失败的原因可能是因为目标对象已经被delete掉了，或者是其它的原因，下面会分析到
bool RefBase::weakref_type::attemptIncStrong(const void* id)
{
//前面我们在讨论强指针的时候说到，增加目标对象的强引用计数的同时，也会增加目标对象的弱引用计数，因此，函数在开始的地方首先就是调用incWeak函数来先增加目标对象的引用计数，如果后面试图增加目标对象的强引用计数失败时，会调用decWeak函数来回滚前面的incWeak操作
    incWeak(id);

//这里试图增加目标对象的强引用计数时，分两种情况讨论，
//情况1：此时目标对象正在被其它强指针引用，即它的强引用计数大于0，并且不等于INITIAL_STRONG_VALUE；
//情况2：此时目标对象没有被任何强指针引用，即它的强引用计数小于等于0，或者等于INITIAL_STRONG_VALUE。

    weakref_impl* const impl = static_cast<weakref_impl*>(this);
    int32_t curCount = impl->mStrong;

    ALOG_ASSERT(curCount >= 0,
            "attemptIncStrong called on %p after underflow", this);
//情况1比较简单，因为这时候说明目标对象一定存在，因此，是可以将这个弱指针提升为强指针的，在这种情况下，只要简单地增加目标对象的强引用计数值就行了
/*
 当我们在这里对目标对象的强引用计数执行加1操作时，要保证原子性，因为其它地方也有可能正在对这个目标对象的强引用计数执行加1的操作，前面我们一般是调用android_atomic_inc函数来完成，但是这里是通过调用android_atomic_cmpxchg函数来完成，android_atomic_cmpxchg函数是体系结构相关的函数，在提供了一些特殊的指令的体系结构上，调用android_atomic_cmpxchg函数来执行加1操作的效率会比调用android_atomic_inc函数更高一些。函数android_atomic_cmpxchg是在system/core/include/cutils/atomic.h文件中定义的一个宏：
int android_atomic_release_cas(int32_t oldvalue, int32_t newvalue,
        volatile int32_t* addr);
 
#define android_atomic_cmpxchg android_atomic_release_cas
它实际执行的函数是android_atomic_release_cas，这个函数的工作原理大概是这样的：如果它发现*addr == oldvalue，就会执行*addr = newvalue的操作，然后返回0，否则什么也不做，返回1。在我们讨论的这个场景中，oldvalue等于curCount，而newvalue等于curCount + 1，于是，在*addr == oldvalue的条件下，就相当于是对目标对象的强引用计数值增加了1。什么情况下*addr != oldvalue呢？在调用android_atomic_release_cas函数之前，oldvalue和值就是从地址addr读出来的，如果在执行android_atomic_release_cas函数的时候，有其它地方也对地址addr进行操作，那么就会有可能出现*addr != oldvalue的情况，这时候就说明其它地方也在操作目标对象的强引用计数了，因此，这里就不能执行增加目标对象的强引用计数的操作了，它必须要等到其它地方操作完目标对象的强引用计数之后再重新执行，这就是为什么要通过一个while循环来执行了。
*/
    while (curCount > 0 && curCount != INITIAL_STRONG_VALUE) {
        if (android_atomic_cmpxchg(curCount, curCount+1, &impl->mStrong) == 0) {
            break;
        }
        curCount = impl->mStrong;
    }
    //情况2比较复杂一点，因为这时候目标对象可能还存在，也可能不存了，这要根据实际情况来判断。
    if (curCount <= 0 || curCount == INITIAL_STRONG_VALUE) {
        bool allow;
        if (curCount == INITIAL_STRONG_VALUE) {
            //如果此时目标对象的强引用计数值等于INITIAL_STRONG_VALUE，说明此目标对象还从未被强指针引用过
//2.1 如果目标对象的生命周期只受强引用计数控制（它的标志位mFlags为0），而这时目标对象又还未被强指针引用过，它自然就不会被delete掉，因此，这时候可以判断出目标对象是存在的；
//2.2 如果目标对象的生命周期受弱引用计数控制（OBJECT_LIFETIME_WEAK），这时候由于目标对象正在被弱指针引用，因此，弱引用计数一定不为0，目标对象一定存在
//2.3 如果目标对象的生命周期不受引用计数控制（OBJECT_LIFETIME_FOREVER），这时候目标对象也是下在被弱指针引用，因此，目标对象的所有者必须保证这个目标对象还没有被delete掉，否则就会出问题了
//在后面两种场景下，因为目标对象的生命周期都是不受强引用计数控制的，而现在又要把弱指针提升为强指针，就需要进一步调用目标对象的onIncStrongAttempted来看看是否允许这种情况发生，这又该怎么理解呢？可以这样理解，目标对象的设计者可能本身就不希望这个对象被强指针引用，只能通过弱指针来引用它，因此，这里它就可以重载其父类的onIncStrongAttempted函数，然后返回false，这样就可以阻止弱指针都被提升为强指针。在RefBase类中，其成员函数onIncStrongAttempted默认是返回true的：
            allow = (impl->mFlags&OBJECT_LIFETIME_WEAK) != OBJECT_LIFETIME_WEAK
                || impl->mBase->onIncStrongAttempted(FIRST_INC_STRONG, id);
        } else {
//如果此时目标对象的强引用计数值小于等于0，那就说明该对象之前一定被强指针引用过，这时候就必须保证目标对象是被弱引用计数控制的（OBJECT_LIFETIME_WEAK），否则的话，目标对象就已经被delete了。同样，这里也要调用一下目标对象的onIncStrongAttempted成员函数，来询问一下目标对象在强引用计数值小于等于0的时候，是否允计将弱指针提升为强指针
            allow = (impl->mFlags&OBJECT_LIFETIME_WEAK) == OBJECT_LIFETIME_WEAK
                && impl->mBase->onIncStrongAttempted(FIRST_INC_STRONG, id);
        }
// 如果allow值为false，那么就说明不允计把这个弱指针提升为强指针，因此就返回false了，在返回之前，要先调用decWeak函数来减少目标对象的弱引用计数，因为函数的开头不管三七二十一，首先就调用了incWeak来增加目标对象的弱引用计数值。
        if (!allow) {
            decWeak(id);
            return false;
        }
        curCount = android_atomic_inc(&impl->mStrong);
 
        // If the strong reference count has already been incremented by
        // someone else, the implementor of onIncStrongAttempted() is holding
        // an unneeded reference.  So call onLastStrongRef() here to remove it.
        // (No, this is not pretty.)  Note that we MUST NOT do this if we
        // are in fact acquiring the first reference.
        if (curCount > 0 && curCount < INITIAL_STRONG_VALUE) {
            impl->mBase->onLastStrongRef(id);
        }
    }
 
    impl->addWeakRef(id);
    impl->addStrongRef(id);
 
#if PRINT_REFS
    LOGD("attemptIncStrong of %p from %p: cnt=%d\n", this, id, curCount);
#endif
//函数attemptIncStrong的主体逻辑大概就是这样了，比较复杂，读者要细细体会一下。函数的最后，如果此弱指针是允计提升为强指针的，并且此目标对象是第一次被强指针引用，还需要调整一下目标对象的强引用计数值：
    if (curCount == INITIAL_STRONG_VALUE) {
        android_atomic_add(-INITIAL_STRONG_VALUE, &impl->mStrong);
        impl->mBase->onFirstRef();
    }
 
    return true;
}









