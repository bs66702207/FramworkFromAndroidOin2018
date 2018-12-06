import java.lang.ref.WeakReference;

/**
 * @author wison
 */
public class TestWeakReference1 {

	public static void main(String[] args) {

		Car car = new Car(22000,"silver");
		WeakReference<Car> weakCar = new WeakReference<Car>(car);
		int i = 0;
		while(true) {
			if(weakCar.get() != null) {
				i++;
				System.out.println("Object is alive for " + i + " loops - " + weakCar);
			} else {
				System.out.println("Object has been collected.");
				break;
			}
		}
	}

}

/**
在上例中, 程序运行一段时间后, 程序打印出"Object has been collected." 说明, weak reference指向的对象的被回收了.
值得注意的一点, 即使有car引用指向对象, 且car是一个strong reference, weak reference weakCar指向的对象仍然被回收了.
这是因为java的编译器在发现进入while循环之后, car已经没有被使用了, 所以进行了优化(将其置空?)
*/
