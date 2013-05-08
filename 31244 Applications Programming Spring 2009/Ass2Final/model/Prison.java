package model;

import java.util.*;

public class Prison extends Viewable
{   private static Date today;

    public static Date today()
    {   return today;   }

    private static void setStart()
    {   today = new Date(1, 1, 2009);    }

    private Cells cells = new Cells();
    private Criminals crims = new Criminals();
    
    public Prison()
    {   setStart(); }
    
    public void add(Criminal crim)
    {   crims.add(crim);
        cells.allocate(crim);    }
        
    public Criminals crims()
    {   return crims;   }
    
    public Cells cells()
    {   return cells;   }
}
