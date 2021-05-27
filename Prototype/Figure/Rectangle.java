package prototype.e1;

public class Rectangle extends Figure {
    String label;

    public Rectangle(String label) {
        this.label = label;
    }

    @Override
    public void draw() {
        System.out.printf("Rectangle(%s)\n", label);
    }
}
