import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;

/**
 * A frame that contains a component with drawings
 */
class WorkFrame extends JFrame
{
    public WorkFrame()
    {
        add(new FillComponent());
        pack();
    }
}

/**
 * A component that displays filled rectangles and ellipses
 */
class FillComponent extends JComponent
{
    private static final int DEFAULT_WIDTH = 200;
    private static final int DEFAULT_HEIGHT = 300;

    public void paintComponent(Graphics g)
    {
        Graphics2D g2 = (Graphics2D) g;

        // bkground
        {
            double width = (double)DEFAULT_WIDTH;
            double height = (double)DEFAULT_HEIGHT;
            Rectangle2D rect = new Rectangle2D.Double(0.0, 0.0, width, height);
            g2.setPaint(Color.BLUE);
            g2.fill(rect);
        }

        //draw triangle
        g2.setPaint(Color.WHITE);
        g.fillPolygon(
            new int[] { 100, 80, 80, 60, 60, 140, 140, 120, 120 },
            new int[] { 60, 100, 130, 160, 190, 190, 160, 130, 100 },
            9
        );

        int[] x = new int[] { 60, 60, 80, 100, 120, 140, 140 };
        int[] y = new int[] { 200, 220, 200, 220, 200, 220, 200 };
        int count = 7;

        for (int i = 0; i < count - 1; ++i) {
            g2.drawLine(x[i], y[i], x[i+1], y[i+1]);
        }

        // red rect
        {
            Rectangle2D rect = new Rectangle2D.Double(90.0, 100.0, 20.0, 30.0);
            g2.setPaint(Color.RED);
            g2.fill(rect);
        }
    }

    public Dimension getPreferredSize() { return new Dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT); }
}
