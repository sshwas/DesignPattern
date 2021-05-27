package proxy.e3;

interface MyList {

    MyObject getAt(int index);
    void setAt(int index, MyObject value);
    void insertAt(int index, MyObject value);
    void removeAt(int index);
    int findIndex(MyObject value);
    int getCount();

    default void add(MyObject value) {
        insertAt(getCount(), value);
    }

    default void remove(MyObject value) {
        int index = findIndex(value);
        if (index == -1)
            return;
        removeAt(index);
    }
}