package model;

import java.util.*;

public class Viewable
{
    private LinkedList<View> views = new LinkedList<View>();
    
    public void attach(View view)
    {
        views.add(view);
    }
    
    public void detach(View view)
    {
        views.remove(view);
    }
                
    public void update()
    {
        for (View view: views)
            view.update();
    }
}