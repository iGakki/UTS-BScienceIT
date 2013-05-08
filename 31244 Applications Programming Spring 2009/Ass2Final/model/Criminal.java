package model;

public class Criminal
{   private String name;
    private int id;
    private Crime crime;
    private Cell cell;
    
    public Criminal(String name)
    {   this.name = name;   }
        
    public void setId(int id)
    {   this.id = id;   }
    
    public void set(Crime crime)
    {   this.crime = crime; }
        
    public void set(Cell cell)
    {   this.cell = cell;   }
    
    public boolean hasLevel(int level)
    {   return level() == level;    }
    
    public int level()
    {   return crime.level(); }
    
    public String name()
    {   return name;    }
}
