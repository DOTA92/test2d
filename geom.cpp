/*   -------------------------------------------------------   */
/*    Vladimir Salnikov (GM3N LMNO University of Caen) 2015    */
/*   -------------------------------------------------------   */ 


#include "geom.h"

#include "period.cpp"
//Cylinders

Cylinder::Cylinder(Vec3D _p, long double _r, Vec3D _l)
{
  p = _p;
  r= _r;
  l = _l;
  FillWalls();
}

void Cylinder::FillWalls()
{
   wall_x = 0;
   wall_y = 0;
   wall_z = 0;
   
   Plane pl;
   
   pl.n = Vec3D(1,0,0);
   pl.pt = Vec3D(0,0,0);
   if(Intersects(pl)) wall_x = -1;
   pl.n = Vec3D(-1,0,0);
   pl.pt = Vec3D(1,1,1);
   if(Intersects(pl)) wall_x = 1;

   pl.n = Vec3D(0,1,0);
   pl.pt = Vec3D(0,0,0);
   if(Intersects(pl)) wall_y = -1;
   pl.n = Vec3D(0,-1,0);
   pl.pt = Vec3D(1,1,1);
   if(Intersects(pl)) wall_y = 1;
   
   
   pl.n = Vec3D(0,0,1);
   pl.pt = Vec3D(0,0,0);
   if(Intersects(pl)) wall_z = -1;
   pl.n = Vec3D(0,0,-1);
   pl.pt = Vec3D(1,1,1);
   if(Intersects(pl)) wall_z = 1;
   
  
  
}


void Cylinder::print(FILE *fp)
{
//  printf("Center: (%Lg, %Lg, %Lg), rad = %Lg \n", x, y, z, r);
  fprintf(fp, "%Lg %Lg %Lg %Lg %Lg %Lg %Lg \n", p.x, p.y, p.z, r, l.x, l.y, l.z);
}

int Cylinder::PointInside(Vec3D p1)
{
  long double lnorm, X, tmp, leff, reff;
  lnorm = l.norm(); 
  X = (p1-p)*l/lnorm;  
  
  tmp = (p1-p)*(p1-p) - X*X;
  
  
  leff = lnorm; //  *(1. + wave*sin(3.*M_PI*sqrt(fabs(tmp))/r) )  ;
  
  reff = r*(1. + wave*cos(3.*M_PI*X/lnorm));
 
  
  
  if(fabs(X) > leff) return 0;
  
  if (tmp > reff*reff) return 0;
  
  return 1;
//  return(  ((p1-p)*(p1-p) - X*X) < r*r );
  
}

int Cylinder::Intersects(Plane pl)
{
    Vec3D binorm, v;
    
    binorm = pl.n ^ l;
    
    if( binorm.norm()>0.001 )
    {
      v = l^binorm;
            v = r*v/v.norm();

      
      if( ( (p + l + v - pl.pt)*pl.n )*( (p - l - v - pl.pt)*pl.n ) < 0  )
      {
	return 1;
      }
      if( ( (p + l - v - pl.pt)*pl.n )*( (p - l + v - pl.pt)*pl.n ) < 0  )
      {
	return 1;
      }
      
      return 0;
      
    }
    else
    {
       if( fabs((p-pl.pt)*pl.n/pl.n.norm()) < r )
       {
	 return 1;
	 
       }
       return 0;
      
      
    }
    
    
}


int Disk::Intersects(Disk d)
{
  Vec3D binorm, l, pt;
  double t, dist1, dist2;
  
  binorm = n^d.n;
  l = binorm^n;
  t = d.n*(d.p - p)/(d.n*l);
  
  pt = p + t*l;
  
  dist1 = (p-pt).norm();
  dist2 = (d.p-pt).norm();
  
  if((dist1 < r)&&(dist2 < d.r))
  {
    return 1;
  }
  
     return 0;
  
  
}



int Cylinder::Intersects(Disk d)
{
  long double t, X, tmp;
  Vec3D pt, a, b;
  
  t = ((d.p-p)*d.n)/(l*d.n);
  a = p + t*l;
  
  pt = d.r*(-1.*d.p + a)/(-1.*d.p + a).norm() + d.p;
  
  X = (pt- p)*l/l.norm();
  
  if(fabs(X)<l.norm())
  {
  
    b = p + X*l/l.norm();
  
      tmp = (b - pt).norm() - r;
      if(tmp<0)
      {
	return 1;
      }
  
  }
  
  if(((a-d.p).norm() < d.r)&&((a-p).norm() < l.norm()) )    //never for identical cylinders
  {
    return 1;
  }
 
 return 0;
 
 //Always check disk-disk intersection as well!!!
  
  
}

