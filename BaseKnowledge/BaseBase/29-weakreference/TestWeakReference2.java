import java.lang.ref.WeakReference;

/**
 * @author wison
 */
public class TestWeakReference2 {

	public static void main(String[] args) {

		Car car = new Car(22000,"silver");
		WeakReference<Car> weakCar = new WeakReference<Car>(car);
		int i = 0;
		while(true) {
			System.out.println("here is the strong reference 'car' " + car);
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
weak reference指向的object就不会被回收了. 因为还有一个strong reference car 指向它.
WeakReference的一个特点是它何时被回收是不可确定的, 因为这是由GC运行的不确定性所确定的. 
所以, 一般用weak reference引用的对象是有价值被cache, 而且很容易被重新被构建, 且很消耗内存的对象.
*/
