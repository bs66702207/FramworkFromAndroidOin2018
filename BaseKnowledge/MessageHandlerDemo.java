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


