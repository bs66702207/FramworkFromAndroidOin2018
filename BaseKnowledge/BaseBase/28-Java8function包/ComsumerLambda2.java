import java.util.function.Consumer;

public class ComsumerLambda2 {

    public static void main(String[] args) {

        Foo f = new Foo();

        f.foo(new Consumer<Integer>() {
            @Override
            public void accept(Integer integer) {
                System.out.println(integer);
            }
        });

        Foo f2 = new Foo();
        f2.foo(integer -> System.out.println(integer));

        Foo f3 = new Foo();
        f3.foo(System.out::println);

    }

}

class Foo {

    private int[] data = new int[10];

    public Foo() {

        for (int i = 0; i < 10; i++) {
            data[i] = i;
        }
    }

    public void foo(Consumer<Integer> consumer) {
        for (int i : data)
            consumer.accept(i);
    }

}
