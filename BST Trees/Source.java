//kamil sordyl

import java.util.Scanner;


//wykorzystowana jest pomocniczas klasa symulujaca stos
//wszystkie funkcje sa iteracyjne, poza tworzeniem drzewa z listy preorder,postorder oraz sprawdzaniem  glebokosci drzewa
class List
{
    Node node;
    List next;

    List(Node x)
    {
        node = x;
        next= null;
    }
}

class Stack //stos obslugujacy wezly drzewa
{
    List head;
    Stack()
    {
        head=null;
    }
    void put(Node x)
    {
        List a = new List(x);
        a.next=head;
        head=a;
    }

    Node pull()//wyciaga element ze stosu
    {
        Node output = head.node;
        head = head.next;
        return output;
    }

    void clean()//czysci stos
    {
        while (head!=null)
        {
            head=head.next;
        }
    }
    boolean isEmpty()
    {
        return head==null;
    }
}

class Person {
    public int priority; // priorytet osoby
    public String name;
    public String surname;

    Person(int priority_,String name_, String surname_)
    {
        priority = priority_;
        name = name_;
        surname = surname_;
    }
// konstruktor...
}

class Node {
    public Person info; // element danych (klucz)
    public Node left; // lewy potomek wezla
    public Node right; // prawy lewy potomek wezla


    Node(Person info_)
    {
        info=info_;
        left=null;
        right=null;
    }

}

class Tree
{
    public Node root;
    Stack stack = new Stack();
    Index preIndex = new Index();
   // public static Scanner sc1 = new Scanner(System.in);
    class Index//dzieki temu indeks nie jest kopiowany a przekazywany w rekurencji
    {
        int index = 0;
    }

    Tree()
    {
        root=null;
    }
    Node Create(int n, boolean preorder, Scanner sc)//tworzy drzewo
    {
        Person[] tablica = new Person[n];
        for(int i=0;i<n;i++)
        {


                int i1 = sc.nextInt();
                String s1 = sc.next();
                String s2 = sc.next();
                tablica[i]=new Person(i1,s1,s2);



        }
        if(root!=null)
        {
            root=null;
        }
        return constructTree(tablica,n,preorder);
    }

    Node constructTreeUtil(Person tab[], Index preIndex, Person key, int min, int max, int size)//tworzy drzewo w preorder
    {



        if (preIndex.index >= size) {
            return null;
        }
        Node root = null;

        if (key.priority > min && key.priority < max) {
            root = new Node(key);
            preIndex.index = preIndex.index + 1;

            if (preIndex.index < size) {
                root.left = constructTreeUtil(tab, preIndex, tab[preIndex.index], min, key.priority, size);

            }

            if (preIndex.index < size) {
                root.right = constructTreeUtil(tab, preIndex, tab[preIndex.index], key.priority, max, size);
            }
        }
        return root;
    }

    Node constructTreeUtilPost(Person tab[], Index preIndex, Person key, int min, int max, int size)//tworzy drzewo w postorderze
    {


        //
        if (preIndex.index < 0) {
            return null;
        }
        Node root = null;

        if (key.priority > min && key.priority < max) {
            root = new Node(key);
            preIndex.index = preIndex.index - 1;

            if (preIndex.index >= 0) {
                root.right = constructTreeUtilPost(tab, preIndex, tab[preIndex.index], key.priority, max, size);

            }

            if (preIndex.index >= 0) {
                root.left = constructTreeUtilPost(tab, preIndex, tab[preIndex.index], min, key.priority, size);
            }
        }
        return root;
    }

