package command.e3;

public abstract class Figure implements Cloneable {

    public abstract void draw(int indent);

    @Override
    public Figure clone() throws CloneNotSupportedException {
        return (Figure)super.clone();
    }
}
