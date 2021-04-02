/*   -------------------------------------------------------   */
/*    Vladimir Salnikov (GM3N LMNO University of Caen) 2015    */
/*   -------------------------------------------------------   */ 



#include "geom.h"
#include "hom_header.h"
using namespace std;







main(int argc, char *argv[])
{
  
  double frac_sph, frac_cyl, frac_def, asp, max_contr, wav;
  int num_sph, num_cyl, num_def, resol, run, num_run, suf;
  
    omp_set_dynamic(0);
     omp_set_num_threads(3);

  
  
    struct timespec start, finish;
  double elapsed;   

  char prefix[256], name[256];
  
  
  if(argc<12)
  {
    printf("Enter volume fraction(sp), number of spheres, volume fraction(cyl), number of cylinders, volume fraction(def), number of defects, aspect ratio, wave amplitude,   number of runs, contrast, suffix \n");
    return 0;    
  }
  frac_sph = strtof(argv[1], NULL);
  num_sph = atoi(argv[2]);
  frac_cyl = strtof(argv[3], NULL);
  num_cyl = atoi(argv[4]);
  frac_def = strtof(argv[5], NULL);
  num_def = atoi(argv[6]);
  asp = strtof(argv[7], NULL);
  wav = strtof(argv[8], NULL);
  
  num_run = atoi(argv[9]);
  max_contr = strtof(argv[10], NULL);
  suf = atoi(argv[11]);

  
  // Geometry MyGeom(frac_sph, frac_cyl, frac_def, num_sph, num_cyl, num_def, 192, asp, wav);
   
   
    
  char fs[5], ns[5], fc[5], nc[5], r[5], fd[5], nd[5];
  if(100*frac_sph<10)  {sprintf(fs, "00%d", (int)(101*frac_sph));}
  else {sprintf(fs, "0%d", (int)(101*frac_sph));}

  if(100*frac_cyl<10)  {sprintf(fc, "00%d", (int)(101*frac_cyl));}
  else {sprintf(fc, "0%d", (int)(101*frac_cyl));}
  
  if(100*frac_def<10)  {sprintf(fd, "00%d", (int)(101*frac_def));}
  else {sprintf(fd, "0%d", (int)(101*frac_def));}

  if(num_sph<10)  {sprintf(ns, "00%d", (int)(num_sph));}
  else {sprintf(ns, "0%d", (int)(num_sph));}

  if(num_cyl<10)  {sprintf(nc, "00%d", (int)(num_cyl));}
  else {sprintf(nc, "0%d", (int)(num_cyl));}
  
  if(num_def<10)  {sprintf(nd, "00%d", (int)(num_def));}
  else {sprintf(nd, "0%d", (int)(num_def));}
  
   
//   sprintf(MyGeom.name, "protokol_%s_%s_%s_%s_%s_%s_%lg__0%d_run%d.txt", fs, ns, fc, nc, fd, nd, asp, (int)(100*wav), suf);
   sprintf(name, "protokol_%s_%s_%s_%s_%s_%s_%lg.txt", fs, ns, fc, nc, fd, nd, max_contr);
   
   
//for (run = 0+suf*2; run < num_run+suf*2; run++)
for (run = 0; run <=0; run++)
{
  
  
    FILE *fp;
  fp = fopen(name, "a");
  
  fprintf(fp, "\n\n\n%.2lg  %d  %.2lg  %d  %.2lg  %d     %lg  %lg             %d.   \n", frac_sph, num_sph, frac_cyl, num_cyl, frac_def, num_def, max_contr, wav, run);
  printf("\n\n\n%.2lg  %d  %.2lg  %d  %.2lg  %d   contrast  %lg wave  %lg  -> run           %d.   \n", frac_sph, num_sph, frac_cyl, num_cyl, frac_def, num_def,  max_contr, wav, run);
  fclose(fp);
 
  
  if(run<10)  {sprintf(r, "00%d", (int)(run));}
  else {sprintf(r, "0%d", (int)(run));}
  
  
  sprintf(prefix, "%s_%s_%s_%s_%s_%s_%lg_0%d_%s_", fs, ns, fc, nc, fd, nd, max_contr, (int)(100*wav), r);
  
  
//  MyGeom.PositionFigures();
  
//  MyGeom.Print(prefix);

//for(resol = 64; resol <= 64; resol+=64)
// {
  
  resol = 32;
  
  fp = fopen(name, "a");
  fprintf(fp, "\n\n%d   ", resol);
  fclose(fp);
  printf("\nResolution %d \n  ", resol);
  
//   MyGeom.ExportImages();


// Homogenization
  
    int err;
  int _size_x, _size_y, _size_z;
  double _dx, _dy, _dz; 
  int _num_mat;
    double contrast;
    
  
  
  _size_x = resol;
  _size_y = _size_x;
  _size_z = _size_x;
  
  _dx = 1./_size_x;
  _dy = 1./_size_y;
  _dz = 1./_size_z;
  
  _num_mat = 2;
  
  Homogenization myHom( _size_x,  _size_y,  _size_z,  _dx,  _dy,  _dz,  _num_mat); 
  sprintf(myHom.name, "protokol_%s_%s_%s_%s_%s_%s_%lg.txt", fs, ns, fc, nc, fd, nd, max_contr);
 
  //MyGeom.ExportSample(_size_x, _size_y, _size_z, myHom.sample, myHom.fraction);
  myHom.ReadSample();
  
  
  for(contrast = max_contr; contrast <= max_contr; contrast*=2.)
  {
    
  
    myHom.FillMatData(contrast);
  
    clock_gettime(CLOCK_MONOTONIC, &start);
  
    myHom.ComputeXi();
   
    myHom.ComputeGreen();
  
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    fp = fopen(name, "a");
        printf("\nAt contrast %lg \n Green: %lg seconds \n", contrast, (double)(elapsed));
       fprintf(fp,"\n%lg \n %lg \n", contrast, (double)(elapsed));
    fclose(fp);
  
    
       
       //myHom.ReadSample();
  //myHom.PrintSample();
    clock_gettime(CLOCK_MONOTONIC, &start);
    myHom.ComputeRigidity();
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    fp = fopen(name, "a");
    printf("\n Rigidity: %lg seconds \n", (double)(elapsed));
    fprintf(fp,"\n %lg \n", (double)(elapsed));
   
    fclose(fp);
  
   myHom.PrintC();
  }
  
// }
  
}  
  
    
  return 0;
}
