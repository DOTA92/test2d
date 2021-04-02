/*   -------------------------------------------------------   */
/*    Vladimir Salnikov (GM3N LMNO University of Caen) 2015    */
/*   -------------------------------------------------------   */ 


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

#include <time.h>  //generating initial data

#include <string.h>  //names of files
#include <dirent.h>

#include <omp.h>



//+++++++++++++++++ Vector algebra

struct Vec3D{
  long double x,y,z;

  Vec3D (): x(0), y(0), z(0) {}
  Vec3D (long double x0, long double y0, long double z0) : x(x0), y(y0), z(z0) {}
  Vec3D (const Vec3D& v): x(v.x), y(v.y), z(v.z) {}

		Vec3D& operator=(const Vec3D& v) 
		{
			x = v.x; y = v.y; z = v.z;
			return *this;
		}
		Vec3D operator+(const Vec3D& v) const 
		{
			return Vec3D(x+v.x, y+v.y, z+v.z);
		}

		Vec3D& operator+=(const Vec3D& v) 
		{
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		Vec3D operator-(const Vec3D& v) const 
		{
			return Vec3D(x-v.x, y-v.y, z-v.z);
		}

		Vec3D& operator-=(const Vec3D& v) 
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		Vec3D operator*(long double c) const 
		{
			return Vec3D(x*c, y*c, z*c);
		}

		Vec3D& operator*=(long double c) 
		{
			x *= c;
			y *= c;
			z *= c;
			return *this;
		}
                friend Vec3D operator*(const double& a, const Vec3D& b)
		{
		    return b*a;
		}
		Vec3D operator/(long double c) const 
		{
			return ( (1./c)*(*this) );
		}

	

		long double  operator*(const Vec3D& v) const 
		{
	  	         return x*v.x + y*v.y+ z*v.z;
		}
		
		Vec3D operator^(const Vec3D& v) const 
		{
			return Vec3D(y*v.z - z*v.y,- x*v.z +z*v.x, x*v.y - v.x*y);
		}

	      
	   void print()
	   {
	     printf("[%Lg, %Lg, %Lg] ", x, y, z);
	   }
	   
	   long double norm()
	   {
	     return sqrt(x*x + y*y + z*z);
	  }
	  
	    Vec3D Symmetric(Vec3D a)
	  {
	    return *this + 2*(a - *this);
	  }
};



//+++++++++++++++++++++++ SHAPES


struct Plane
{
  Vec3D pt, n;
};

class Sphere;
class Cylinder;
class Disk;

class Disk{
public:
  Vec3D p, n;
  long double r;
  
  int Intersects(Disk d);
};


class Sphere{
public:
  long double r, wave;
  Vec3D p;
  int wall_x, wall_y, wall_z; //0 if inside the box, -1 close to the left wall, +1 close to the right wall
  
  void print(FILE *fp);
  int PointInside(Vec3D p1);
  int Intersects(Sphere sp);
  int Intersects(Cylinder cyl);
  Sphere Shift(int coord, double shift);
  Sphere(Vec3D _p, long double _r);
  
};

class Cylinder{
public:
 long double r, wave;
 Vec3D p, l;
 int wall_x, wall_y, wall_z; //0 if inside the box, -1 close to the left wall, +1 close to the right wall
    
  void print(FILE *fp);
  int PointInside(Vec3D p1);
  int Intersects(Cylinder cyl);
  int Intersects(Sphere sp);
  int Intersects(Disk d);
  Cylinder Shift(int coord, double shift);
  Cylinder(Vec3D _p, long double _r, Vec3D _l);   
     int Intersects(Plane pl);
      void FillWalls();
     
};


class Geometry{
   private:
   public:

     int num_spheres, num_generated_spheres, num_rejected_spheres;
     int num_cylinders, num_generated_cylinders, num_rejected_cylinders, resolution;
     int num_defects, num_generated_defects, num_rejected_defects;
     
     double fraction_sp, fraction_cyl, fraction_def, aspect, wave;
     Sphere *spheres;
     Cylinder *cylinders;

     char name[128];
     
     
      Sphere *defects;
     
     Geometry(double __fraction_sp, double __fraction_cyl, double __fraction_def, int __num_spheres, int __num_cylinders, int __num_defects, int __resolution, double __aspect, double __wave);
     int AnotherSphere();
     int AnotherCylinder();
     int PositionFigures();
     void Print(char prefix[128]);
     int PointInsideFigures(Vec3D p);
     void ExportImages();
     void ExportSample(int size_x, int size_y, int size_z, int *sample, double &fraction);
     int AnotherDefect();

};



