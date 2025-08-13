# 这个文档整理了一些常见的C++面试题

### final和override的作用?
### final为什么能提高代码执行效率?
since(c++11).Specifies that a virtual function cannot be overridden in a derived class, or that a class cannot be derived from.


### static的三种作用?
### thread_local变量作用?
### 存放位置?生命周期?
### 一个变量可以既是const又是volatile吗?
### NULL和nullptr区别?
### 为什么要引入nullptr?
### 为什么noexcept能提高性能?
### delete[]是怎样知道数组长度的?
### new，placement new，operator new的区别?
### 怎么在把对象new在栈上?
### __cdecl和__stdcall区别?
### 重载类的delete运算符，delete这个对象的时候会发生什么?
### 函数调用压栈流程?
### 声明和定义的作用，从编译角度说明?
### 现代大部分编程语言都没有头文件，c++为什么有头文件?
### 头文件和模块的优劣比较?
### #include和前置声明的区别?
### c++11为什么引入枚举类?
### 程序是从main 函数开始执行的吗?
### 虚函数怎么实现的，性能?真的更慢吗?
### 构造函数、析构函数、重载运算符函数可以是虚函数吗?
### 类成员函数模板可以是虚函数吗?
### 成员函数指针和普通函数指针区别?
### 各种变量存放在虚拟内存的哪个分区?
### 对象的内存模型?
### 发生继承时候的对象内存模型?
### 什么是标准布局类型和trivial类型?有什么用?
### 什么是类型擦除?有哪些实现方式?
### 什么是多态?静态和动态多态的实现原理?
### inline的作用?优劣?为什么不会引发符号重定义错误?inline用作内联展开这层含义的时候，构造函数、析构函数、虚函数可以被inline修饰吗?
### 可以获取inline函数的指针吗?
### static inline和extern inline含义?
### malloc和new区别?
### malloc实现原理?
### free后，内存被立即释放了吗?
### 谈谈lambda函数?
### union和struct和class的区别?
### 什么是零三五原则?
### C++可调用类型有哪些?
### 为什么需要把析构函数定义为虚函数?
### 具有类成员和基类的类，在实例化和销毁的时候，构造函数和析构函数的调用顺序?
### 指针和引用的区别?
### 符号重定义的解决方法有哪些?
### 四种指针类型转换的区别? static_cast, dynamic_cast, reinterpret_cast, const_cast
### 知道什么是RVO吗?
### RTTI的实现原理?
### extern C的作用?
### 可以在运行时访问private成员吗?
### C++编译流程?
### 动态库和静态库的区别?
### 知道动态库延迟加载优化吗?
### 智能指针是什么?
### 几种智能指针的区别?
### 四种智能指针的简单实现?
### 什么是左值和右值?它们是C++11才有的吗?
### string literal是左值还是右值?
### i++和++i是左值还是右值?
### 什么是左右值引用?和左右值有关系吗?
### 右值引用适合什么场景下用?
### 基本类型的长度?
### 内存对齐规则?
### 为什么要内存对齐?应用场景?
### 通过指针访问数组，系统是如何知道指针越界的?
### 断言是什么?断言和条件语句的优劣?
### 继承和组合的优劣?
### 可变参数函数的实现原理?
### tuple的实现原理?
### tuple可以替代结构体吗?
### any可以替代void*吗?
### any采取了什么样的优化方案?
### 使用场景有哪些?
### variant可以替代union吗?
### optional的使用场景有哪些?
### any和variant性能差异?
### sizeof(function)大小是多少?
### function的实现方式?
### 零拷贝原则是什么?
### forward和move的作用?
### 有了move，为什么还要引入forward?
完美转发(perfect forwarding)
### 引用折叠规则是什么?
### 万能引用是什么?
### constexpr if和SFINEA比较?
### type traits作用和实现方式?
### 模板的全特化和偏特化是什么?
### 可变参数模板有哪些应用场景?
### 模板的匹配规则是什么?
### CRTP是什么?
### 顺序容器和关联容器有什么区别?
### 容器的内存释放原则和拷贝策略?
### 线程安全?
### 迭代器和指针的区别?
### 什么是迭代器失效?++iterator和iterator++哪个效率高?
### string采用了什么优化手段?
### string::data()和string::c_str()的区别?
### string可被继承吗?array和vector的区别?
### vector内存分配策略?怎么提高效率?
### capacity()和size()有什么区别?
### vector::erase()和std::remove()的区别?
### vector中reserve()和resize()的区别?
### vector<bool>是数组吗?
### 和bitset区别?
### vector<char>和string的区别?
### list和vector区别?
### list::size()，list::empty()时间复杂度?
### forward_list和list区别?
### deque数据结构是什么?
### 适配器是什么?
### 关联容器有哪些?它们的区别是什么?
### vector中at()和operator[]有什么区别?
### map中at()和operator[]有什么区别?
### map::operator[] 和 map::insert的区别?
### vector::swap()和vector::operator=的区别?
### push_back()和emplace_back()区别?
### clear()会释放内存吗?
### 互斥锁和自旋锁区别?
### C++标准库提供了哪些解决死锁的方案?
### 线程和协程的区别?为什么引入协程?什么是有栈协程和无栈协程?哪种更好?
### 条件变量的实现原理?
### 进行条件判断的时候能用if替代while吗?
### 条件变量和信号量区别?
### 无锁编程的memory order有哪些?
### 为什么要在父线程执行detach()或者join()?
一般父线程会通过std::thread的构造创建子线程，然后子线程会开始。如果父线程希望所有子线程都执行完了(退出后)再退出，那么可以通过join()，来等待所以子线程执行完并退出。
### async、promise、packaged_task可互相替代吗?
### 什么是无锁编程?




