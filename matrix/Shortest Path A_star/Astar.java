import java.util.PriorityQueue;
import java.util.Scanner;

public class Astar {
    // Node info
    private class Node{
        int x, y;
        int f, g, h;        // f = g + h
        Node(int x, int y, int f, int g, int h){
            this.x = x; this.y = y;
            this.f = f; this.g = g; this.h = h;
        }
    }

    // Literals
    private int rows, cols;
    private Node[][] mat;
    private Node source, target;

    public void readInput(){
        Scanner sc = new Scanner(System.in);
        rows = sc.nextInt();
        cols = sc.nextInt();
        mat = new Node[rows][cols];

        int xs = sc.nextInt(), ys = sc.nextInt();
        source = new Node(xs, ys, 0, 0, 0);
        int xt = sc.nextInt(), yt = sc.nextInt();
        target = new Node(xt, yt, 0, 0, 0);
    }
}
