import java.util.function.Consumer;

class FSMImpl {

	public void function1() {
		System.out.println("function1");
	}

	public void enclose(Consumer<FSMImpl> transition, FSMImpl core) {
		transition.accept(core);
	}

}

class EncloseTest {

    public static void main(String[] args) {
        FSMImpl mCore = new FSMImpl();
        mCore.enclose(FSMImpl::function1, mCore);
    }

}