int Cylinder::Intersects(Cylinder cyl)
{
  long double rho, t1, t2;
  Vec3D n1, n2, n;
  
  n = l^cyl.l;
  n = n/n.norm();
  rho = (p - cyl.p)*n;
  
  if (fabs(rho) > r + cyl.r) return 0;   //lines too far to intersect
  
  n1 = n^l;
  n2 = n^cyl.l;
  
  t1 = ((cyl.p-p)*n2)/(l*n2);
  t2 = ((p-cyl.p)*n1)/(cyl.l*n1);
  
  if((fabs(t1)<1.)&&(fabs(t2)<1.))   //intersection by the cylindrical face
  {
    if(fabs(rho) < r + cyl.r) return 1;
  }
  

  //Intersections with the disks:
  
  Disk d;
  
  d.p = p + l;
  d.n = l; 
  d.r = r;
  if (cyl.Intersects(d)) return 1;

  d.p = p - l;
  d.n = -1.*l; 
  d.r = r;
  if (cyl.Intersects(d)) return 1;
  
  d.p = cyl.p + cyl.l;
  d.n = cyl.l; 
  d.r = cyl.r;
  if (Intersects(d)) return 1;

  d.p = cyl.p - cyl.l;
  d.n = -1.*cyl.l; 
  d.r = cyl.r;
  if (Intersects(d)) return 1;
  
   
  //Intersection of disks with disks
  Disk cd;
  
  d.p = p + l;
  d.n = l; 
  d.r = r;
  
  cd.p = cyl.p + cyl.l;
  cd.n = cyl.l; 
  cd.r = cyl.r;
  
  if(d.Intersects(cd)) return 1;
  
  d.p = p - l;
  d.n = l; 
  d.r = r;
  
  cd.p = cyl.p + cyl.l;
  cd.n = cyl.l; 
  cd.r = cyl.r;
  
  if(d.Intersects(cd)) return 1;
  
  d.p = p + l;
  d.n = l; 
  d.r = r;
  
  cd.p = cyl.p - cyl.l;
  cd.n = cyl.l; 
  cd.r = cyl.r;
  
  if(d.Intersects(cd)) return 1;
  
  d.p = p - l;
  d.n = l; 
  d.r = r;
  
  cd.p = cyl.p - cyl.l;
  cd.n = cyl.l; 
  cd.r = cyl.r;
  
  if(d.Intersects(cd)) return 1;
  
  
  
  
  
  return 0 ;
}

int Cylinder::Intersects(Sphere sp)
{
 long double L, X, lnorm;
  lnorm = l.norm();
  
  X = (sp.p-p)*l/lnorm;
  
  if(fabs(X) > lnorm + sp.r) return 0;  //projection out of half axis + r_sphere
  
  if(fabs(X)<lnorm)   //projection inside cylinder
  {
    return ( (sp.p-p)*(sp.p-p) - X*X < (sp.r + r)*(sp.r + r) );   
  }

  L = sqrt(fabs((sp.p-p)*(sp.p-p) - X*X));   //boundary state -- check distance to the disk
  
  return (L < sqrt(sp.r*sp.r - (fabs(X)-lnorm)*(fabs(X)-lnorm)) + r);
  
  
 }
  
Cylinder Cylinder::Shift(int coord, double shift)
{
  Cylinder tmp(p, r, l);
  if(coord == 1)
  {
     tmp.p.x += shift;
  }
  if(coord == 2)
  {
     tmp.p.y += shift;
  }
  if(coord == 3)
  {
     tmp.p.z += shift;
  }
  tmp.wave = wave;
  return tmp;
}


//++++++++++++++++++++++++ Spheres

Sphere::Sphere(Vec3D _p, long double _r)
{
  p = _p; 
  r= _r;
//  wall_x = 0; wall_y = 0; wall_z = 0;
}

void Sphere::print(FILE *fp)
{
//  printf("Center: (%Lg, %Lg, %Lg), rad = %Lg \n", x, y, z, r);
  fprintf(fp, "%Lg %Lg %Lg %Lg \n", p.x, p.y, p.z, r);
}

