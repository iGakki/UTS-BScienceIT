package model;

public enum Name
{   murder(3), arson(3), assault(3), 
    fraud(2), theft(2), vandalism(2),
    drunk(1), littering(1), badHair(1);
    
    public static Name matching(String target)
    {   for (Name name: Name.values())
            if (name.toString().equals(target))
                return name;
        return null;    }
    
    private int level;
    
    Name(int level)
    {   this.level = level;    }
    
    public int level()
    {   return level;   }
}
