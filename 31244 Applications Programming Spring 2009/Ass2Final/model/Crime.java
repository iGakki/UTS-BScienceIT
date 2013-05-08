package model;

import java.util.*;

public class Crime
{   private Name name;
    private Period period;
    private Date start, end;
    
    public Crime(String name)
    {   this.name = Name.matching(name);    }
    
    public void set(Period period)
    {   this.period = period;
        start = new Date(Prison.today());
        end = new Date(Prison.today());
        end.add(period.toDays() - 1);    }

    public int level()
    {   return name.level();    }
}
