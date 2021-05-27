package iterator.e9;

public class MyListIteratorFactory implements MyIteratorFactory {
    private MyList myList;

    public MyListIteratorFactory(MyList myList) {
        this.myList = myList;
    }

    @Override
    public MyIterator getIterator() {
        return new MyListIterator(myList);
    }

    @Override
    public MyIterator getReverseIterator() {
        return new MyListReverseIterator(myList);
    }
}
