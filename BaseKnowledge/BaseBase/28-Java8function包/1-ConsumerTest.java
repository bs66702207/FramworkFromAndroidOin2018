import java.util.function.Consumer;

class FSM {

	FSMImpl _owner;

	public FSM(FSMImpl owner) {
		_owner = owner;
	}

	public void function1() {
		_owner.function1();
	}

}

class FSMImpl {

	public void function1() {
		System.out.println("function1");
	}

	public void enclose(Consumer<FSM> transition, FSM core) {
		transition.accept(core);
	}
}

class ConsumerTest
{

	public static void main(String[] args) {
		FSMImpl mCore = new FSMImpl();
		FSM fsm = new FSM(mCore);
		mCore.enclose(FSM::function1, fsm);
	}

}
