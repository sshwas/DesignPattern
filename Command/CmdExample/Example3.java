package command.e3;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class Example3 {

    static List<Figure> figures = new ArrayList<Figure>();
    static LinkedList<Command> undoStack = new LinkedList<Command>();
    static LinkedList<Command> redoStack = new LinkedList<Command>();

    static void drawFigures() {
        System.out.println();
        for (int i = 0; i < figures.size(); ++i) {
            System.out.printf("%d: ", i);
            figures.get(i).draw(0);
        }
        System.out.println();
    }

    static void execute(String cmd) {
        try {
            int index;
            Command command = null;
            String[] a = cmd.split(" +");
            switch (a[0].toLowerCase()) {
            case "rectangle":
                command = new CmdAdd(figures, new Rectangle(a[1]));
                break;
            case "line":
                command = new CmdAdd(figures, new Line(a[1]));
                break;
            case "remove":
                index = Integer.valueOf(a[1]);
                command = new CmdRemove(figures, index);
                break;
            case "duplicate":
                index = Integer.valueOf(a[1]);
                command = new CmdDuplicate(figures, index);
                break;
            case "group":
                List<Integer> indexes = new ArrayList<>();
                for (int i = 1; i < a.length; ++i)
                    indexes.add(Integer.valueOf(a[i]));
                command = new CmdGroup(figures, indexes);
                break;
            case "undo":
                command = undoStack.pop();
                redoStack.push(command);
                command.undo();
                command = null;
                break;
            case "redo":
                command = redoStack.pop();
                break;
            case "quit":
                System.exit(0);
                break;
            }
            if (command != null) {
                command.execute();
                undoStack.push(command);
            }
        } catch (Exception e) {
        }
    }

    static void prompt() {
        System.out.printf("  사각형 : rectangle 레이블\n");
        System.out.printf("  선     : line 레이블\n");
        System.out.printf("  삭제   : remove 번호\n");
        System.out.printf("  복제   : duplicate 번호\n");
        System.out.printf("  그룹   : group 번호1, 번호2,...\n");
        System.out.printf("  Undo   : undo\n");
        System.out.printf("  Redo   : redo\n");
        System.out.printf("  종료   : quit\n");
        System.out.printf("  ? ");
    }

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            while (true) {
                prompt();
                String cmd = scanner.nextLine();
                execute(cmd);
                drawFigures();
            }
        }
    }
}
