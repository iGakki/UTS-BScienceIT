import model.*;

import java.awt.*;
import java.util.*;
import javax.swing.*;

public class PopupWindow extends JFrame
{   
    public Window(Prison prison)
    {   setup();
        build(prison);
        pack();
        setVisible(true);   }
        
    private void setup()
    {   setLocation(0, 500);
        setDefaultCloseOperation(EXIT_ON_CLOSE);    }
        
    private void build(Prison prison)
    {   add(new TabbedPane(prison));    }
}