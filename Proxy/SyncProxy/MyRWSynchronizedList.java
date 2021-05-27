package proxy.e3;

import java.util.concurrent.locks.ReentrantReadWriteLock;

class MyRWSynchronizedList implements MyList {
    MyList list;
    ReentrantReadWriteLock lock = new ReentrantReadWriteLock();

    MyRWSynchronizedList(MyList list) {
        this.list = list;
    }

    @Override
    public int getCount() {
        lock.readLock().lock();
        try {
            return list.getCount();
        } finally {
            lock.readLock().unlock();
        }
    }

    @Override
    public MyObject getAt(int index) {
        lock.readLock().lock();
        try {
            return list.getAt(index);
        } finally {
            lock.readLock().unlock();
        }
    }

    @Override
    public void setAt(int index, MyObject data) {
        lock.writeLock().lock();
        try {
            list.setAt(index, data);
        } finally {
            lock.writeLock().unlock();
        }
    }

    @Override
    public void insertAt(int index, MyObject data) {
        lock.writeLock().lock();
        try {
            list.insertAt(index, data);
        } finally {
            lock.writeLock().unlock();
        }
    }

    @Override
    public void removeAt(int index) {
        lock.writeLock().lock();
        try {
            list.removeAt(index);
        } finally {
            lock.writeLock().unlock();
        }
    }

    @Override
    public int findIndex(MyObject data) {
        lock.readLock().lock();
        try {
            return list.findIndex(data);
        } finally {
            lock.readLock().unlock();
        }
    }
}