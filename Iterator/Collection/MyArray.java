package iterator.e9;

import java.util.Arrays;

public class MyArray implements MyCollection {
    int[] data;
    int count;

    public MyArray() {
        this(8);
    }

    public MyArray(int size) {
        data = new int[size];
        count = 0;
    }

    private void expand() {
        data = Arrays.copyOf(data, data.length * 2);
    }

    @Override
    public void add(int value) {
        if (count == data.length) expand();
        data[count++] = value;
    }

    public int get(int index) {
        return data[index];
    }

    public int getCount() {
        return count;
    }

    @Override
    public MyIteratorFactory getIteratorFactory() {
        return new MyArrayIteratorFactory(this);
    }
}
