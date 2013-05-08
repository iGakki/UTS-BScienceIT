import model.*;

import java.awt.*;
import javax.swing.*;

public class CountPanel extends JPanel implements View
{
    private Prison prison;
    private JLabel count;

    public CountPanel(Prison prison)
    {   this.prison = prison;
        prison.attach(this);
        build();
        setup();    }

    private void setup()
    {}

    private void build()
    {   count = new JLabel(getCount());
        add(count);
        update();   }
    
    public void update()
    {   count.setText(getCount());   }
    
    private String getCount()
    {   return prison.crims().count() + " prisoners         ";  }
}
