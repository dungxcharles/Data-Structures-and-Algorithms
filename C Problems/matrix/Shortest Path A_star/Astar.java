import java.util.PriorityQueue;
import java.util.Scanner;

public class Astar {
    public int cnt = 0;
    // Node info
    private class Node{
        int x, y;
        int f, g, h;        // f = g + h
        Node parent;
        public Node(int x, int y){
            this.x = x;
            this.y = y;
            this.f = 0; this.g = 0; this.h = 0;
            this.parent = null;
        }
        public Node(int x, int y, int g, int h, Node parent){
            this.x = x; this.y = y;
            this.g = g; this.h = h; this.f = g + h;
            this.parent = parent;
        }

        public void updateNode(){
            this.h = manhattanHeuristic(this);
            this.g = (this.parent).g + 1;
            this.f = this.g + this.h;
        }

        // @Override
        public boolean equals(Object node){
            Node other = (Node)node;
            return this.x == other.x && this.y == other.y;
        }
    }

    // Literals
    private int rows, cols;
    private int[][] mat;
    private boolean[][] visited;
    private Node source, target;

    private final int dx[] = {1, 0, -1, 0};
    private final int dy[] = {0, 1, 0, -1};

    // Read inputs
    public void readInput(){
        System.out.println("Please input number of rows, number of columns, matrix (0/1), source, target respectively:");
        Scanner sc = new Scanner(System.in);
        rows = sc.nextInt();
        cols = sc.nextInt();
        mat = new int[rows][cols];
        visited = new boolean[rows][cols];

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                mat[i][j] = sc.nextInt();
                if (mat[i][j] == 1){
                    visited[i][j] = true;
                }else{
                    visited[i][j] = false;
                }
            }
        }

        int xs = sc.nextInt(), ys = sc.nextInt();
        
        int xt = sc.nextInt(), yt = sc.nextInt();
        target = new Node(xt, yt);
        source = new Node(xs, ys);
        source.h = manhattanHeuristic(source);
        source.f = source.h;
    }

    private boolean isValid(Node node){
        return node.x >= 0 && node.x < rows && node.y >= 0 && node.y < cols && !visited[node.x][node.y];
    }

    private int manhattanHeuristic(Node a){
        return Math.abs(a.x - target.x) + Math.abs(a.y - target.y);
    }

    // Path-finding Solver
    public boolean astarSolver(){
        PriorityQueue<Node> pq = new PriorityQueue<>(
            (a, b) -> Integer.compare(a.f, b.f)
        );

        pq.add(source);

        while (!pq.isEmpty()){
            Node top = pq.poll();

            if (visited[top.x][top.y] == true)   continue;
            visited[top.x][top.y] = true;
            cnt++;

            if (top.equals(target)){
                target.parent = top;
                return true;
            }

            for (int i = 0; i < 4; i++){
                Node newNode = new Node(top.x + dx[i], top.y + dy[i]);
                
                if (isValid(newNode)){
                    newNode.parent = top;
                    newNode.updateNode();
                    pq.add(newNode);
                }
            }
        }
        return false;
    }

    public void printPath(){
        Node t = target;
        while (t != null){
            mat[t.x][t.y] = 2;
            t = t.parent;
        }

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                System.out.print(mat[i][j] + " ");
            }
            System.out.println();
        }
    }
}
