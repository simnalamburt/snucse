import java.awt.*;
import javax.swing.*;

public class LabWork
{
    public static void main(String[] args)
    {
        //work1();
        work2();
    }
    public static void work1() {
        LabSub a1 = new LabSub(10);
        LabSub a2 = new LabSub(5);

        System.out.println("Total number of LabSub object is " + LabSub.mNumber);

        System.out.println(a1);
        System.out.println(a2);
        a1=a2;
        a1.a = 50;
        System.out.println(a1);
        System.out.println(a2);
    }
    //GUI
    public static void work2() {
        EventQueue.invokeLater(new Runnable()
        {
            public void run()
            {
                JFrame frame = new WorkFrame();
                frame.setTitle("GUI");
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                frame.setVisible(true);
            }
        });
    }
}

