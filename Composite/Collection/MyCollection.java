package composite.e5;

public abstract class MyCollection implements MyObject, Cloneable {
    public abstract void add(MyObject value);
    public abstract boolean contains(MyObject value);
    public abstract MyIterator getIterator();

    @Override
    public int hashValue() {
        int result = getClass().hashCode();
        MyIterator it = getIterator();
        while (!it.isEnd()) {
            MyObject value = it.getNext();
            if (value != null)
                result = (31 * result + value.hashValue()) & 0xFFFFFF;
        }
        return result;
    }

    @Override
    public boolean equals(MyObject obj) {
        if (this == obj) return true;
        if (obj == null) return false;
        if (getClass() != obj.getClass()) return false;
        MyCollection col = (MyCollection)obj;
        MyIterator it1 = this.getIterator();
        MyIterator it2 = col.getIterator();
        while (!it1.isEnd() && !it2.isEnd()) {
            MyObject o1 = it1.getNext();
            MyObject o2 = it2.getNext();
            if (o1 == o2) continue;
            if (o1 != null && o1.equals(o2)==false) return false;
        }
        return it1.isEnd() && it2.isEnd();
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append(getClass().getSimpleName()).append("( ");
        MyIterator it = getIterator();
        while (!it.isEnd()) {
            MyObject value = it.getNext();
            builder.append(value).append(' ');
        }
        builder.append(')');
        return builder.toString();
    }

    public void addAll(MyCollection col) {
        MyIterator it = col.getIterator();
        while (!it.isEnd())
            this.add(it.getNext());
    }

    @Override
    public MyCollection clone() throws CloneNotSupportedException {
        try {
            MyCollection col = this.getClass().getConstructor().newInstance();
            col.addAll(this);
            return col;
        } catch (Exception ex) {
            throw new CloneNotSupportedException(ex.getMessage());
        }
    }
    
    /*
    @Override
    public MyCollection clone() throws CloneNotSupportedException {
    	return (MyCollection)super.clone();
    }
    */
}
