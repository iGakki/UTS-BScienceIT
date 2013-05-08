package model;

import java.util.*;

public class Period
{   private final int daysInYear = 365;
    private final int daysInMonth = 30;
    private int days, months, years;

    public Period(int days, int months, int years)
    {   this.days = days;
        this.months = months;
        this.years = years; }

    public int toDays()
    {   int days = this.days;
        days += months * daysInMonth;
        days += years * daysInYear;
        return days;    }
}