    Node constructTree(Person tab[],int size, boolean preorder)//wywoluje odpowiednia funkcje z odpowiednimi parametram
    {
        if(preorder)
        {

            preIndex.index=0;
            return constructTreeUtil(tab,preIndex,tab[0],Integer.MIN_VALUE,Integer.MAX_VALUE,size);
        }
        else//sus z indexami
        {
            //Index preIndex=new Index();
            preIndex.index=size -1;
            //int preIndex=size -1;
            return constructTreeUtilPost(tab,preIndex,tab[preIndex.index],Integer.MIN_VALUE,Integer.MAX_VALUE,size);
        }

    }
//////////////////////////////////////////////////////////////////////////////////////MODUL KOLEJKOWANIA/////////////////////////
//////////////////////////////////////////////////////////////////////////////////////MODUL KOLEJKOWANIA/////////////////////////
//////////////////////////////////////////////////////////////////////////////////////MODUL KOLEJKOWANIA/////////////////////////
//////////////////////////////////////////////////////////////////////////////////////MODUL KOLEJKOWANIA/////////////////////////
//////////////////////////////////////////////////////////////////////////////////////MODUL KOLEJKOWANIA/////////////////////////
  //enque
    public void addPerson(Person info_)
    {
        Node newNode = new Node(info_);

        if (root==null)
        {
            root = newNode;

        }
        else
        {
            Node focusNode = root;
            Node parent;
            while(true)
            {
                parent = focusNode;

                if (info_.priority< focusNode.info.priority)
                {
                    focusNode=focusNode.left;
                    if(focusNode==null)
                    {
                        parent.left=newNode;
                        return;
                    }
                }
                else if(info_.priority> focusNode.info.priority)
                {
                    focusNode=focusNode.right;
                    if(focusNode==null)
                    {
                        parent.right=newNode;
                        return;
                    }
                }
                else
                {
                    focusNode=focusNode.right;
                    if(focusNode==null)
                    {
                        parent.right=newNode;
                        return;
                    }
                }
            }

        }
    }

    //na poczatku podajemy dequeMax(root,null)
    Node dequeMax(Node focusNode, Node parent)
    {
        while(focusNode!=null)
        {
            if(focusNode==root && focusNode.right==null)
            {
                root=focusNode.left;
                return focusNode;
            }
            else if(focusNode.right==null)
            {
                //sprawdzanie czy focus node posiada lewego rodzica
                //jesli tak, to podmien go z focus node i usun potem focusNode
                if(focusNode.left!=null)
                {
                    parent.right=focusNode.left;
                    return focusNode;
                }
                else
                {
                    parent.right=null;
                    return focusNode;
                }
            }
            else
            {
                parent=focusNode;
                focusNode=focusNode.right;
            }

        }
        return null;//drzewo puste
    }

    Node dequeMin(Node focusNode, Node parent)
    {
        while(focusNode!=null)
        {
            if(focusNode==root && focusNode.left==null)
            {
                root=focusNode.right;
                return focusNode;
            }
            else if(focusNode.left==null)
            {
                //sprawdzanie czy focus node posiada prawego rodzica
                //jesli tak, to podmien go z focus node i usun potem focusNode
                if(focusNode.right!=null)
                {
                    parent.left=focusNode.right;
                    return focusNode;
                }
                else
                {
                    parent.left=null;
                    return focusNode;
                }
            }
            else
            {
                parent=focusNode;
                focusNode=focusNode.left;
            }

        }
        return null;//drzewo puste
    }



    //if root!=null


    //na poczatku wywalujemy NextElement(root,priority tego dla ktorego szukamy nastepnika,null)
    //jesli funkcja zwroci null to nie ma nastepnika
    //jesli output to null
    //jest node z key nie ma prawego potomka cofamy sie przez stos tak dlugo jak bedziemy miec wartosc wieksza od key
    Node NextElement(Node focusNode,int key, Node bestcandidate)
    {
        stack.clean();
        boolean exists=false;
        while(focusNode!=null)
        {
            stack.put(focusNode);
            if(focusNode.info.priority<key)
            {
/*                if( focusNode.right != null && focusNode.right.info.priority>key)//sus
                {
                    return null;
                }*/
                focusNode=focusNode.right;
                continue;
            }
            if(focusNode.info.priority>key)
            {
                if(bestcandidate == null || focusNode.info.priority<bestcandidate.info.priority)
                {
                    bestcandidate=focusNode;
                }
                focusNode=focusNode.left;
                continue;
            }
            else if(focusNode.info.priority==key)
            {
                exists=true;
                if(focusNode.right==null)
                {
                    while(!stack.isEmpty())
                    {
                        Node parent=stack.pull();
                        if(parent.left==focusNode)
                        {
                           return parent;
                        }
                        focusNode=parent;


                    }
                    return null;
                }
                else
                {
                    focusNode=focusNode.right;
                    continue;
                }

            }
        }
        if(exists) return bestcandidate;
        return null;
    }


