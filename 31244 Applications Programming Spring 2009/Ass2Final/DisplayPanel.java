import model.*;

import java.awt.*;
import javax.swing.*;

public class DisplayPanel extends JPanel implements View
{
    private Prison prison;
    private CountPanel countPanel;
    private CrimTable crimTable;
    private JScrollPane scroll;

    public DisplayPanel(Prison prison, CountPanel countPanel, CrimTable crimTable)
    {   this.prison = prison;
        prison.attach(this);
        this.countPanel = countPanel;
        this.crimTable = crimTable;
        build();
        setup();    }

    private void setup()
    {   setPreferredSize(new Dimension(400,170));
        setLayout(new FlowLayout());    }
    
    private void build()
    {   // countPanel = new CountPanel(prison);
        add(countPanel);
        add(crimTable);
        update();   }
    
    public void update()
    {}
}
