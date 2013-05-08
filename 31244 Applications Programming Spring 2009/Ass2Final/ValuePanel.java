import model.*;

import java.awt.*;
import javax.swing.*;


public class ValuePanel extends JPanel implements View
{
    private Prison prison;
    private GridBagLayout bag = new GridBagLayout();
    private JLabel nameLabel = new JLabel("Name");
    private JTextField nameField = new JTextField();
    private Dimension nameFieldSize = new Dimension(90, 20);
    private JTextField days = new JTextField();
    private JTextField months = new JTextField();
    private JTextField years = new JTextField();
    private Dimension numberFieldSize = new Dimension(30, 20);

    
    public ValuePanel(Prison prison)
    {   this.prison = prison;
        prison.attach(this);
        build();
        setup();    }
    
    private void setup()
    {   setLayout(bag); }
    
    private void build()
    {   addToBag(addNamePair(), 3, 2, 0, 0);
          addToBag(addPair(days, "  days         "), 3, 1, 0, 2);
        addToBag(addPair(months, "  months    "), 3, 1, 0, 3);
         addToBag(addPair(years, "  years       "), 3, 1, 0, 4);
        update();   }
    
    public void update()
    {   nameField.setText("");
        days.setText("");
        months.setText("");
        years.setText("");  }
    
    private Box addNamePair()
    {   Box box = Box.createVerticalBox();
        box.add(Box.createVerticalStrut(6));
        nameLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
        box.add(nameLabel);
        box.add(Box.createVerticalStrut(6));
        nameField.setPreferredSize(nameFieldSize);
        nameField.setMinimumSize(nameFieldSize);
        nameField.setMaximumSize(nameFieldSize);
        nameField.setAlignmentX(Component.CENTER_ALIGNMENT);
        box.add(nameField);
        return box; }
    
    private Box addPair(JTextField field, String label)
    {   Box box = Box.createHorizontalBox();
        box.add(Box.createVerticalStrut(6));
        field.setPreferredSize(numberFieldSize);
        field.setMinimumSize(numberFieldSize);
        field.setMaximumSize(numberFieldSize);
        field.setAlignmentX(Component.LEFT_ALIGNMENT);
        box.add(field);
        box.add(new JLabel(label));
        box.add(Box.createVerticalStrut(6));
        return box; }
        
    private void place(Component comp, int w, int h, int x, int y)
    {   GridBagConstraints cons = new GridBagConstraints();
        cons.gridwidth = w;
        cons.gridheight = h;
        cons.gridx = x;
        cons.gridy = y;
        cons.weightx = 1;
        cons.weighty = 1;
        cons.fill = GridBagConstraints.BOTH;
        bag.setConstraints(comp, cons); }
        
    private void addToBag(Component c, int w, int h, int x, int y)
    {   add(c);
        place(c, w, h, x, y);   }
        
    public String getName()
    {   return nameField.getText();    }
        
    public int getDays()
    {   return Integer.parseInt(days.getText());    }
    
    public int getMonths()
    {   return Integer.parseInt(months.getText());    }
    
    public int getYears()
    {   return Integer.parseInt(years.getText());    }
}
