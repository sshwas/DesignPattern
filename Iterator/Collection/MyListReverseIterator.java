package iterator.e9;

public class MyListReverseIterator implements MyIterator {
    private MyList myList;
    private MyList.Node current;

    public MyListReverseIterator(MyList myList) {
        this.myList = myList;
        this.current = myList.dummy.prev;
    }

    @Override
    public int getNext() {
        int r = current.data;
        current = current.prev;
        return r;
    }

    @Override
    public boolean isEnd() {
        return current == myList.dummy;
    }

    @Override
    public void remove() {
        current.next = current.next.next;
        current.next.prev = current;
    }
}