package model;

import java.util.*;

public class Date extends GregorianCalendar
{   public Date(Date Date)
    {   setLenient(false);
        set(Date);    }

    public void set(Date date)
    {   set(date.year(), date.month() - 1, date.day()); }
    
    public Date(int day, int month, int year)
    {   setLenient(false);
        set(year, month - 1, day);  }
    
    public void add(int days)
    {   add(5, days);   }
    
    public int day()
    {   return get(5);  }
    
    public int month()
    {   return get(2) + 1;  }
    
    public int year()
    {   return get(1);  }
}
