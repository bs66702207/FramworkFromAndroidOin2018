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






