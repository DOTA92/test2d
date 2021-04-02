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
  Ey = (double *) malloc((num_mat + 1)*sizeof(double));
  nu = (double *) malloc((num_mat + 1)*sizeof(double));
  H = (double *) malloc((num_mat + 1)*sizeof(double));
  Si0 = (double *) malloc((num_mat + 1)*sizeof(double));

  
  
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
  pl = (double *) malloc((num_vox)*sizeof(double));
  pln = (double *) malloc((num_vox)*sizeof(double));
  trsig = (double *) malloc((num_vox)*sizeof(double));
  trsign = (double *) malloc((num_vox)*sizeof(double));
  
 
  for(i = 0; i<3; i++)
  { 
     epsilon[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * num_vox);
     epsilonn[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * num_vox);
     epsilonn1[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * num_vox);
     sigma[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * num_vox);
     ss[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * num_vox);
     sigman[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * num_vox);
     ssn[i] = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * num_vox);
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
  free(Ey);
  free(nu);
  free(Si0);
  free(H);

  for(i = 0; i<2; i++)
  {
    free(Xi[i]);
  }
  

  for(i = 0; i<6; i++)
  {
    free(Gamma[i]);
  }

  free(sample);
  free(pl);
  free(pln);
  free(trsig);
  free(trsign);
  
  
  // fftw_destroy_plan(p);
  

  for(i = 0; i<3; i++)
  { 
     fftw_free(epsilon[i]);
     fftw_free(epsilonn[i]);
     fftw_free(epsilonn1[i]);
     fftw_free(sigma[i]);
     fftw_free(ss[i]);
     fftw_free(sigman[i]);
     fftw_free(ssn[i]);
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
  
  double contrast;
  int  resol, num_run;
  
    omp_set_dynamic(0);
     omp_set_num_threads(3);

  
  
    struct timespec start, finish;
  double elapsed;   

  char prefix[256], name[256];
  
  
  if(argc<4)
  {
    printf("Enter volume resol,  contrast, number \n");
    return 0;    
  }
  resol= atoi(argv[1]);
  //contrast = atoi(argv[2]);
  contrast = strtof(argv[2],NULL);
  num_run = strtof(argv[3],NULL);

 
  
   

   sprintf(name, "protokol_%d_%lg.txt", resol, contrast);
 
  
    FILE *fp;
  fp = fopen(name, "a");
  
  fprintf(fp, "\n\n\n%d     %lg    \n", resol, contrast);
  printf("\n\n\n  %d  %lg  \n",resol ,  contrast);
  fclose(fp);
 
  
  
  
  sprintf(prefix, "%d_%lg", resol,contrast);
  
  

  //resol = 128;//1766;
  
  fp = fopen(name, "a");
  fprintf(fp, "\n\n%d_%lg ", resol,contrast);
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
 sprintf(myHom.name, "protokol_%d_%lg.txt", resol, contrast);
 
  
  myHom.ReadSample(num_run);
  
  
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
    myHom.Nonlinearnalysis();
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    fp = fopen(name, "a");
    printf("\n Rigidity: %lg seconds \n", (double)(elapsed));
    fprintf(fp,"\n %lg \n", (double)(elapsed));
   
    fclose(fp);
  
   myHom.PrintC();
  
  
  
  
    
  return 0;
}


  
  



