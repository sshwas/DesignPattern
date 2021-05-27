package command.e3;

public class Line extends Figure {
    String label;

    public Line(String label) {
        this.label = label;
    }

    @Override
    public void draw(int indent) {
        String padding = "  ".repeat(indent);
        System.out.printf("%sLine(%s)\n", padding, label);
    }
}
