package iterator.e9;

import java.util.function.Predicate;

public class Example9 {

    static void add(MyCollection col, int count) {
        for (int i = 0; i < count; ++i)
            col.add(i);
    }

    static void print(MyIterator it) {
        while (!it.isEnd())
            System.out.printf("%d ", it.getNext());
        System.out.println();
    }

    // predicate를 만족하는 항목들을 제거한다
    static void remove(MyIterator it, Predicate<Integer> predicate) {
        while (!it.isEnd())
            if (predicate.test(it.getNext()))
                it.remove();
    }

    static void doSomething(MyCollection col, int count) {
        MyIteratorFactory factory = col.getIteratorFactory();

        add(col, 10);
        remove(factory.getIterator(), value -> value < 5); // 5 미만 제거
        print(factory.getIterator());
        remove(factory.getIterator(), value -> value >= 5); // 5 이상 제거

        add(col, 10);
        remove(factory.getReverseIterator(), value -> value < 5);
        print(factory.getReverseIterator());
        remove(factory.getReverseIterator(), value -> value >= 5);

        add(col, 10);
        remove(factory.getIterator(), value -> value % 2 == 0); // 짝수 제거
        print(factory.getIterator());
        remove(factory.getIterator(), value -> value % 2 == 1); // 홀수 제거

        add(col, 10);
        remove(factory.getReverseIterator(), value -> value % 2 == 1);
        print(factory.getReverseIterator());
        remove(factory.getReverseIterator(), value -> value % 2 == 0);
        print(factory.getReverseIterator());
}

    public static void main(String[] args) {
        doSomething(new MyArray(), 10);
        doSomething(new MyList(), 10);
    }
}