### SNMP用途?
### SMTP，IMAP，POP3的异同?
### SSH和TELNET的异同?SSH和FTP的异同?
### FTPS和HTTPS的异同?
### PPPoE 与 DHCP 的异同?DHCP和移动IP的异同?
### DNS协议原理?根域名服务器有多少个?
### HTTP/1.0，HTTP/1.1，HTTP/2.0的区别?
### HTTP请求报文格式是怎样的? HTTP响应报文格式是怎样的?状态码是什么?HTTP长连接是什么?HTTP强缓存和协商缓存是什么?HTTP请求方法GET和POST的异同?HTTPS流程?
### WebSocket和HTTPS的异同?应用层粘包的解决办法?
### TCP为什么要三次握手?四次挥手?
### TIME-WAIT 等待的时间为什么是 2MSL?
### TCP半连接队列、全连接队列是什么?
### TCP报文标识有哪些?
### TCP初始化序列号为什么是随机数?
### TCP可靠传输是怎么实现的?
### TCP和UDP能否同时使用相同端口号?
### 既然IP层有分片机制，为什么还要在TCP层分段?
### TCP的Keep-Alive和HTTP的Keep-Alive区别?
### 端口映射、NAT映射、DMZ映射、内网穿透的区别?
### 防火墙和WAF的异同?
### MPLS VPN、IPsec VPN，TLS VPN的区别?
### IPv4有哪些特殊的地址?
### IPv4地址有哪些分类?
### 组播目的IP含义是什么?
### 单播、多播、广播、任播是什么?
### 主机路由，网络路由，聚合路由，默认路由区别?
### ICMP协议是什么?
### ping本机地址或者回环地址，是否走网卡?
### ARP协议的的作用?
### 为什么要在网络层进行报文分片?
### VLAN和VPN的区别?
### CSMA/CD半双工通信和全双工通信的区别?
### PPPoe和PPP区别?双绞线、同轴电缆、光纤的区别?光猫、路由的区别?
### 路由器上console口、WAN口、LAN口的作用?
### 有线组网方式有哪些?无线组网方式有哪些?
### Qos是什么?什么是数字证书，数字签名?
### 怎么通过数字签名实现加密通信?
### epoll的原理?
### RPC和RESTful的区别?
### listen，connect，accpet，close的作用?