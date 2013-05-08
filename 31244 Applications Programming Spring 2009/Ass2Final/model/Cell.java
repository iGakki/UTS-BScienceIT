package model;

import java.util.*;

public class Cell
{   private String id;
    private LinkedList<Bunk> bunks = new LinkedList<Bunk>();
    
    public Cell(String id, int bunks)
    {   this.id = id;
        setBunks(bunks);    }
        
    private void setBunks(int number)
    {   if (number == 1)
            bunks.add(new Bunk("only"));
        else
        {   bunks.add(new Bunk("top"));
            bunks.add(new Bunk("bottom"));   }}
    
    public boolean isFull()
    {   for (Bunk bunk: bunks)
            if (bunk.isFree())
                return false;
        return true;    }
        
    public boolean fits(Criminal crim)
    {   for (Bunk bunk: bunks)
            if (bunk.isFree())
                continue;
            else if (bunk.isCompatible(crim))
                continue;
            else
                return false;
        return true;    }

    public void set(Criminal crim)
    {   for (Bunk bunk: bunks)
            if (bunk.isFree())
            {   bunk.set(crim);
                crim.set(this);
                return; }}
     
    public Bunk bunk(Criminal crim)
    {   for (Bunk bunk: bunks)
            if (bunk.has(crim))
                return bunk;
        return null;    }
        
    public boolean isFree()
    {   for (Bunk bunk: bunks)
            if (bunk.hasOwner())
                return false;
        return true;    }
    
    public String id()
    {   return id;   }
    
    public Bunk getBunk(int i)
    {   return bunks.get(i);    }
}
