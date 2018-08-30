//frameworks/base/core/java/android/os/Handler.java

//handler发消息方式：
//发送即时消息：

Message msg = new Message();
msg.what = 100;
handler.sendMessage(msg);

//延时5秒发送消息：
Message msg = new Message();
msg.what = 100;
handler.sendMessageDelayed(msg, 5000);

当执行handler.sengMessageDelayed后，需要取消消息的发送，可以执行handler.removeMessages(100).

//Android中Looper的quit方法和quitSafely方法
Looper是通过调用loop方法驱动着消息循环的进行: 从MessageQueue中阻塞式地取出一个消息，然后让Handler处理该消息，周而复始，loop方法是个死循环方法。
那如何终止消息循环呢？我们可以调用Looper的quit方法或quitSafely方法，二者稍有不同。
https://blog.csdn.net/iispring/article/details/47622705
通过观察以上源码我们可以发现:
    当我们调用Looper的quit方法时，实际上执行了MessageQueue中的removeAllMessagesLocked方法，该方法的作用是把MessageQueue消息池中所有的消息全部清空，无论是延迟消息（延迟消息是指通过sendMessageDelayed或通过postDelayed等方法发送的需要延迟执行的消息）还是非延迟消息。
    当我们调用Looper的quitSafely方法时，实际上执行了MessageQueue中的removeAllFutureMessagesLocked方法，通过名字就可以看出，该方法只会清空MessageQueue消息池中所有的延迟消息，并将消息池中所有的非延迟消息派发出去让Handler去处理，quitSafely相比于quit方法安全之处在于清空消息之前会派发所有的非延迟消息。
    无论是调用了quit方法还是quitSafely方法只会，Looper就不再接收新的消息。即在调用了Looper的quit或quitSafely方法之后，消息循环就终结了，这时候再通过Handler调用sendMessage或post等方法发送消息时均返回false，表示消息没有成功放入消息队列MessageQueue中，因为消息队列已经退出了。
    需要注意的是Looper的quit方法从API Level 1就存在了，但是Looper的quitSafely方法从API Level 18才添加进来。
