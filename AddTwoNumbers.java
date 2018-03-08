package AlgorithmOfLeetcode;

public class AddTwoNumbers {
    public static class ListNode{
        int val;
        ListNode next;
        ListNode(int x){
           val=x;
        }
    }
    public static ListNode addTwoNumbers(final ListNode first,final ListNode second){
       ListNode head=new ListNode(0);
       ListNode p=first,q=second,curr=head;
       int carry=0;
       while (p!=null||q!=null){
           int x=(p!=null)?p.val:0;
           int y=(q!=null)?q.val:0;
           int sum=carry+x+y;
           carry=sum/10;
           curr.next=new ListNode(sum%10);
           curr=curr.next;
           if (p.next!=null)p=p.next;
           if (q.next!=null)q=q.next;
       }
       if (carry>0){
           curr.next=new ListNode(carry);
           curr=curr.next;
       }
       curr.next=null;
       return head.next;
    }
    public static void printListNode(final ListNode head){
        ListNode node=head;
        while (node!=null){
            System.out.print(node.val+" ");
            node=node.next;
        }
    }
    public static void main(String[]args){
        ListNode l1=new ListNode(1);
        ListNode first=l1;
        int j=9;
        while (--j>=0){
            l1.next=new ListNode(j);
            l1=l1.next;
        }
        l1.next=null;
        ListNode l2=new ListNode(1);
        ListNode second=l2;
        j=7;
        while (--j>=0){
            l2.next=new ListNode(j);
            l2=l2.next;
        }
        l2.next=null;
        printListNode(first);
        System.out.println();
        printListNode(second);
        ListNode head=addTwoNumbers(first,second);
        printListNode(head);
    }
}