int Sphere::PointInside(Vec3D p1)
{
  
   double reff, tmp;
   Vec3D cent;
   cent = Vec3D(0.5, 0.5, 0.5);

   tmp = 0.95*(p1 - cent)*(p-cent)/((p1 - cent).norm()*(p-cent).norm());
   tmp = cos(7.*M_PI*acos(tmp));
   
   reff = r*(1. + wave*tmp);
   
   return ( (p1-p)*(p1-p) < reff*reff );
   
  
}

int Sphere::Intersects(Sphere sp)
{
  return( ((sp.p - p)*(sp.p - p)) < ((sp.r+r)*(sp.r+r)) );
}

int Sphere::Intersects(Cylinder cyl)
{
  long double L, X, lnorm;
  lnorm = cyl.l.norm();
  
  X = (p-cyl.p)*cyl.l/lnorm;
  
  if(fabs(X) > lnorm + r) return 0;  //projection out of half axis + r_sphere
  
  if(fabs(X)<lnorm)   //projection inside cylinder
  {
    return ( (p-cyl.p)*(p-cyl.p) - X*X < (r + cyl.r)*(r + cyl.r) );   
  }

  L = sqrt(fabs((p-cyl.p)*(p-cyl.p) - X*X));   //boundary state -- check distance to the disk
  
  return (L < sqrt(r*r - (fabs(X)-lnorm)*(fabs(X)-lnorm)) + cyl.r);
  
}



  
Sphere Sphere::Shift(int coord, double shift)
{
  Sphere tmp(p, r);
  if(coord == 1)
  {
     tmp.p.x += shift;
  }
  if(coord == 2)
  {
     tmp.p.y += shift;
  }
  if(coord == 3)
  {
     tmp.p.z += shift;
  }
  tmp.wave = wave;
  return tmp;
}



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


Geometry::Geometry(double __fraction_sp, double __fraction_cyl, double __fraction_def, int __num_spheres, int __num_cylinders, int __num_defects, int __resolution, double __aspect, double __wave)
{
   srand ( time(NULL) );
  
  fraction_sp = __fraction_sp;
  fraction_cyl = __fraction_cyl;
  fraction_def = __fraction_def;
  num_spheres = __num_spheres;
  num_cylinders = __num_cylinders;
  num_defects = __num_defects;
  resolution = __resolution;

  num_generated_spheres = 0;
  num_rejected_spheres = 0;
  num_generated_defects = 0;
  num_rejected_defects = 0;
  num_generated_cylinders = 0;
  num_rejected_cylinders = 0;  

  spheres = (Sphere *) malloc(num_spheres*sizeof(Sphere));
  cylinders = (Cylinder *) malloc(num_cylinders*sizeof(Cylinder));
  defects = (Sphere *) malloc(num_defects*sizeof(Sphere));

  aspect =  __aspect;
  wave = __wave;

  double rad; 
  int i;
  rad = pow((3.*fraction_sp)/(num_spheres*4.*M_PI), 1./3.);
  for(i = 0; i<num_spheres; i++)
  {
    spheres[i].r = rad;
    spheres[i].wave = wave;
  }
  
  rad = pow((fraction_cyl)/(num_cylinders*M_PI*2.*aspect), 1./3.);  //length = aspect*diam
  for(i = 0; i<num_cylinders; i++)
  {
    cylinders[i].r = rad;
    cylinders[i].wave = wave;
  }
    
  rad = pow((3.*fraction_def)/(num_defects*4.*M_PI), 1./3.);
  for(i = 0; i<num_defects; i++)
  {
    defects[i].r = rad;
    defects[i].wave = 0;
  }

    
    
}

