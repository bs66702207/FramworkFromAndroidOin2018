/*
 * 事件
 */
interface IEvent {
	void setEventListener(IEventListener arg);
	boolean ClickButton();
	boolean MoveMouse();
}

/*
 * 事件监听器，调用事件处理器
 */
interface IEventListener {
	void doEvent(IEvent arg);//callback
}

/*
 * 事件源1：事件发生的地点
 */
class EventSource implements IEvent{
	private IEventListener mEventListener;
	boolean button;
	boolean mouse;
	
	//注册监听器
	@Override
	public void setEventListener(IEventListener arg){
		mEventListener = arg;
	}
	
	//触发事件
	public void mouseEventHappened(){//鼠标移动事件发生了！
		mouse = true;
		mEventListener.doEvent(this);
	}
 
	@Override
	public boolean ClickButton() {
		// TODO Auto-generated method stub
		return button;
		
	}
 
	@Override
	public boolean MoveMouse() {
		// TODO Auto-generated method stub
		return mouse;
	}
 
}

/*
 * 事件源2：事件发生的地点
 */
class EventSource2 implements IEvent {
	private IEventListener ml;
	boolean button;
	boolean mouse;
 
	@Override
	public void setEventListener(IEventListener arg) {
		ml = arg;
	}
 
	@Override
	public boolean ClickButton() {
		// TODO Auto-generated method stub
		return button;
	}
 
	@Override
	public boolean MoveMouse() {
		// TODO Auto-generated method stub
		return mouse;
	}
 
	// 触发事件
	public void buttonEventHappened() {//按钮按下事件发生了！
		button = true;
		ml.doEvent(this);
	}
 
}

class FullListenerDemo {
	public static void main(String[] args) {
 
		// 事件源（被监听的对象）
		EventSource m1 = new EventSource();
		EventSource2 m2 = new EventSource2();
		// 监听器
		IEventListener mEventListener = new IEventListener() {
 
			@Override
			public void doEvent(IEvent arg) {
				if (true == arg.ClickButton()) {
					System.out.println("你点击了按钮");
				} else if(true == arg.MoveMouse()) {
					System.out.println("你移动了鼠标");
				}
			}
		};
 
		// 注册监听器到事件源
		m1.setEventListener(mEventListener);
		m1.mouseEventHappened();
		
		// 注册监听器到事件源
		m2.setEventListener(mEventListener);
		m2.buttonEventHappened();
	}
}
