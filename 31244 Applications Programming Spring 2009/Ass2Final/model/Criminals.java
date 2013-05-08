package model;

import java.text.*;
import java.util.*;

public class Criminals
{   private LinkedList<Criminal> crims = new LinkedList<Criminal>();
    private Cells cells = new Cells();
    private int id = 0;

    private int nextId()
    {   return ++id;    }

    public void add(Criminal crim)
    {   crim.setId(nextId());
        crims.add(crim);    }
        
    public int count()
    {   return crims.size();    }
}
