package composite.e5;

public class MyHashSet extends MyCollection {
    static final double A = 0.3758;
    MyObject[] a;
    int count, threshold;

    public MyHashSet() {
        this(32);
    }

    public MyHashSet(int size) {
        this.a = new MyObject[size];
        this.count = 0;
        this.threshold = (int) (this.a.length * 0.7);
    }

    private void expand() {
        int newSize = a.length * 2;
        MyHashSet newHashTable = new MyHashSet(newSize);
        for (int i = 0; i < a.length; ++i)
            if (a[i] != null) newHashTable.add(a[i]);
        this.a = newHashTable.a;
        this.threshold = newHashTable.threshold;
    }

    private int getStartIndex(MyObject value) { // 최초 저장할 위치 계산
        double fractionalPart = (value.hashValue() * A) % 1;
        return (int) (fractionalPart * this.a.length);
    }

    private static int getStepDistance(MyObject value) { // 충돌 발생한 경우 건너뛸 간격 계산
        final int[] STEPS = {3, 5, 7, 11, 13, 17, 19}; // 소수 크기 간격
        return STEPS[Math.abs(value.hashValue()) % STEPS.length];
    }

    @Override
    public void add(MyObject value) {
        int startIndex = getStartIndex(value);
        int step = getStepDistance(value);
        int collisionCount = 0;
        do {
            int index = (startIndex + collisionCount * step) % a.length;
            if (a[index] == null) {
                a[index] = value;
                this.count++;
                if (this.count >= this.threshold)
                    expand();
                return;
            } else if (a[index] == value)
                return;
            ++collisionCount;
        } while (collisionCount < a.length);
    }

    @Override
    public boolean contains(MyObject value) {
        int startIndex = getStartIndex(value);
        int step = getStepDistance(value);
        int collisionCount = 0;
        do {
            int index = (startIndex + collisionCount * step) % a.length;
            if (a[index] == null)
                return false;
            else if (a[index].equals(value))
                return true;
            ++collisionCount;
        } while (collisionCount < a.length);
        return false;
    }

    private class MyHashSetIterator implements MyIterator {
        private int current;

        public MyHashSetIterator() {
            current = -1;
            next();
        }

        private void next() {
            ++current;
            while (current < a.length && a[current] == null)
                ++current;
        }

        @Override
        public MyObject getNext() {
            MyObject r = a[current];
            next();
            return r;
        }

        @Override
        public boolean isEnd() {
            return current >= a.length;
        }
    }

    @Override
    public MyIterator getIterator() {
        return new MyHashSetIterator();
    }
}
