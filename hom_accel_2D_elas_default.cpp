/*   -------------------------------------------------------   */
/*    Vladimir Salnikov (GM3N LMNO University of Caen) 2015    */
/*   -------------------------------------------------------   */ 

#include <iostream>
#include "hom_header_2D_elas.h"
using namespace std;

Homogenization::Homogenization(int _size_x, int _size_y, double _dx, double _dy, int _num_mat)
{
  size_x = _size_x;
  size_y = _size_y;
  
  dx = _dx;
  dy = _dy;
  
  num_mat = _num_mat;
  
  num_vox = size_x*size_y;
  
  K = (double *) malloc((num_mat + 1)*sizeof(double));
  mu = (double *) malloc((num_mat + 1)*sizeof(double));
  
  Ci = (double *) malloc((num_mat)*9*sizeof(double));
  Si = (double *) malloc((num_mat)*9*sizeof(double));
  
    
  
  int i;
  for(i = 0; i<2; i++)
  {
    Xi[i] = (double complex *) malloc((num_vox)*sizeof(double complex));
  }
  

  for(i = 0; i<6; i++)
  {
    Gamma[i] = (double complex *) malloc((num_vox)*sizeof(double complex));
  }

  sample = (int *) malloc((num_vox)*sizeof(int));
  
 
  for(i = 0; i<3; i++)
  { 
     epsilon[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * num_vox);
     sigma[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * num_vox);
     sigma_f[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * num_vox);
     tau[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * num_vox);
     ecomp[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * num_vox);
     d[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * num_vox);
     f[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * num_vox);
 
  }
  
  for(i = 0; i<3; i++)
  {
     p_sigma_forward[i] = fftw_plan_dft_2d(size_x, size_y,  sigma[i], sigma_f[i], FFTW_FORWARD,FFTW_MEASURE);// FFTW_EXHAUSTIVE);// FFTW_MEASURE);   //FFTW_ESTIMATE);
     
     p_tau_forward[i] = fftw_plan_dft_2d(size_x, size_y,  tau[i], tau[i], FFTW_FORWARD,FFTW_MEASURE);//, FFTW_EXHAUSTIVE);// FFTW_MEASURE);  
     
     p_ecomp_backward[i] =  fftw_plan_dft_2d(size_x, size_y,  ecomp[i], ecomp[i], FFTW_BACKWARD,FFTW_MEASURE);//, FFTW_EXHAUSTIVE);// FFTW_MEASURE);   //FFTW_ESTIMATE);
    
  }
  
  
}

Homogenization::~Homogenization()
{
    
  int i;
  free(K);
  free(mu);
  free(Ci);
  free(Si);

  for(i = 0; i<2; i++)
  {
    free(Xi[i]);
  }
  

  for(i = 0; i<6; i++)
  {
    free(Gamma[i]);
  }

  free(sample);
  
  
  // fftw_destroy_plan(p);
  

  for(i = 0; i<3; i++)
  { 
     fftw_free(epsilon[i]);
     fftw_free(sigma[i]);
     fftw_free(sigma_f[i]);
     fftw_free(tau[i]);
     fftw_free(ecomp[i]);
     fftw_free(d[i]);
     fftw_free(f[i]);
  }
  
  for(i = 0; i<3; i++)
  { 
     fftw_destroy_plan(p_sigma_forward[i]);
     fftw_destroy_plan(p_tau_forward[i]);
     fftw_destroy_plan(p_ecomp_backward[i]);
  }
 
  
}


main(int argc, char *argv[])
{
  
  double frac_sph, frac_cyl, frac_def, asp, contrast, wav;
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
  contrast = strtof(argv[10], NULL);
  suf = atoi(argv[11]);

  
  
   
    
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
  
   

   sprintf(name, "protokol_%s_%s_%s_%s_%s_%s_%lg.txt", fs, ns, fc, nc, fd, nd, contrast);
   
   
//for (run = 0+suf*2; run < num_run+suf*2; run++)
for (run = 0; run <=0; run++)
{
  
  
    FILE *fp;
  fp = fopen(name, "a");
  
  fprintf(fp, "\n\n\n%.2lg  %d  %.2lg  %d  %.2lg  %d     %lg  %lg             %d.   \n", frac_sph, num_sph, frac_cyl, num_cyl, frac_def, num_def, contrast, wav, run);
  printf("\n\n\n%.2lg  %d  %.2lg  %d  %.2lg  %d   contrast  %lg wave  %lg  -> run           %d.   \n", frac_sph, num_sph, frac_cyl, num_cyl, frac_def, num_def,  contrast, wav, run);
  fclose(fp);
 
  
  if(run<10)  {sprintf(r, "00%d", (int)(run));}
  else {sprintf(r, "0%d", (int)(run));}
  
  
  sprintf(prefix, "%s_%s_%s_%s_%s_%s_%lg_0%d_%s_", fs, ns, fc, nc, fd, nd, contrast, (int)(100*wav), r);
  
  

  resol = 128;//1766;
  
  fp = fopen(name, "a");
  fprintf(fp, "\n\n%d   ", resol);
  fclose(fp);
  printf("\nResolution %d \n  ", resol);



// Homogenization
  
    int err;
  int _size_x, _size_y;
  double _dx, _dy ; 
  int _num_mat;
    
    
  
  
  _size_x = resol;
  _size_y = _size_x;
  
  
  _dx = 1./_size_x;
  _dy = 1./_size_y;
  
  
  _num_mat = 2;
  
  Homogenization myHom( _size_x,  _size_y,   _dx,  _dy,  _num_mat); 
  //sprintf(myHom.name, "protokol_%s_%s_%s_%s_%s_%s_%lg.txt", fs, ns, fc, nc, fd, nd, contrast);
 sprintf(myHom.name, "protokol_%lg.txt",  contrast);
 
  
  myHom.ReadSample();
  
  
  cout<<"contrast="<<contrast<<endl;
  
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
  
    
  return 0;
}


  
  



