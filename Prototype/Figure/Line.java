package prototype.e1;

public class Line extends Figure {
    String label;

    public Line(String label) {
        this.label = label;
    }

    @Override
    public void draw() {
        System.out.printf("Line(%s)\n", label);
    }
}
