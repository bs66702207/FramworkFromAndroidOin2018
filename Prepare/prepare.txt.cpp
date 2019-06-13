//1 asep
//1.1开发elf
新增两个section
.page_hash: 对ELF文件的代码段和数据段进行hash计算，计算单位为一页4K
.page_hash_sig: 将.page_hash进行RSA非对称加密算法进行加密(签名)
//1.2kernel验证elf
//1.2.1读elf的签名验证
在load_elf_binary处将.page_hash和.page_hash_sig两个section内容读入，对.page_hash进行私钥签名校验，利用PCB task_struct新增成员dtv_hash来记录.page_hash的起始地址
无论校验成功或者失败都将释放和.page_hash_sig，如果校验失败则也释放.page_hash；否则在do_exit进程退出时，释放掉读入的.page_hash
//1.2.2缺页中断的hash验证
在__do_page_fault处，根据缺页中断的地址addr，来计算这一页的hash，跟对应的.page_hash进行比对是否相等

//1.3攻击实验
模拟nfs过滤器，在linux/net/sunrpc/svcsock.c修改数据，来验证是否可以“防止”攻击

//1.4bug8219321
第一个classes.dex会被加载运行，第二个classes.dex会被验证
if (mEntries.put(entryName, newEntry) != null) {//当hashmap里面已经有该key时返回的是这个key的value，如果没有该key返回的是null
    throw new ZipException("Duplicate entry name: " + entryName);
}

//2 擎天os
               ————————————   ————————————   ————————————   ————————————   ||  ———————————————
User          |application1| |application2| |application3| |application4|  || |Secure firmware|    EL0
               ————————————   ————————————   ————————————   ————————————   ||  ———————————————
     ----------------------------------------------------------------------||--------------------------
SVC ABT IRQ    ———————————————————————————   ————————————————————————————  ||  ———————————————
FIQ UND SYS   |            OS1            | |            OS2             | || |  Trusted OS   |    EL1
               ———————————————————————————   ————————————————————————————  ||  ———————————————
     ----------------------------------------------------------------------||--------------------------
               ——————————————————————————————————————————————————————————  || No Hypervisor in
Hyp           |                        Hypervisor                        | ||   Secure world       EL2
               ——————————————————————————————————————————————————————————  ||
     ----------------------------------------------------------------------||--------------------------
               ———————————————————————————————————————————————————————————————————————————————
Mon           |                                    Secure monitor                             |    EL3
               ———————————————————————————————————————————————————————————————————————————————

PS: 启动阶段，smc的中断向量的注册，从核Secondary CPUs配置，TZPC控制外设，TZASC控制DDR，TZMA控制片内RAM，AXI总线上增加NSBIT控制信号

//3 ext4
ext4文件系统有data block组成，通过超级块可以知道
data block一般是4K("block_size")，这些data block组成块组；
inode大小256字节("inode_size")；
每个块组的inode数量 "inodes_per_group"；
每个块组可以存放多少个块组描述符 "block_group_desc_group"；
根据inode X定位ext4文件系统镜像的具体偏移；
//3.1大的偏移 inode table的偏移，除以inodes_per_group
inode X所在的块组号block_number = (X - 1)/inodes_per_group
block_number在块组描述符表里的偏移(除法+取余)
  block数 = block_number / block_group_desc_group
  内部具体偏移字节 = block_number % block_group_desc_group
利用dd命令，bs=4096 skip=block数来查看第block_number的inode table的偏移为第 "N1" 个block
//3.2小的偏移 inode table里面的偏移，取余inodes_per_group
inode X 在inode表中的地址偏移inode_X_offset = (X - 1) % inodes_per_group * inode_size
从inode table 开始，skip多少个block: "N2" = inode_X_offset / 4096
进入block后偏移的字节数: "N3" = inode_X_offset % 4096
//3.3总的偏移
(N1 + N2) * 4096 + N3(字节)，用dd查看，

//3.4安全删除
使用sync或者discard+覆盖写

//4 fingerprint
AndroidM版本，keymaster访问keystore
1. 指纹HAL层初始化时，fp TA通过keymaster来获得一个密钥key
2. pre_enroll，输入完PIN密码，CA和fp TA会产生一个challenge
3. pre_enroll之后，enroll之前，gatekeeper会产生token，
token {
    challenge
    timestamp
    hamc
}
4. enroll，CA do_enroll调用到fp TA，先验证token->challenge是否通过，token->timerstamp验证是否超时，key来计算token里面成员之后比对token->hamc
5. post_enroll，删除密码反初始化
6. token验证通过之后，正式开始enroll，hal层卡在sys节点上，等待手指按在sensor上产生中断，kernel sysfs_notify 该sys节点，hal层向fp TA发起enroll命令，
   TA侧SPI开始采集数据，并且将采集的结果返回给CA测，成功或者是失败，失败的原因等。
7. fp TA lib限制了采集次数
8. 解锁，由keyguard发起authenticate调用到fp TA，TA去采集指纹图像对比验证。