    //na poczatku wywalujemy PrevElement(root,priority tego dla ktorego szukamy nastepnika,null)
    //jesli funkcja zwroci null to nie ma nastepnika
    Node PrevElement(Node focusNode,int key, Node bestcandidate)
    {
        stack.clean();
        boolean exists=false;
        while(focusNode!=null)
        {
            stack.put(focusNode);
            if(focusNode.info.priority>key)
            {
 /*              if( focusNode.left != null && focusNode.left.info.priority<key)//sus
               {

               }*/
                focusNode=focusNode.left;
                continue;
            }
            if(focusNode.info.priority<key)
            {
                if(bestcandidate == null || focusNode.info.priority>bestcandidate.info.priority)
                {
                    bestcandidate=focusNode;
                }
                focusNode=focusNode.right;
                continue;
            }
            else if(focusNode.info.priority==key)//znalazlo, musi pamietac ze tu byl
            {
                exists=true;
                if(focusNode.left==null)
                {
                    while(!stack.isEmpty())
                    {
                        Node parent=stack.pull();
                        if(parent.right==focusNode)
                        {
                            return parent;
                        }
                        focusNode=parent;


                    }
                    return null;
                }
                else
                {
                    focusNode=focusNode.left;
                    continue;
                }

            }
        }
        if(exists) return bestcandidate;
        return null;

    }


///////////////////////////////////////////////////////////////////////////MODUL RAPORTOWANIA//////////////////////////
///////////////////////////////////////////////////////////////////////////MODUL RAPORTOWANIA//////////////////////////
///////////////////////////////////////////////////////////////////////////MODUL RAPORTOWANIA//////////////////////////
///////////////////////////////////////////////////////////////////////////MODUL RAPORTOWANIA//////////////////////////
///////////////////////////////////////////////////////////////////////////MODUL RAPORTOWANIA//////////////////////////
///////////////////////////////////////////////////////////////////////////MODUL RAPORTOWANIA//////////////////////////
///////////////////////////////////////////////////////////////////////////MODUL RAPORTOWANIA//////////////////////////

    void preorder()
    {
        if(root==null)
        {
            return;
        }
        stack.clean();//czyszczenie stacku
        Node focusNode;
        //Node parent=null;
        stack.put(root);
        while(!stack.isEmpty())
        {
            focusNode=stack.pull();

            System.out.print(focusNode.info.priority+" - "+focusNode.info.name+" "+focusNode.info.surname);

            if(focusNode.right!=null)
            {
                stack.put(focusNode.right);
            }

            if(focusNode.left!=null)
            {
                stack.put(focusNode.left);
            }
            if(!stack.isEmpty())
            {
                System.out.print(", ");
            }
            else
            {
                System.out.print("\n");
            }

        }
    }


    void postorder()
    {
        if(root==null)
        {
            return;
        }
        Stack print = new Stack();

        stack.clean();//czyszczenie stacku
        Node focusNode;
        //Node parent=null;
        stack.put(root);
        while(!stack.isEmpty())
        {
            focusNode=stack.pull();

            print.put(focusNode);


            if(focusNode.left!=null)
            {
                stack.put(focusNode.left);
            }

            if(focusNode.right!=null)
            {
                stack.put(focusNode.right);
            }

        }
        while(!print.isEmpty())
        {
            focusNode = print.pull();
            System.out.print(focusNode.info.priority+" - "+focusNode.info.name+" "+focusNode.info.surname);
            if(!print.isEmpty())
            {
                System.out.print(", ");
            }
            else
            {
                System.out.print("\n");
            }
        }


    }

