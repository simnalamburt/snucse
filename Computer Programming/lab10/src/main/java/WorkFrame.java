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
    private static final int DEFAULT_WIDTH = 400;
    private static final int DEFAULT_HEIGHT = 400;

    public void paintComponent(Graphics g)
    {
        Graphics2D g2 = (Graphics2D) g;

        // draw a rectangle

        double leftX = 100;
        double topY = 100;
        double width = 200;
        double height = 150;

        Rectangle2D rect = new Rectangle2D.Double(leftX, topY, width, height);
        g2.setPaint(Color.BLACK);
        g2.draw(rect);
        g2.setPaint(Color.RED);
        g2.fill(rect); // Note that the right and bottom edge are not painted over

        // draw the enclosed ellipse

        Ellipse2D ellipse = new Ellipse2D.Double();
        ellipse.setFrame(rect);
        g2.setPaint(new Color(0, 128, 128)); // a dull blue-green
        g2.fill(ellipse);

        //draw triangle
        //*
        g2.setPaint(Color.BLACK);
        g.fillPolygon(new int[] {(int)leftX, (int)(leftX+(width/2)), (int)(leftX+width)},
                new int[] {(int)(topY+height), (int)(topY), (int)(topY+height)}, 3);
        g2.drawLine((int)leftX, (int)(topY+height), (int)(leftX+(width/2)), (int)topY);
        g2.drawLine((int)(leftX+(width/2)), (int)topY, (int)(leftX+width), (int)topY);
        g2.drawLine((int)(leftX+width), (int)(topY+height), (int)leftX, (int)(topY+height));
        //*/
    }

    public Dimension getPreferredSize() { return new Dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT); }
}
