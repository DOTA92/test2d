/*   -------------------------------------------------------   */
/*    Vladimir Salnikov (GM3N LMNO University of Caen) 2015    */
/*   -------------------------------------------------------   */ 


//#include "geom.h"


//int IntersectsAll(fig1 sp1, fig2 sp2); //take into account also periodicity


template <class fig1, class fig2>
int IntersectsAll(fig1 sp1, fig2 sp2)
{
  int res = 0;
  if(!sp1.wall_x && !sp1.wall_y && !sp1.wall_z && !sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
  }  
  
  //One wall 
  if(sp1.wall_x && !sp1.wall_y && !sp1.wall_z && !sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
  }
  if(!sp1.wall_x && sp1.wall_y && !sp1.wall_z && !sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
  }
  if(!sp1.wall_x && !sp1.wall_y && sp1.wall_z && !sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
  }
  if(!sp1.wall_x && !sp1.wall_y && !sp1.wall_z && sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
  }
  if(!sp1.wall_x && !sp1.wall_y && !sp1.wall_z && !sp2.wall_x && sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
  }
  if(!sp1.wall_x && !sp1.wall_y && !sp1.wall_z && !sp2.wall_x && !sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
  }

  //Two walls
  if(sp1.wall_x && sp1.wall_y && !sp1.wall_z && !sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = ((sp1.Shift(1, -sp1.wall_x))).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
  }
  if(sp1.wall_x && !sp1.wall_y && sp1.wall_z && !sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = ((sp1.Shift(1, -sp1.wall_x))).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
  }
  if(!sp1.wall_x && sp1.wall_y && sp1.wall_z && !sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = ((sp1.Shift(3, -sp1.wall_z))).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
  }
  if(!sp1.wall_x && !sp1.wall_y && !sp1.wall_z && sp2.wall_x && sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
    res = ((sp2.Shift(1, -sp2.wall_x))).Shift(2, -sp2.wall_y).Intersects(sp1);
    if(res) return 1;
  }
  if(!sp1.wall_x && !sp1.wall_y && !sp1.wall_z && sp2.wall_x && !sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
    res = ((sp2.Shift(1, -sp2.wall_x))).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
  }
  if(!sp1.wall_x && !sp1.wall_y && !sp1.wall_z && !sp2.wall_x && sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
    res = ((sp2.Shift(3, -sp2.wall_z))).Shift(2, -sp2.wall_y).Intersects(sp1);
    if(res) return 1;
  }

  
  if(sp1.wall_x && !sp1.wall_y && !sp1.wall_z && sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
  }
  if(sp1.wall_x && !sp1.wall_y && !sp1.wall_z && !sp2.wall_x && sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
  }
  if(sp1.wall_x && !sp1.wall_y && !sp1.wall_z && !sp2.wall_x && !sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
  }  

  if(!sp1.wall_x && sp1.wall_y && !sp1.wall_z && sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
  }
  if(!sp1.wall_x && sp1.wall_y && !sp1.wall_z && !sp2.wall_x && sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
  }
  if(!sp1.wall_x && sp1.wall_y && !sp1.wall_z && !sp2.wall_x && !sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
  }  
  
  if(!sp1.wall_x && !sp1.wall_y && sp1.wall_z && sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
  }
  if(!sp1.wall_x && !sp1.wall_y && sp1.wall_z && !sp2.wall_x && sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
  }
  if(!sp1.wall_x && !sp1.wall_y && sp1.wall_z && !sp2.wall_x && !sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
  }  
  
 
  //three walls
  //111000
  if(sp1.wall_x && sp1.wall_y && sp1.wall_z && !sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
  }  
  //000111
  if(!sp1.wall_x && !sp1.wall_y && !sp1.wall_z && sp2.wall_x && sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
  }  
  
  //110100  101100 011100
  if(sp1.wall_x && sp1.wall_y && !sp1.wall_z && sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
  }  
  if(sp1.wall_x && !sp1.wall_y && sp1.wall_z && sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
  }  
  if(!sp1.wall_x && sp1.wall_y && sp1.wall_z && sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(3, -sp1.wall_z).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(3, -sp1.wall_z).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
  }  
  
 //110010  101010 011010
 if(sp1.wall_x && sp1.wall_y && !sp1.wall_z && !sp2.wall_x && sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
  }  
  if(sp1.wall_x && !sp1.wall_y && sp1.wall_z && !sp2.wall_x && sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
  }  
  if(!sp1.wall_x && sp1.wall_y && sp1.wall_z && !sp2.wall_x && sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(3, -sp1.wall_z).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(3, -sp1.wall_z).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
  }  
  //110001  101001 011001
    if(sp1.wall_x && sp1.wall_y && !sp1.wall_z && !sp2.wall_x && !sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
  }  
  if(sp1.wall_x && !sp1.wall_y && sp1.wall_z && !sp2.wall_x && !sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
  }  
  if(!sp1.wall_x && sp1.wall_y && sp1.wall_z && !sp2.wall_x && !sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(3, -sp1.wall_z).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(3, -sp1.wall_z).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
  }  

  
    //110100  101100 011100
  if(sp2.wall_x && sp2.wall_y && !sp2.wall_z && sp1.wall_x && !sp1.wall_y && !sp1.wall_z)
  { 
    res = sp2.Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1);
    if(res) return 1;
    res = sp2.Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
  }  
  if(sp2.wall_x && !sp2.wall_y && sp2.wall_z && sp1.wall_x && !sp1.wall_y && !sp1.wall_z)
  { 
    res = sp2.Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = sp2.Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
  }  
  if(!sp2.wall_x && sp2.wall_y && sp2.wall_z && sp1.wall_x && !sp1.wall_y && !sp1.wall_z)
  { 
    res = sp2.Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(3, -sp2.wall_z).Shift(2, -sp2.wall_y).Intersects(sp1);
    if(res) return 1;
    res = sp2.Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2).Shift(3, -sp2.wall_z).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
  }  
  
 //110010  101010 011010
 if(sp2.wall_x && sp2.wall_y && !sp2.wall_z && !sp1.wall_x && sp1.wall_y && !sp1.wall_z)
  { 
    res = sp2.Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1);
    if(res) return 1;
    res = sp2.Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
  }  
  if(sp2.wall_x && !sp2.wall_y && sp2.wall_z && !sp1.wall_x && sp1.wall_y && !sp1.wall_z)
  { 
    res = sp2.Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = sp2.Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
  }  
  if(!sp2.wall_x && sp2.wall_y && sp2.wall_z && !sp1.wall_x && sp1.wall_y && !sp1.wall_z)
  { 
    res = sp2.Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(3, -sp2.wall_z).Shift(2, -sp2.wall_y).Intersects(sp1);
    if(res) return 1;
    res = sp2.Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(3, -sp2.wall_z).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
  }  
  //110001  101001 011001
    if(sp2.wall_x && sp2.wall_y && !sp2.wall_z && !sp1.wall_x && !sp1.wall_y && sp1.wall_z)
  { 
    res = sp2.Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1);
    if(res) return 1;
    res = sp2.Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
  }  
  if(sp2.wall_x && !sp2.wall_y && sp2.wall_z && !sp1.wall_x && !sp1.wall_y && sp1.wall_z)
  { 
    res = sp2.Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = sp2.Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
  }  
  if(!sp2.wall_x && sp2.wall_y && sp2.wall_z && !sp1.wall_x && !sp1.wall_y && sp1.wall_z)
  { 
    res = sp2.Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(3, -sp2.wall_z).Shift(2, -sp2.wall_y).Intersects(sp1);
    if(res) return 1;
    res = sp2.Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(3, -sp2.wall_z).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
  }  

  //four walls

  //111100 111010 111001
  if(sp1.wall_x && sp1.wall_y && sp1.wall_z && sp2.wall_x && !sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
  }  
  if(sp1.wall_x && sp1.wall_y && sp1.wall_z && !sp2.wall_x && sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
  }  
  if(sp1.wall_x && sp1.wall_y && sp1.wall_z && !sp2.wall_x && !sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
  }  

    //100111 010111 001111
  if(sp2.wall_x && sp2.wall_y && sp2.wall_z && sp1.wall_x && !sp1.wall_y && !sp1.wall_z)
  { 
    res = sp2.Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = sp2.Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
  }  
  if(sp2.wall_x && sp2.wall_y && sp2.wall_z && !sp1.wall_x && sp1.wall_y && !sp1.wall_z)
  { 
    res = sp2.Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = sp2.Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
  }  
  if(sp2.wall_x && sp2.wall_y && sp2.wall_z && !sp1.wall_x && !sp1.wall_y && sp1.wall_z)
  { 
    res = sp2.Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = sp2.Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
  }  

  //110110
  if(sp1.wall_x && sp1.wall_y && !sp1.wall_z && sp2.wall_x && sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1,-sp2.wall_x).Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(2,-sp2.wall_y));
    if(res) return 1;
  }  
  //110101
  if(sp1.wall_x && sp1.wall_y && !sp1.wall_z && sp2.wall_x && !sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1,-sp2.wall_x).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(3,-sp2.wall_z));
    if(res) return 1;
  }  
  //110011
  if(sp1.wall_x && sp1.wall_y && !sp1.wall_z && !sp2.wall_x && sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2,-sp2.wall_y).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(2,-sp2.wall_y).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(2,-sp2.wall_y).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(2,-sp2.wall_y).Shift(3,-sp2.wall_z));
    if(res) return 1;
  }  

  //101110
  if(sp1.wall_x && !sp1.wall_y && sp1.wall_z && sp2.wall_x && sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1,-sp2.wall_x).Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(2,-sp2.wall_y));
    if(res) return 1;
  }  
  //101101
  if(sp1.wall_x && !sp1.wall_y && sp1.wall_z && sp2.wall_x && !sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1,-sp2.wall_x).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(3,-sp2.wall_z));
    if(res) return 1;
  }  
  //101011
  if(sp1.wall_x && !sp1.wall_y && sp1.wall_z && !sp2.wall_x && sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2,-sp2.wall_y).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(2,-sp2.wall_y).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(2,-sp2.wall_y).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2,-sp2.wall_y).Shift(3,-sp2.wall_z));
    if(res) return 1;
  }  
  
   //011110
  if(!sp1.wall_x && sp1.wall_y && sp1.wall_z && sp2.wall_x && sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1,-sp2.wall_x).Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(2,-sp2.wall_y));
    if(res) return 1;
  }  
  //011101
  if(!sp1.wall_x && sp1.wall_y && sp1.wall_z && sp2.wall_x && !sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1,-sp2.wall_x));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(1,-sp2.wall_x).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1,-sp2.wall_x).Shift(3,-sp2.wall_z));
    if(res) return 1;
  }  
  //011011
  if(!sp1.wall_x && sp1.wall_y && sp1.wall_z && !sp2.wall_x && sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2,-sp2.wall_y));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = sp1.Intersects(sp2.Shift(2,-sp2.wall_y).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(2,-sp2.wall_y).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(2,-sp2.wall_y).Shift(3,-sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2,-sp2.wall_y).Shift(3,-sp2.wall_z));
    if(res) return 1;
  }  

  // five walls
  //111011  
  if(sp1.wall_x && sp1.wall_y && sp1.wall_z && !sp2.wall_x && sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;

    res = sp1.Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;

    res = sp1.Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;

    res = sp1.Intersects(sp2.Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z));
    if(res) return 1;
    
  }  
  
  //111101  
  if(sp1.wall_x && sp1.wall_y && sp1.wall_z && sp2.wall_x && !sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;

    res = sp1.Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;

    res = sp1.Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;

    res = sp1.Intersects(sp2.Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z));
    if(res) return 1;
    
  }  
    //111110  
  if(sp1.wall_x && sp1.wall_y && sp1.wall_z && sp2.wall_x && sp2.wall_y && !sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;

    res = sp1.Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;

    res = sp1.Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;

    res = sp1.Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
  }  

  //011111  
  if(sp2.wall_x && sp2.wall_y && sp2.wall_z && !sp1.wall_x && sp1.wall_y && sp1.wall_z)
  { 
    res = sp2.Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;

    res = sp2.Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;

    res = sp2.Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;

    res = sp2.Intersects(sp1.Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z));
    if(res) return 1;
    
  }  
  
  //101111  
  if(sp2.wall_x && sp2.wall_y && sp2.wall_z && sp1.wall_x && !sp1.wall_y && sp1.wall_z)
  { 
    res = sp2.Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;

    res = sp2.Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;

    res = sp2.Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(3, -sp1.wall_z));
    if(res) return 1;

    res = sp2.Intersects(sp1.Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z));
    if(res) return 1;
    
  }  
    //110111  
  if(sp2.wall_x && sp2.wall_y && sp2.wall_z && sp1.wall_x && sp1.wall_y && !sp1.wall_z)
  { 
    res = sp2.Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1);
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1);
    if(res) return 1;

    res = sp2.Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x));
    if(res) return 1;

    res = sp2.Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(2, -sp1.wall_y));
    if(res) return 1;

    res = sp2.Intersects(sp1.Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(1, -sp2.wall_x)).Intersects(sp1.Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(2, -sp2.wall_y)).Intersects(sp1.Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2.Shift(3, -sp2.wall_z)).Intersects(sp1.Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Intersects(sp1.Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y));
    if(res) return 1;
    res = (sp2).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y).Shift(3, -sp2.wall_z).Intersects(sp1.Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y));
    if(res) return 1;
  }  
  
  //six walls

      //111111  
  if(sp1.wall_x && sp1.wall_y && sp1.wall_z && sp2.wall_x && sp2.wall_y && sp2.wall_z)
  { 
    res = sp1.Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2);
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2);
    if(res) return 1;

    res = sp1.Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x));
    if(res) return 1;

    res = sp1.Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(2, -sp2.wall_y));
    if(res) return 1;

    res = sp1.Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    
    
      res = sp1.Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z));
    if(res) return 1;

    res = sp1.Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x));
    if(res) return 1;

    res = sp1.Intersects(sp2.Shift(3, -sp2.wall_z).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(2, -sp2.wall_y));
    if(res) return 1;

    res = sp1.Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(1, -sp1.wall_x)).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(2, -sp1.wall_y)).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1.Shift(3, -sp1.wall_z)).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;
    res = (sp1).Shift(1, -sp1.wall_x).Shift(2, -sp1.wall_y).Shift(3, -sp1.wall_z).Intersects(sp2.Shift(3, -sp2.wall_z).Shift(1, -sp2.wall_x).Shift(2, -sp2.wall_y));
    if(res) return 1;

    
    
    
    
  }  

  
  return 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
