import model.*;

import java.awt.*;
import javax.swing.*;
import java.util.*;

public class CrimePanel extends JPanel implements View
{
    private Prison prison;
    private ButtonGroup group = new ButtonGroup();
    
    public CrimePanel(Prison prison)
    {   this.prison = prison;
        prison.attach(this);
        setup();
        build();    }
 
    private void setup()
    {   setLayout(new GridLayout(3, 3)); }
    
    private void build()
    {
        for(Name name: Name.values())
        {   addButton(group, name.toString());  }
    }
    
    public void update()
    {   group.clearSelection(); }
    
    public void addButton(ButtonGroup group, String label)
    {   JRadioButton button = new JRadioButton(label);
        group.add(button);
        add(button);    }

    public String getCrime()
    {   Enumeration e = group.getElements();
        while (e.hasMoreElements())
        {   JRadioButton  button = (JRadioButton) e.nextElement();
            if(button.isSelected())
            {   return button.getText();    }    }
        return null;    }
}