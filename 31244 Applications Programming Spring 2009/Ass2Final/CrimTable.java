import model.*;

import java.awt.*;
import javax.swing.*;
import javax.swing.table.*;

public class CrimTable extends JPanel implements View
{
    private Prison prison;
    JTable table;
    
    public CrimTable(Prison prison)
    {   this.prison = prison;
        prison.attach(this);
        setup();
        build();    }
        
    private void setup()
    {}
    
    private void build()
    {   table = new JTable(new TableModel());
        table.setPreferredScrollableViewportSize(new Dimension(210, 130));
        table.setFillsViewportHeight(true);
        setColumn();
        JScrollPane scrollPane = new JScrollPane(table);
        add(scrollPane);
        update();
    }
    
    private void setColumn()
    {   TableColumnModel model = table.getColumnModel();
        TableColumn column = model.getColumn(0);
        column.setPreferredWidth(20);  }
    
    public void update()
    {   for (int i = 0; i < 20; i++)
        {   if (!prison.cells().get(i).getBunk(0).isFree())
            {   table.setValueAt(prison.cells().get(i).getBunk(0).owner().name(), i, 1); }
            if ((i + 1)%2 == 0)
                if (!prison.cells().get(i).getBunk(1).isFree())
                {   table.setValueAt(prison.cells().get(i).getBunk(1).owner().name(), i, 2); }}}

private class TableModel extends AbstractTableModel
{   private String[] columnNames = {"A","B","C"};
    Object[][] data = {{1.1,"",""},{1.2,"",""},{1.3,"",""},{1.4,"",""},
        {1.5,"",""},{1.6,"",""},{1.7,"",""},{1.8,"",""},{1.9,"",""},
        {"1.10","",""},{2.1,"",""},{2.2,"",""},{2.3,"",""},{2.4,"",""},
        {2.5,"",""},{2.6,"",""},{2.7,"",""},{2.8,"",""},{2.9,"",""},
        {"2.10","",""}};

    public int getColumnCount()
    {   return columnNames.length;  }

    public int getRowCount()
    {   return data.length; }

    public String getColumnName(int col)
    {   return columnNames[col];    }
    
    public Object getValueAt(int row, int col)
    {   return data[row][col];  }
    
    public void setValueAt(Object value, int row, int col)
    {   data[row][col] = value;
        fireTableCellUpdated(row, col); }
}
}