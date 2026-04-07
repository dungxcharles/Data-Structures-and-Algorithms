public class Queue{
    private class Node{
        int val;
        Node next;
        Node(int val){
            this.val = val;
            this.next = null;
        }
    }

    private Node head = null;
    private Node tail = null;

    public void enqueue(int val){
        Node newNode = new Node(val);
        if (head == null && tail == null){
            head = newNode;
            tail = newNode;
            return;
        }
        tail.next = newNode;
        tail = tail.next;
    }

    public int dequeue(){
        if (head == null || tail == null){
            System.out.println("Queue is empty!");
            return Integer.MIN_VALUE;
        }

        Node tmp = head;
        head = head.next;
        if (head == null){
            tail = null;
        }
        return tmp.val;
    }

    public boolean isEmpty(){
        return head == null;
    }
}