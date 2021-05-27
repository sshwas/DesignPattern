package iterator.e9;

class MyArrayReverseIterator implements MyIterator {
    private MyArray myArray;
    private int current;

    public MyArrayReverseIterator(MyArray myArray) {
        this.myArray = myArray;
        this.current = myArray.count - 1;
    }

    @Override
    public int getNext() {
        return myArray.data[current--];
    }

    @Override
    public boolean isEnd() {
        return current < 0;
    }

    @Override
    public void remove() {
        --myArray.count;
        for (int i = current + 1; i < myArray.count; ++i)
            myArray.data[i] = myArray.data[i + 1];
    }
}