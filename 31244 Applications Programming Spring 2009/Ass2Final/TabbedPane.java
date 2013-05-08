import model.*;

import java.awt.*;
import javax.swing.*;

public class TabbedPane extends JTabbedPane
{
    private CountPanel countPanel;
    private CrimTable crimTable;
    
    public TabbedPane(Prison prison)
    {   setup();
        build(prison);
        setVisible(true);   }
    
    private void setup()
    {   setBorder(BorderFactory.createLineBorder(Color.blue));  }

    private void build(Prison prison)
    {   countPanel = new CountPanel(prison);
        crimTable = new CrimTable(prison);
        add("Input", new InputPanel(prison, countPanel, crimTable));
        add("Display", new DisplayPanel(prison, countPanel, crimTable));   }
}