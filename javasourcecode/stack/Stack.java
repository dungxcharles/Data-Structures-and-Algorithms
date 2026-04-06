package javasourcecode.stack;
public class Stack{
    private class Node{
        int value;
        Node next;
        Node(int value){
            this.value = value;
            this.next = null;
        }
    }

    private Node head = null;

    public void push(int value){
        Node newNode = new Node(value);
        newNode.next = head;
        head = newNode;
    }

    public int pop(){
        if (head == null){
            System.out.println("The head is null!");
            return Integer.MIN_VALUE;
        }
        Node res = head;
        head = head.next;
        return res.value;
    }

    public boolean isEmpty(){
        return head==null;
    }
}