package command.e3;

import java.util.Collections;
import java.util.List;

public class CmdGroup implements Command {
    List<Figure> figures;
    List<Integer> indexes;
    FigureGroup group;
    int index;

    public CmdGroup(List<Figure> figures, List<Integer> indexes) {
        this.figures = figures;
        this.indexes = indexes;
    }

    @Override
    public void execute() {
        Collections.sort(indexes);
        group = new FigureGroup();
        for (int index : indexes)
            group.add(figures.get(index));
        figures.add(group);
        index = figures.size() - 1;
        for (int i = 0; i < group.getCount(); ++i)
            figures.remove(group.get(i));
    }

    @Override
    public void undo() {
        for (int i = 0; i < indexes.size(); ++i)
            figures.add(indexes.get(i), group.get(i));
        figures.remove(index);
    }
}
