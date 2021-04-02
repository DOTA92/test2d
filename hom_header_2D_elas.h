/*   -------------------------------------------------------   */
/*    Vladimir Salnikov (GM3N LMNO University of Caen) 2015    */
/*   -------------------------------------------------------   */ 


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

#include <complex.h>
#include <fftw3.h>

#include <time.h>  //generating initial data
#include <string.h>  //names of files
#include <dirent.h>

#include <omp.h>

// #include <fenv.h>

class Homogenization{
   private:
   public:
     int size_x, size_y;
     double dx, dy,  fraction;
     int num_mat;
     long int num_vox;
          
     char name[128];
     
     double complex *Gamma[6];  //Green operator
     
     double complex *Xi[2]; //technical things
     
     double *K, *mu, *Ey, *nu, *H, *Si0, *pl, *pln, *trsig, *trsign;  //length num_mat+1
     
     double C_hom[3][3], C0[3][3], S0[3][3];
     double *Ci, *Si; 
     int *sample;
     
     double Sig[3], Ei[3], Ei1[3], time1, ki, Direc[3];
     fftw_complex *sigma[3], *ss[3], *sigman[3], *ssn[3], *epsilon[3], *epsilonn[3], *epsilonn1[3], *sigma_f[3], *tau[3], *ecomp[3], *d[3], *f[3];  //All the FFT source/target
     
     
     fftw_plan p_sigma_forward[3], p_ecomp_backward[3], p_tau_forward[3];     //All the FFT plans

     
     
     
     
     
     Homogenization(int _size_x, int _size_y,  double _dx, double _dy, int _num_mat);
     ~Homogenization();
     
      int ReadSample(int number);
      int ReadMatData();
      int FillMatData(double contrast);
      void FillGamma(double complex *G, int i, int j, int k, int h);
      void ComputeXi();
      void ComputeGreen();
      void Initialisation();
      void ImposingMacroStressDirection(double deps);
      void RadicalReturn();
      void FFT(double acc);
      void ComputeColumn(int col);
      void ComputeRigidity();
      void PrintC();
      void PrintSample();
      double eq_error();
      double comp_error();
      void Nonlinearnalysis();
      
};
