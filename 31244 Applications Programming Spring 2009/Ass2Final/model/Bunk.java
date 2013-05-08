package model;

public class Bunk
{   private String location;
    private Criminal owner;

    public Bunk(String location)
    {   this.location = location;   }
    
    public boolean hasOwner()
    {   return owner != null;   }
    
    public boolean isFree()
    {   return !hasOwner(); }
    
    public boolean isCompatible(Criminal crim)
    {   return owner.hasLevel(crim.level()); }
        
    public void set(Criminal crim)
    {   owner = crim;   }
    
    public boolean has(Criminal crim)
    {   return owner == crim;   }
    
    public void clear()
    {   owner = null;   }
    
    public Criminal owner()
    {   return owner;  }
}