    void inorder() {
        if(root==null)
        {
            return;
        }
        stack.clean();//czyszczenie stacku
        Node focusNode = root;
        //stack.put(root);
        while (!stack.isEmpty() || focusNode != null) {//A CO JESLI focus NODE nie jest nullem ale nic juz nie doda do stacku?
            //focusNode = stack.pull();

            while (focusNode != null) {
                stack.put(focusNode);
                focusNode = focusNode.left;
            }
            focusNode = stack.pull();//A CO JESLI focus NODE nie jest nullem ale nic juz nie doda do stacku?
            System.out.print(focusNode.info.priority + " - " + focusNode.info.name + " " + focusNode.info.surname);
            if(focusNode.right == null && stack.isEmpty())
            {
                System.out.print("\n");
            }
            else
            {
                System.out.print(", ");
            }
            focusNode=focusNode.right;


        }

    }
    static int maxLevel;//ustaw maxLevel jako 0 na poczatku
    void height(Node focusNode,int level)//na poczatku podajemy root
    {//przechodzimy przez cale drzewo
        if(focusNode!=null)
        {
            if (level>maxLevel)
            {
                maxLevel=level;
            }

            height(focusNode.left,level+1);
            height(focusNode.right,level+1);
        }
    }





    public boolean remove(int key)
    {
        if(root==null)return false;
        Node focusNode = root;
        Node parent = root;
        boolean isItAleftChild = true;
        while(focusNode!=null && focusNode.info.priority!=key )
        {
            parent = focusNode;

            if(key<focusNode.info.priority)
            {
                isItAleftChild = true;
                focusNode=focusNode.left;
            }
            else
            {   isItAleftChild = false;
                focusNode=focusNode.right;
            }
        }
        if(focusNode==null)
        {
            return false;
        }
        else if(focusNode.left==null && focusNode.right ==null)
        {
            if(focusNode==root)
            {
                root = null;
                return true;
            }
            else
            {
                if(isItAleftChild)
                {
                    parent.left=null;
                }
                else
                {
                    parent.right=null;
                }
            }
        }
        else if(focusNode.right==null)
        {
            if(focusNode ==root)
            {
                root=focusNode.left;
            }
            else if(isItAleftChild)
            {
                parent.left=focusNode.left;
            }
            else
            {
                parent.right=focusNode.left;
            }
        }
        else if(focusNode.left==null)
        {
            if(focusNode ==root)
            {
                root=focusNode.right;
            }
            else if(isItAleftChild)
            {
                parent.left=focusNode.right;
            }
            else
            {
                parent.right=focusNode.right;
            }
        }
        else
        {
            Node replacement = getReplacementNode(focusNode);

            if(focusNode==root)
            {
                root = replacement;
            }
            else if(isItAleftChild)
            {
                parent.left=replacement;
            }
            else
            {
                parent.right = replacement;
            }
            replacement.left = focusNode.left;
        }
            return true;
    }

    public Node getReplacementNode(Node replacedNode)
    {
        Node replacementParent = replacedNode;
        Node replacement = replacedNode;

        Node focusNode = replacedNode.right;

        while (focusNode!=null)
        {
            replacementParent = replacement;
            replacement = focusNode;
            focusNode=focusNode.left;
        }
        if(replacement !=replacedNode.right)
        {
            replacementParent.left=replacement.right;
            replacement.right=replacedNode.right;
        }

        return replacement;
    }


}

class Source
{

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int datatests = sc.nextInt();
        String command;
        String order;
        Person p;
        Node node;//sus
        int n;

