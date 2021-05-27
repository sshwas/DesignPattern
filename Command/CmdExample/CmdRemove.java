package command.e3;

import java.util.List;

class CmdRemove implements Command {
    List<Figure> figures;
    int index;
    Figure figure;

    CmdRemove(List<Figure> figures, int index) {
        this.index = index;
        this.figures = figures;
    }

    @Override
    public void execute() {
        figure = figures.remove(index);
    }

    @Override
    public void undo() {
        figures.add(index, figure);
    }
};