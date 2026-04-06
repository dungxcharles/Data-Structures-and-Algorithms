package javasourcecode.stack;

public class Main {
    public static void main(String[] args) {
        Stack stack = new Stack();
        stack.push(4);
        stack.push(5);
        stack.push(7);
        while (!stack.isEmpty()){
            System.out.println(stack.pop());
        }
    }
}
