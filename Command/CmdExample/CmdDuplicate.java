package command.e3;

import java.util.List;

class CmdDuplicate implements Command {
    List<Figure> figures;
    int index;

    CmdDuplicate(List<Figure> figures, int index) {
        this.figures = figures;
        this.index = index;
    }

    @Override
    public void execute() {
        try {
            Figure figure = figures.get(index);
            figures.add(figure.clone());
            index = figures.size() - 1;
        } catch (CloneNotSupportedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void undo() {
        figures.remove(index);
    }
}