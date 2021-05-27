package iterator.e9;

public class MyListIterator implements MyIterator {
    protected MyList myList;
    protected MyList.Node current;

    public MyListIterator(MyList myList) {
        this.myList = myList;
        this.current = myList.dummy.next;
    }

    @Override
    public int getNext() {
        int r = current.data;
        current = current.next;
        return r;
    }

    @Override
    public boolean isEnd() {
        return current == myList.dummy;
    }

    @Override
    public void remove() {
        current.prev = current.prev.prev;
        current.prev.next = current;
    }

}