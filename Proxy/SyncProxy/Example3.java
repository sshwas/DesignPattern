package proxy.e3;

import java.util.ArrayList;
import java.util.List;

public class Example3 {

    static void work(MyList list) {
        for (int i=0; i < 1000; ++i) {
            list.insertAt(0, new MyInt(999));
            list.removeAt(0);
        }
    }

    static void add(MyList list, int count) {
        for (int i = 0; i < count; ++i)
            list.add(new MyInt(i));
    }

    static void print(MyList list) {
        System.out.printf("Count: %d\n", list.getCount());
        for (int i = 0; i < list.getCount(); ++i)
            System.out.printf("%s ", list.getAt(i));
        System.out.println();
    }

    static void doSomething(MyList list) throws Exception {
        List<Thread> threads = new ArrayList<>();
        add(list, 100);
        for (int i = 0; i < 100; ++i) {
            Thread t = new Thread(() -> work(list));
            t.start();
            threads.add(t);
        }
        for (Thread t: threads)
            t.join();
        print(list);
    }

    public static void main(String[] args) throws Exception {
        doSomething(new MyRWSynchronizedList(new MyArrayList()));
        doSomething(new MyRWSynchronizedList(new MyLinkedList()));
    }
}