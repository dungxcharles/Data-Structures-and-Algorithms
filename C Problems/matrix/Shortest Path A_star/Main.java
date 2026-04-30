public class Main {
    public static void main(String[] args) {
        Astar solver = new Astar();

        solver.readInput();
        boolean check = solver.astarSolver();
        System.out.println("Path finding status: " + check);
        System.out.println("The number of visited nodes: " + solver.cnt);

        if (check){
            System.out.println("The shortest path found by A*:");
            solver.printPath();
        }
    }
}