        for (int i = 0; i < datatests; i++) {
            int commandsAmount = sc.nextInt();
            Tree tree=new Tree();
            System.out.println("ZESTAW "+(i+1));
            for(int j=0;j<commandsAmount;j++)
            {

                command = sc.next();

                switch(command)
                {
                    case "CREATE":
                        order = sc.next();
                        boolean isPreorder=(order.equals("PREORDER"));

                        n=sc.nextInt();
                        tree.root=tree.Create(n,isPreorder,sc);
                        break;
                    case "DELETE":
                        n=sc.nextInt();
                        boolean done = tree.remove(n);
                        if(!done)
                        {
                            System.out.println("DELETE "+n+": BRAK");
                        }
                        break;
                    case "ENQUE":
                        //debug
                        if(1==0)
                        {
                            System.out.println("erorr");
                        }
                        int aa=sc.nextInt();
                        String bb=sc.next();
                        String cc=sc.next();
                        p= new Person(aa,bb,cc);
                        tree.addPerson(p);
                        break;
                    case "DEQUEMAX":
                        node=tree.dequeMax(tree.root,null);
                        if(node==null)
                        {
                            System.out.println("DEQUEMAX: BRAK");
                        }
                        else System.out.println("DEQUEMAX: "+node.info.priority+" - "+node.info.name+" "+node.info.surname);
                        break;
                    case "DEQUEMIN":
                        node=tree.dequeMin(tree.root,null);
                        if(node==null)
                        {
                            System.out.println("DEQUEMIN: BRAK");
                        }
                        else System.out.println("DEQUEMIN: "+node.info.priority+" - "+node.info.name+" "+node.info.surname);
                        break;
                    case "NEXT":
                        n= sc.nextInt();
                        node = tree.NextElement(tree.root,n,null);
                        if(node==null)
                        {
                            System.out.println("NEXT "+n+": BRAK");
                        }
                        else System.out.println("NEXT "+n+": "+node.info.priority+" - "+node.info.name+" "+node.info.surname);
                        break;
                    case "PREV":
                        n= sc.nextInt();
                        node = tree.PrevElement(tree.root,n,null);
                        if(node==null)
                        {
                            System.out.println("PREV "+n+": BRAK");
                        }
                        else System.out.println("PREV "+n+": "+node.info.priority+" - "+node.info.name+" "+node.info.surname);
                        break;
                    case "PREORDER":
                        System.out.print("PREORDER: ");
                        tree.preorder();
                        break;

                    case "INORDER":
                        System.out.print("INORDER: ");
                        tree.inorder();
                        break;
                    case "POSTORDER":
                        System.out.print("POSTORDER: ");
                        tree.postorder();
                        break;
                    case "HEIGHT":
                        tree.maxLevel=0;
                        tree.height(tree.root,0);
                        System.out.println("HEIGHT: "+tree.maxLevel);
                        tree.maxLevel=0;
                        break;
                    default:
                        break;
                }
            }


        }

    }

}

//Test
/*
        1
        12
        CREATE PREORDER 7 4 d d 2 b b 1 a a 3 c c 6 f f 5 e e 7 g g
        DEQUEMIN
        DEQUEMAX
        POSTORDER
        NEXT 3
        NEXT 6
        DELETE 6
        ENQUE 8 x x
        POSTORDER
        DELETE 8
        DELETE 8
        POSTORDER
*/

//output
/*
        ZESTAW 1
        DEQUEMIN: 1 - a a
        DEQUEMAX: 7 - g g
        POSTORDER: 3 - c c, 2 - b b, 5 - e e, 6 - f f, 4 - d d
        NEXT 3: 4 - d d
        NEXT 6: BRAK
        POSTORDER: 3 - c c, 2 - b b, 8 - x x, 5 - e e, 4 - d d
        DELETE 8: BRAK
        POSTORDER: 3 - c c, 2 - b b, 5 - e e, 4 - d d*/