int Geometry::PointInsideFigures(Vec3D p)
{
  int i, in, spoilt=0;
  
  for(i = 0; ((i<num_defects)&&(!spoilt)); i++)
  {
    if(defects[i].PointInside(p))
    {
      spoilt = 1;
      p = p.Symmetric(defects[i].p);
    }
  }

  
  
  
  for(i=0; i<num_spheres; i++)
  {
    if(spheres[i].PointInside(p)) return 1;
    
    if(spheres[i].wall_x)
    {
      if(spheres[i].Shift(1, -spheres[i].wall_x).PointInside(p))  return 1; 
    }
    if(spheres[i].wall_y)
    {
      if(spheres[i].Shift(2, -spheres[i].wall_y).PointInside(p))  return 1; 
    }
    if(spheres[i].wall_z)
    {
      if(spheres[i].Shift(3, -spheres[i].wall_z).PointInside(p))  return 1; 
    }
    
    if(spheres[i].wall_x && spheres[i].wall_y)
    {
      if(spheres[i].Shift(1, -spheres[i].wall_x).Shift(2, -spheres[i].wall_y).PointInside(p))  return 1; 
    }
    if(spheres[i].wall_x && spheres[i].wall_z)
    {
      if(spheres[i].Shift(1, -spheres[i].wall_x).Shift(3, -spheres[i].wall_z).PointInside(p))  return 1; 
    }
    if(spheres[i].wall_y && spheres[i].wall_z)
    {
      if(spheres[i].Shift(3, -spheres[i].wall_z).Shift(2, -spheres[i].wall_y).PointInside(p))  return 1; 
    }

    if(spheres[i].wall_x && spheres[i].wall_y && spheres[i].wall_z)
    {
      if(spheres[i].Shift(3, -spheres[i].wall_z).Shift(2, -spheres[i].wall_y).Shift(1, -spheres[i].wall_x).PointInside(p))  return 1; 
    }
  }
  
    for(i=0; i<num_cylinders; i++)
  {
    if(cylinders[i].PointInside(p)) return 1;
    
    if(cylinders[i].wall_x)
    {
      if(cylinders[i].Shift(1, -cylinders[i].wall_x).PointInside(p))  return 1; 
    }
    if(cylinders[i].wall_y)
    {
      if(cylinders[i].Shift(2, -cylinders[i].wall_y).PointInside(p))  return 1; 
    }
    if(cylinders[i].wall_z)
    {
      if(cylinders[i].Shift(3, -cylinders[i].wall_z).PointInside(p))  return 1; 
    }
    
    if(cylinders[i].wall_x && cylinders[i].wall_y)
    {
      if(cylinders[i].Shift(1, -cylinders[i].wall_x).Shift(2, -cylinders[i].wall_y).PointInside(p))  return 1; 
    }
    if(cylinders[i].wall_x && cylinders[i].wall_z)
    {
      if(cylinders[i].Shift(1, -cylinders[i].wall_x).Shift(3, -cylinders[i].wall_z).PointInside(p))  return 1; 
    }
    if(cylinders[i].wall_y && cylinders[i].wall_z)
    {
      if(cylinders[i].Shift(3, -cylinders[i].wall_z).Shift(2, -cylinders[i].wall_y).PointInside(p))  return 1; 
    }

    if(cylinders[i].wall_x && cylinders[i].wall_y && cylinders[i].wall_z)
    {
      if(cylinders[i].Shift(3, -cylinders[i].wall_z).Shift(2, -cylinders[i].wall_y).Shift(1, -cylinders[i].wall_x).PointInside(p))  return 1; 
    }
  }

  
  
  
  return 0;
}

int Geometry::AnotherSphere()
{
  double rad, tmp;
  int valid = 0, i;
  
  rad = spheres[num_generated_spheres].r;
    
  while(!valid)
  {
   tmp =((double)rand())/RAND_MAX;
   if(tmp<rad) spheres[num_generated_spheres].wall_x = -1;
   if((tmp>=rad)&&(1.-tmp>=rad)) spheres[num_generated_spheres].wall_x = 0;
   if(1.-tmp<rad) spheres[num_generated_spheres].wall_x = 1;
   spheres[num_generated_spheres].p.x = tmp;;
   
   tmp =((double)rand())/RAND_MAX;
   if(tmp<rad) spheres[num_generated_spheres].wall_y = -1;
   if((tmp>=rad)&&(1.-tmp>=rad)) spheres[num_generated_spheres].wall_y = 0;
   if(1.-tmp<rad) spheres[num_generated_spheres].wall_y = 1;
   spheres[num_generated_spheres].p.y = tmp;;

   tmp =((double)rand())/RAND_MAX;
   if(tmp<rad) spheres[num_generated_spheres].wall_z = -1;
   if((tmp>=rad)&&(1.-tmp>=rad)) spheres[num_generated_spheres].wall_z = 0;
   if(1.-tmp<rad) spheres[num_generated_spheres].wall_z = 1;
   spheres[num_generated_spheres].p.z = tmp;;
   
   valid = 1;
   for(i = 0; (i<num_generated_spheres)&&valid; i++)
   {
      if(IntersectsAll<Sphere, Sphere>(spheres[num_generated_spheres], spheres[i])) 
      {
	valid = 0;
      }
   }
   for(i = 0; (i<num_generated_cylinders)&&valid; i++)
   {
      if(IntersectsAll<Sphere, Cylinder>(spheres[num_generated_spheres], cylinders[i])) 
      {
	valid = 0;
      }
   }
   num_rejected_spheres++;
   
   if(num_rejected_spheres > 1e8)
   {
     num_rejected_spheres = 1;
     num_generated_spheres = 0;
     num_rejected_cylinders = 0;
     num_generated_cylinders = 0;

     printf("\ngeneration restarted\n");
   }
   
  }
   
   num_rejected_spheres--; 
   num_generated_spheres++;
  
 //     printf("\n Generated %d out of %d spheres, rejected %d\n", num_generated_spheres, num_spheres, num_rejected_spheres);

   return 0;
}


