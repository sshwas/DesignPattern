package composite.e5;

public class MyInt implements MyObject {
    private int value;

    public MyInt(int value) {
        this.value = value;
    }

    @Override
    public boolean equals(MyObject obj) {
        if (this == obj) return true;
        if (obj == null) return false;
        if (getClass() != obj.getClass()) return false;
        return (value == ((MyInt)obj).value);
    }

    @Override
    public int hashValue() {
        return value;
    }

    @Override
    public String toString() {
        return String.format("MyInt(%d)", value);
    }
}
