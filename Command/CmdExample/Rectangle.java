package command.e3;

public class Rectangle extends Figure {
    String label;

    public Rectangle(String label) {
        this.label = label;
    }

    @Override
    public void draw(int indent) {
        String padding = "  ".repeat(indent);
        System.out.printf("%sRectangle(%s)\n", padding, label);
    }
}