int Geometry::AnotherCylinder()
{
  double length, tmp, px, py, pz, lx, ly, lz, rad;
  int valid = 0, i;
  
  rad = cylinders[num_generated_cylinders].r;
  length = aspect*rad;
    
  while(!valid)
  {
   tmp =((double)rand())/RAND_MAX;
   cylinders[num_generated_cylinders].p.x = tmp;
   
   tmp =((double)rand())/RAND_MAX;
   cylinders[num_generated_cylinders].p.y = tmp;;

   tmp =((double)rand())/RAND_MAX;
   cylinders[num_generated_cylinders].p.z = tmp;
   
   
   cylinders[num_generated_cylinders].l.x =((double)rand())/RAND_MAX - 0.5;
   cylinders[num_generated_cylinders].l.y =((double)rand())/RAND_MAX - 0.5;
   cylinders[num_generated_cylinders].l.z =((double)rand())/RAND_MAX - 0.5;

   tmp = cylinders[num_generated_cylinders].l.norm();
   
   cylinders[num_generated_cylinders].l.x  *=length/tmp;
   cylinders[num_generated_cylinders].l.y *=length/tmp;
   cylinders[num_generated_cylinders].l.z *=length/tmp;
   
   cylinders[num_generated_cylinders].FillWalls();
    
   
   
   
   
   valid = 1;
   for(i = 0; (i<num_generated_cylinders)&&valid; i++)
   {
     if(IntersectsAll<Cylinder, Cylinder>(cylinders[num_generated_cylinders], cylinders[i]))   
      {
	valid = 0;
      }
   }
   for(i = 0; (i<num_generated_spheres)&&valid; i++)
   {
      if(IntersectsAll<Sphere, Cylinder>(spheres[i], cylinders[num_generated_cylinders]))   
      {
	valid = 0;
      }
   }

   num_rejected_cylinders++;
   
   if(num_rejected_cylinders > 1e8)
   {
     num_rejected_spheres = 0;
     num_generated_spheres = 0;
     num_rejected_cylinders = 1;
     num_generated_cylinders = 0;

     printf("\ngeneration restarted\n");
   }

   
  }
   
   num_rejected_cylinders--; 
   num_generated_cylinders++;
  
 //     printf("\n Generated %d out of %d cylinders, rejected %d\n", num_generated_cylinders, num_cylinders, num_rejected_cylinders);

   return 0;
}



int Geometry::AnotherDefect()
{
  double rad, tmp;
  int valid = 0, i;
  
  rad = defects[num_generated_defects].r;
    
  while(!valid)
  {
   tmp =(1.-2.*rad)*(((double)rand())/RAND_MAX) + rad;
   defects[num_generated_defects].p.x = tmp;
   
   tmp =(1.-2.*rad)*(((double)rand())/RAND_MAX) + rad;
   defects[num_generated_defects].p.y = tmp;

   tmp =(1.-2.*rad)*(((double)rand())/RAND_MAX) + rad;
    defects[num_generated_defects].p.z = tmp;
   
   valid = 1;
   for(i = 0; (i<num_generated_defects)&&valid; i++)
   {
      
      if(defects[num_generated_defects].Intersects(defects[i]) ) 
      {
	valid = 0;
      }
   }
  }

  num_generated_defects++;
  
//     printf("\n Generated %d out of %d defects\n", num_generated_defects, num_defects);

   return 0;
}




