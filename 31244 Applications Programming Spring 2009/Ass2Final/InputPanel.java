import model.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class InputPanel extends JPanel implements View
{
    private Prison prison;
    private GridBagLayout bag = new GridBagLayout();
    private ValuePanel valuePanel;
    private CrimePanel crimePanel;
    private CountPanel countPanel;
    private CrimTable crimTable;
    private Dimension buttonSize = new Dimension(270, 60);
    
    public InputPanel(Prison prison, CountPanel countPanel, CrimTable crimTable)
    {   this.prison = prison;
        prison.attach(this);
        this.countPanel = countPanel;
        this.crimTable = crimTable;
        setup();
        build(prison);  }

    private void setup()
    {   setPreferredSize(new Dimension(400,170));
        setLayout(bag); }
    
    private void build(Prison prison)
    {   valuePanel = new ValuePanel(prison);
        crimePanel = new CrimePanel(prison);
        addToBag(valuePanel, 1, 2, 0, 0);
        addToBag(crimePanel, 1, 1, 1, 0);
        addToBag(addButton(), 1, 1, 1, 1);  }
    
    public void update()
    {}
    
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
        
     private JButton addButton()
    {   JButton button = new JButton("Allocate cell");
        button.setPreferredSize(buttonSize);
        button.setMinimumSize(buttonSize);
        button.setMaximumSize(buttonSize);
        button.addActionListener(new AllocateListener());
        return button;  }
    
private class AllocateListener implements ActionListener
{   public void actionPerformed(ActionEvent e)
    {   Criminal criminal = new Criminal(valuePanel.getName());
        Crime crime = new Crime(crimePanel.getCrime());
        crime.set(new Period(valuePanel.getDays(), valuePanel.getMonths(), valuePanel.getYears()));
        criminal.set(crime);
        prison.add(criminal);
        valuePanel.update();
        crimePanel.update();
        countPanel.update();
        crimTable.update(); }
}
}