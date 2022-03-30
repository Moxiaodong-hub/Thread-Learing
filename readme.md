# Linux多线程

# 一、线程基本控制

## 1.打印线程和进程

## 2.创建线程

## 3.主线程

## 4.线程的退出

### （1）return方式退出

### （2）pthread_exit方式退出

### （3）exit方式退出

 这种方式会导致祝线程退出，导致其他线程也跟着退出

## 5.线程连接

pthread_join

线程连接时，发起连接的线程会进入阻塞状态，知道被连接的线程退出结束；

被连接的线程会进入分离状态。

线程可以通过pthread_detach自我分离，已经进入分离状态的线程不能被连接。

## 6.线程取消

### （1）取消函数

pthread_cancel（）

### （2）取消状态

使能取消  不使能取消

### （3）取消类型

立即取消   延时取消  默认是立即取消

## 7.线程通信

**函数：int pthread_kill(pthread_t thread, int sig)**

pthread_kill可不是kill，而是向线程发送signal。还记得signal吗，大部分signal的默认动作是终止进程的运行，所以，我们才要用signal()去抓信号并加上处理函数。如果线程代码内不做处理，则按照信号默认的行为影响整个进程，也就是说，如果你给一个线程发送了SIGQUIT，但线程却没有实现signal处理函数，则整个进程退出。pthread_kill(threadid, SIGKILL)也一样，杀死整个进程。
如果要获得正确的行为，就需要在线程内实现signal(SIGKILL,sig_handler)了。
如果int sig是0呢，这是一个保留信号，一个作用是用来判断线程是不是还活着。

**返回值：**
线程不存在：ESRCH

信号不合法：EINVAL

## 8.线程通信处理

**函数名：int sigaction(int signum, const struct sigaction *act, struct sigaction oldact)***

**参数：**

signum，信号的名字

act，结构体，主要成员为sa_mask （信号集），sa_handler;

oldact，传出旧的处理方式，指针非空, 则返回该信号的上一个动作.

int sigemptyset(sigset_t set)；
-清空信号集

int sigfillset(sigset_t set)；
-将所有信号加入信号集

int sigaddset(sigset_t set, int signum)；
-增加一个信号到信号集

int sigdelset(sigset_t set,int signum)；
-删除一个信号到信号集

## 9.线程清理

**函数1： pthread_cleanup_push（）参数1，清理函数名；参数2，清理函数参数**

压入栈，如果线程被取消会执行，当执行pop参数非0时会执行，按照先进后出顺序

**函数2: pthread_cleanup_pop（）参数1，实数**

执行pop时（参数非0），清理函数会执行。

# 二、线程的同步

## 1.互斥量

**互斥量锁的是同一进程中不同线程的共享资源**

**函数：**

pthread_mutex_t ：声明变量；

pthread_mutex_init：初始化 参数1变量名 参数2 NULL；

pthread_mutex_lock： 上锁；

pthread_mutex_unlock：解锁；

**上锁后，别的线程如果二次上锁会导致线程堵塞**

## 2.读写锁

**读写锁和互斥量是相似的，读写锁有三种状态：读锁、写锁、不加锁**

**函数：**

pthread_rwlock_rdlock：别的线程还能读；

pthread_rwlock_wrlock：别的线程不能读，比读锁的优先级高

pthread_rwlock_unlock

pthread_rwlock_destory

## 3.条件变量

**条件变量是和互斥量配合使用**

**函数：**

pthread_cond_t 声明变量

pthread_cond_init 初始化函数

pthread_cond_signal 条件变量，得到此变量的线程开始执行

pthread_cond_wait 参数1条件变量（等待条件变量），参数2互斥量

pthread_cond_destroy

# 三、线程的高级控制

## 1.一次性初始化

**很多变量必须初始化而且必须初始化一次，这是需要用一次性初始化**

**底层通过互斥量和条件变量来实现，三种状态0（未执行）1（正在执行）2（执行完成）**

**函数**：

pthread_once_t 声明变量 变量初始值PTHREAD_ONCE_INIT（0）

pthread_once（）参数1 变量名 参数2 初始化函数

## 2.分离属性

**初始化线程的时候，第二个参数可以设置属性 attr是属性的意思**

**函数：**

pthread_attr_t 声明变量

pthread_attr_init 初始化变量

pthread_attr_setdetachstate（）变量1 变量名，变量2（PTHREAD_CREATE_DETACHED，      PTHREAD_CREATE_JOINABLE

pthread_attr_getdetachstate（）获取分离状态属性

pthread_attr_destroy（）销毁

## 3.线程栈的属性

**对于进程来说，栈的大小是固定且有限的。如果一个进程中有很多线程，会导致线程栈累计超过可用的虚拟地址空间，这个时候需要减少线程默认栈的大小**

**可以修改栈的大小和地址，一般情况置修改栈的大小**

**函数：**

pthread_arrt_setstacksize（）参数1 变量名， 参数2 栈大小

pthread_attr_getstacksize（）参数1 变量名， 参数2 存储变量

**并不是每个系统都支持因此需要检查宏**

```cpp
#ifdef _POSIX_THREAD_ATTR_STACKSIZE
**
#endif
```

## 4.线程同步属性

### 1.互斥量属性

### 2.读写锁属性

### 3.条件变量属性

## 5.线程的私有数据

**程序设计中有种变量，每个线程都能访问，看起来像是全局变量。但没成对这个变量的访问相互不受影响**

**函数：**

thread_key_t声明变量

thread_key_create（）创建私有数据 变量1变量名，变量2析构函数可以为NULL

pthread_setspecific（）设置值 变量1 变量名 变量2 绑定的值（可以是变量）

pthread_getspecific（）查询值 变量1 变量名

## 6.线程与fork

**线程中调用fork时会把父线程中的所有参数都复制一份**，**这样会导致如果存在锁也会被复制且不能解锁，形成死锁，因此需要解决这种问题**

**函数：**

pthread_atfork() 参数1 执行fork前执行的函数， 参数2 进入父进程前执行的函数， 参数3 进入子进程时执行的函数。

**在执行fork前进行加锁，如果之前被加锁了，这时会等待解锁，否则加锁。进入父进程前解锁，进入子进程前解锁，这样就确保都是解锁状态**