package proxy.e3;

public class MyLinkedList implements MyList {
    private static class Node {
        private MyObject data;
        private Node prev, next;

        Node(MyObject data) {
            this.data = data;
        }
    }

    private Node dummy;
    private int count;

    public MyLinkedList() {
        dummy = new Node(null);
        dummy.prev = dummy.next = dummy;
        count = 0;
    }

    private Node getNode(int index) {
        Node node = dummy;
        if (index < count / 2)
            for (int i = 0; i <= index; ++i)
                node = node.next;
        else
            for (int i = count-1; i >= index; --i)
                node = node.prev;
        return node;
    }

    @Override
    public MyObject getAt(int index) {
        return getNode(index).data;
    }

    @Override
    public void setAt(int index, MyObject value) {
        getNode(index).data = value;
    }

    @Override
    public void insertAt(int index, MyObject value) {
        Node newNode = new Node(value);
        Node node = getNode(index);
        newNode.next = node;
        newNode.prev = node.prev;
        node.prev.next = newNode;
        node.prev = newNode;
        ++count;
    }

    @Override
    public void removeAt(int index) {
        Node node = getNode(index);
        node.prev.next = node.next;
        node.next.prev = node.prev;
        --count;
    }

    @Override
    public int findIndex(MyObject value) {
        int index;
        Node node = dummy.next;
        for (index = 0; index < count; ++index) {
            if (value.equals(node.data)) break;
            node = node.next;
        }
        return index;
    }

    @Override
    public int getCount() {
        return count;
    }
}
