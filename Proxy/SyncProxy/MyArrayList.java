package proxy.e3;

import java.util.Arrays;

class MyArrayList implements MyList {
    private MyObject[] data;
    private int count;
    private int size;

    public MyArrayList() {
        this(10);
    }

    public MyArrayList(int size) {
        this.count = 0;
        this.size = size;
        this.data = new MyObject[size];
    }

    private void expand() {
        size = data.length * 2;
        data = Arrays.copyOf(data, size);
    }

    @Override
    public MyObject getAt(int index) {
        return data[index];
    }

    @Override
    public void setAt(int index, MyObject value) {
        data[index] = value;
    }

    @Override
    public void insertAt(int index, MyObject value) {
        if (count >= size)
            expand();
        for (int i = count - 1; i >= index; --i)
            data[i + 1] = data[i];
        data[index] = value;
        count++;
    }

    @Override
    public void removeAt(int index) {
        for (int i = index; i < count - 1; ++i)
            data[i] = data[i + 1];
        count--;
    }

    @Override
    public int findIndex(MyObject value) {
        for (int i = 0; i < count; ++i)
            if (value.equals(data[i]))
                return i;
        return -1;
    }

    @Override
    public int getCount() {
        return count;
    }


}