public class Main {
    public static void main(String[] args) {
        Queue myQ = new Queue();
        myQ.enqueue(3);
        myQ.enqueue(4);
        myQ.enqueue(1);
        while (!myQ.isEmpty()){
            System.out.println(myQ.dequeue());
        }
    }
}