// 5 支付
1. 证书CA里面保存着发布者的公钥，目的利用"权威机构"来确认这个确实是发布者的公钥
2. 根证书的hash存储在QFPROM里，熔丝熔断(短接部位永久断开)后无法更改，这样就保证ROOT CA的合法性，ROOT CA里面的公钥可以去解出其他CA的里公钥或者验证其他image的合法性
3. RPMB存储SE机器的devinfo，用户PIN码，用户私钥，微信ATTK私钥, IFAA设备私钥
4. 支付宝IFAA，设备中预置IFAA证书，私钥保存在RPMB，公钥上传到服务器
4.1 注册时IFAA server收到注册请求后将deviceID，挑战字等信息发给APP，APP-> IFAA TA，IFAA TA会通过预置的IFAA证书里的公钥来确认这些信息，然后将deviceID，挑战字，识别结果私钥签名返回给IFAA server，IFAA server进行公钥验证。
4.2 支付流程类似，先验证证书，再进行业务。
5. 微信SOTER，基于Android Fingerprint和Keymaster(TEE)实现，接口统一，充分利用原生系统接口keystore
6. 比较:
不同点: IFAA意在构建互联网安全标准，可扩展性强，开发难度大；SOTER利用原生接口，实现生物识别功能，开发难度低
相同点: 都需要远程服务端的交互，而且验证等结果的确认都在服务端

//6 binder
1. IPC--驱动
    在IPC这一层可以使用C语言实现server、service_manager(简称sm)、client，比如有两个服务hello、goodbye，
3.1 注册服务
    hello通过add_service，binder驱动会为hello服务将创建一个binder_node节点存放在红黑树里，binder驱动会通知(sm固定handle=0)的sm，sm会在kernel里创建binder_ref，binder_ref->node指向hello服务的binder_node，binder_ref->desc=1，goodbye也是类似，sm自己会维护一张表svclist，里面记录hello服务{(.name="hello", .handle=desc=1), (.name="goodbye", .handle=desc=2)
3.2 获得服务
    client get_service(goodbye)，binder驱动通知到sm，sm在svclist根据goodbye找到其handle=2，sm在内核态根据handle=2找到sm的binder_ref->node指向goodbye binder_node，创建client进程的binder_ref，这个client的binder_ref->node等于sm的binder_ref->node，client的binder_ref->desc=1返回给client这个desc作为handle
3.3 使用服务
    client向handle=1发送数据(ioctl)，这个client的binder_ref->node指向goodbye的binder_node，binder_node->proc可以找到goodbye的进程，那么就可以将数据传递过去，goodbye根据收到的ptr/cookie来分辨client想使用哪个服务，调用相应的函数
3.4 回复消息
    回复数据的时候并没有handle来找到client，所以必定在某个地方记录了这个发送者client
    涉及到双向传输，BC_TRANSACTION/BR_TRANSACTION，传输栈TRANSACTION_STACK
client->server，client的传输栈，入A栈
transaction_stack {
    .freom = test_client
    .to_proc = test_server
    .to_thread = test_server
}

server收到BR_TRANSACTION，将上面的信息入B栈，同一个结构体
transaction_stack {
    .freom = test_client
    .to_proc = test_server
    .to_thread = test_server
}

server发BC_REPLY，从B栈中取出transaction_stack，得知需要回复的client是谁，出B栈出A栈 

2. RPC--BpBinder BBInder
2.1 发数据
对于addService/getService，对于mRemote指向一个JavaBinderProxy对象，它的mObject指向一个C++的BpBinder对象，这个BpBinder的mHandle=0
对于sayhello/sayhello_to，mRemote是一个JavaBinderProxy对象，它的mObject指向一个C++的BpBinder对象，这BpBinder的mHandle=1来自getService("hello")

mRemote->JavaBinderProxy{
    mObject->BpBinder(mHandle)
}

2.2 读数据
(1)addService->jni->C++，创建BBinder派生类JavaBBinder对象，其成员.mObject指向指向JAVA对象HelloService/GoodbyeService，这个对象会存入binder_node.cookie中
(2)server进程从驱动中读到数据后，将.cookie转换为BBinder对象，调用它的transact函数，就会调用到BBinder的onTransact函数，
调用它的transact函数
  ->调用到JavaBBinder的onTransact函数(c++)
      ->jni调用Binder派生类execTransact方法
            ->Binder派生类IHelloService.Stub中定义的onTransact函数(JAVA)
(3)IHelloService.Stub->onTransact，分析数据，选择调用sayhello/sayhello_to
(4)IPCThreadState实现底层的数据发送和接收，Parcel发呢个装数据
3. 服务层--平时写代码直接使用的

//7 RSA密钥生成步骤
第一步，随机选择两个不相等的质数p和q。
第二步，计算p和q的乘积n。
第三步，计算n的欧拉函数φ(n)。
第四步，随机选择一个整数e，条件是1< e < φ(n)，且e与φ(n) 互质。
第五步，计算e对于φ(n)的模反元素d。
第六步，将n和e封装成公钥，n和d封装成私钥。

1）公钥 (n,e) 对m加密
m的e次方 ≡ c (mod n)，计算得出c，将c发送出去
2）解密要用私钥(n,d)
c的d次方 ≡ m (mod n)，计算得出m=65

//8 摘要算法，通过加盐等进行一系列的按位与/或等操作算出来一个值










I started working in twenty thirteen. Four years safety experience. Two years power experience. My first job is yongxin shibo research and development center, my main contribution is porting hardware module cipher driver to our TEE os. My second job is smartisan technology company bsp department, my main contribution is the research of ext four safe delete and power feature core function coding. My recent work is chehejia company and responsible for Android car power managerment.
