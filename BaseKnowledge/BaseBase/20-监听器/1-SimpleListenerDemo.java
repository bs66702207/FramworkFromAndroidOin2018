/**
（1）事件：用户对组件的一个操作，称之为一个事件
（2）事件源：发生事件的组件就是事件源
（3）事件监听器（处理器）：监听并负责处理事件的方法

SimpleListenerDemo简化了模型，仅仅包含事件源与监听器，完整的模式见FullListenerDemo
*/

//事件监听器，事件处理器
interface IEventListener {
	void onclickButton();//callback
}

//事件源：事件发生的地点
class EventSource {
	private IEventListener mEventListener;

	//注册监听器
	public void setEventListener(IEventListener arg) {
    	mEventListener = arg;
	}

	//触发事件，相当于APP里的button按下了
	public void EventHappened() {
    	mEventListener.onclickButton();
	}
}

class SimpleListenerDemo {
	public static void main(String[] args) {

		//事件源（被监听的对象)
		EventSource m1 = new EventSource();

		//监听器
		IEventListener mEventListener = new IEventListener() {

			@Override
			public void onclickButton() {
				// TODO Auto-generated method stub
				System.out.println("你点击了按钮");
			}
		};

		//注册监听器到事件源
		m1.setEventListener(mEventListener);
		m1.EventHappened();
	}
}  
