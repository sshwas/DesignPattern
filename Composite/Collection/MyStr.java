package composite.e5;

public class MyStr implements MyObject {
    private String value;

    public MyStr(String value) {
        this.value = value;
    }

    public MyStr(int value) {
        this.value = String.valueOf(value);
    }

    @Override
    public boolean equals(MyObject obj) {
        if (this == obj) return true;
        if (obj == null) return false;
        if (getClass() != obj.getClass()) return false;
        MyStr myString = (MyStr)obj;
        return (value == myString.value) ||
               (value != null && value.equals(myString.value));
    }

    @Override
    public int hashValue() {
        return value.hashCode();
    }

    @Override
    public String toString() {
        return String.format("MyStr(%s)", value);
    }
}
