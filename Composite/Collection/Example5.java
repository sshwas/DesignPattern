package composite.e5;

public class Example5 {

    static void addData(MyCollection col, int count) {
        for (int i = 0; i < count; ++i)
            col.add( i % 2 == 0 ? new MyInt(i) : new MyStr(i) );
    }

    static MyCollection createComposite(MyCollection col) throws CloneNotSupportedException {
        MyCollection c1 = col.clone(), c2 = col.clone(), c3 = col.clone();
        addData(c1, 3);
        addData(c2, 3);
        addData(c3, 3);
        c2.add(c1);
        c3.add(c2);
        return c3;
    }

    static void testComposite(MyCollection col) throws CloneNotSupportedException {
        MyCollection c1 = createComposite(col);
        MyCollection c2 = createComposite(col);

        System.out.println(c1.equals(c2));
        System.out.println(c1);
    }

    public static void main(String[] args) throws CloneNotSupportedException {
        testComposite(new MyArray());
        testComposite(new MyList());
        testComposite(new MyHashSet());
    }
}
