package model;

import java.util.*;

public class Cells
{   private LinkedList<Cell> cells = new LinkedList<Cell>();

    public Cells()
    {   for (int floor = 1; floor <= 2; floor++)
            for (int cell = 1; cell <= 10; cell++)
            {   String id = "" + floor + "." + cell;
                if ((cell % 2) == 0)
                    cells.add(new Cell(id, 2));
                else
                    cells.add(new Cell(id, 1)); }}

    public void allocate(Criminal crim)
    {   Cell cell = nextFree(crim);
        cell.set(crim); }
        
    public Cell nextFree(Criminal crim)
    {   for (Cell cell: cells)
            if (cell.isFull())
                continue;
            else if (cell.fits(crim))
                return cell;
        return null;    }
        
    public Cell get(int i)
    {   return cells.get(i);   }
}
