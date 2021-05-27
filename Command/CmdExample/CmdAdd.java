package command.e3;

import java.util.List;

class CmdAdd implements Command {
    List<Figure> figures;
    Figure figure;
    int index;

    CmdAdd(List<Figure> figures, Figure figure) {
        this.figures = figures;
        this.figure = figure;
    }

    @Override
    public void execute() {
        figures.add(figure);
        index = figures.size() - 1;
    }

    @Override
    public void undo() {
        figures.remove(index);
    }
};