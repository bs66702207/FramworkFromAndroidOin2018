import java.util.function.Consumer;

class ConsumerDemo {

	public void function(boolean on) {
		System.out.println("function: " + on);
	}

	public <T> void enclose(Consumer<T> handler, T object) {
		handler.accept(object);
	}

    public void useEnclose() {
        enclose(on -> this.function(on), true);
    }

}

class ComsumerLambda {

    public static void main(String[] args) {
        ConsumerDemo mCore = new ConsumerDemo();
        mCore.useEnclose();
        mCore.enclose(on->mCore.function(on), false);
    }

}
