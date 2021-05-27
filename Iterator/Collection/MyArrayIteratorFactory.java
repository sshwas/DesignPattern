package iterator.e9;

public class MyArrayIteratorFactory implements MyIteratorFactory {
    private MyArray myArray;

    public MyArrayIteratorFactory(MyArray myArray) {
        this.myArray = myArray;
    }

    @Override
    public MyIterator getIterator() {
        return new MyArrayIterator(myArray);
    }

    @Override
    public MyIterator getReverseIterator() {
        return new MyArrayReverseIterator(myArray);
    }
}