int Geometry::PositionFigures()
{
  num_generated_cylinders = 0;
  num_generated_spheres = 0;
  
  while((num_generated_cylinders<num_cylinders)||(num_generated_spheres<num_spheres))
  {
    if(num_generated_cylinders<num_cylinders)
    {
      AnotherCylinder();
    }
    
    if(num_generated_spheres<num_spheres)
    {
      AnotherSphere();
    }
  }

  
   while(num_generated_defects<num_defects)
  {
    AnotherDefect();
  }


  

  return 0;
}

void Geometry::Print(char prefix[128])
{
  FILE *fp;
 char filename[128];
  sprintf(filename, "%sspheres.out", prefix);
  
  fp = fopen(filename, "w");
  printf("\n Printing: Generated %d out of %d spheres, rejected %d\n", num_generated_spheres, num_spheres, num_rejected_spheres);
  for(int i=0; i<num_generated_spheres; i++)
  {
    spheres[i].print(fp);
  }
  fclose(fp);
  
  sprintf(filename, "%scylinders.out", prefix);
    fp = fopen(filename, "w");
    
  printf("\n Printing: Generated %d out of %d cylinders, rejected %d\n", num_generated_cylinders, num_cylinders, num_rejected_cylinders);
  for(int i=0; i<num_generated_cylinders; i++)
  {
    cylinders[i].print(fp);
  }
  fclose(fp);

  
}

void Geometry::ExportImages()
{
  FILE *fp;
  char filename[128];
  
  double cell, actual_fraction=0;
  cell = 1./((double)resolution);
  Vec3D pt;
  
  int i, j, k, in;

//   omp_set_dynamic(0);
//    omp_set_num_threads(4);

//   #pragma omp parallel for private(i,j,k, pt, in, fp, filename)
  for(k=0; k<resolution; k++)
  {
  /*  if(k<10)    sprintf(filename, "slice000%d.pbm", k);
    if((k>=10)&&(k<100))    sprintf(filename, "slice00%d.pbm", k);
    if((k>=100)&&(k<1000))    sprintf(filename, "slice0%d.pbm", k);
    if((k>=1000))    sprintf(filename, "slice%d.pbm", k);
    fp = fopen(filename, "w");
    
    fprintf(fp, "P1\n %d %d\n", resolution, resolution);
  */  
    for(i=0; i<resolution; i++)
    {
     	for(j=0; j<resolution; j++)
	{
	    pt = Vec3D(i*cell + cell/2., j*cell + cell/2., k*cell + cell/2);
	    in = PointInsideFigures(pt);
// 	    fprintf(fp, "%d ", in);
	    actual_fraction+= in;
	}
//	fprintf(fp, "\n");
    }
//     fclose(fp);
//     printf("\nSlice %d saved", k);
  }
  
  actual_fraction = actual_fraction/(resolution*resolution*resolution);
  
  printf("\n Generated %d out of %d spheres, rejected %d\n", num_generated_spheres, num_spheres, num_rejected_spheres);
  printf("\n Generated %d out of %d cylinders, rejected %d\n", num_generated_cylinders, num_cylinders, num_rejected_cylinders);
  
  
  printf("\n Actual fraction at resolution %d^3 = %lg \n", resolution, actual_fraction);
  
  
  fp = fopen(name, "a");
  
  fprintf(fp, "%d  %d  %.4lg  ", num_rejected_spheres, num_rejected_cylinders, actual_fraction);
  fclose(fp);
  
  
  
  
}


void Geometry::ExportSample(int size_x, int size_y, int size_z, int *sample, double &fraction)
{
  int i, j, k;
  int res_y = size_y, res_z=size_z, stat, in;
  long int n;
  n = 0;
  Vec3D pt;
  
  double dx, dy, dz;
  dx = 1./((double)(size_x));
  dy = 1./((double)(size_y));
  dz = 1./((double)(size_z));
  
  fraction = 0;
  
   for(k = 0; k<size_z; k++)
   {
    for(i = 0; i<size_x; i++)
    {
      for(j = 0; j<size_y; j++)
      {
	 pt = Vec3D(i*dx + dx/2., j*dy + dy/2., k*dz + dz/2.);
	 in = PointInsideFigures(pt);
	
	 sample[n] = in;
	 if(in>0)
	 {
	   fraction +=1;  
	 }
	 n++;
	
      }
    }

  }
  
  fraction /= (size_x * size_y * size_z);
  FILE *fp;
   fp = fopen(name, "a");
  
  fprintf(fp, " %lg  \n", fraction);
  printf("Actual fraction %lg  \n", fraction);
  fclose(fp);
}





