class AA {
	public String str = null;
	AA(String str) {
		this.str = str;
	}
}

class NullDemo {
	public static void main(String[] args) {
		AA a1 = new AA("helloworld!");
		AA b1 = a1;
		a1 = null;
		System.out.println("b1.str = " + b1.str);
		System.out.println("a1.str = " + a1.str);
	}
}
