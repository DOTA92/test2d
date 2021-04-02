/*   -------------------------------------------------------   */
/*    Vladimir Salnikov (GM3N LMNO University of Caen) 2015    */
/*   -------------------------------------------------------   */ 


#include "hom_header_2D_elas.h"
#include <cmath>
#include <iostream>
using namespace std;


int Homogenization::FillMatData(double contrast)
{
  int i, j, k;
    
  // Matrix  
  Ey[1] = 68900;
  nu[1] = 0.35;
  H[1] = 0.;
  Si0[1] = 68.9;
  // Inclusion
  Ey[2] = 400000;
  nu[2] = 0.23;
  H[2] = 0.;
  Si0[2] = 10000;

     
  
  for(i = 1; i<=num_mat; i++)
  {
    K[i] = Ey[i]/(3.*(1.-2.*nu[i]));
    mu[i] = Ey[i]/(2.*(1.+nu[i]));
  }
 
 
  
  
 for(k = 0; k<num_mat; k++)
 {
   
   for(i = 0; i<3; i++)
   {
     for(j = 0; j<3; j++)
     {
        Ci[k*9 + i*3 + j] = 0;
     }
   }
  
    Ci[k*9 + 0*3 + 0] = K[k+1] + 4.*mu[k+1]/3.;
    Ci[k*9 + 0*3 + 1] = K[k+1] - 2.*mu[k+1]/3.;
    Ci[k*9 + 0*3 + 2] = 0.;  
    
    Ci[k*9 + 1*3 + 0] = K[k+1] - 2.*mu[k+1]/3.;
    Ci[k*9 + 1*3 + 1] = K[k+1] + 4.*mu[k+1]/3.;
    Ci[k*9 + 1*3 + 2] = 0.;
    
    Ci[k*9 + 2*3 + 0] = 0.;
    Ci[k*9 + 2*3 + 1] = 0.;
    Ci[k*9 + 2*3 + 2] = 2.*mu[k+1];
    
   
 }
  
  
 
 //  THIS WORKS FOR TWO MATERIALS !!!
 //K[0] = -25.*sqrt(K[1]*K[2]);
 //mu[0] = -100*sqrt(mu[1]*mu[2]);
 K[0] = K[1];
 mu[0] = mu[1];
 Ey[0] = Ey[1];
 nu[0] = nu[1];
   cout<<"K0="<<K[0]<<endl;
   cout<<"Mu0="<<mu[0]<<endl;
   
 for(k = 0; k<num_mat; k++)
 {  
    
    
  for(i = 0; i<3; i++)
  {
    for(j = 0; j<3; j++)
    {
      Si[k*9 + i*3 + j] = 0.;
    }
  }
  
   Si[k*9 + 0*3 + 0] = (3.*(K[k+1] - K[0])+(mu[k+1] - mu[0]))/(9.*(K[k+1] - K[0])*(mu[k+1] - mu[0]));  
   Si[k*9 + 0*3 + 1] = 1./(9.*(K[k+1] - K[0]))-1./(6.*(mu[k+1] - mu[0]));
   Si[k*9 + 0*3 + 2] = 0.;
   
   Si[k*9 + 1*3 + 0] = 1./(9.*(K[k+1] - K[0]))-1./(6.*(mu[k+1] - mu[0]));
   Si[k*9 + 1*3 + 1] = (3.*(K[k+1] - K[0])+(mu[k+1] - mu[0]))/(9.*(K[k+1] - K[0])*(mu[k+1] - mu[0]));
   Si[k*9 + 1*3 + 2] = 0.;
   
   Si[k*9 + 2*3 + 0] = 0.;
   Si[k*9 + 2*3 + 1] = 0.;
   Si[k*9 + 2*3 + 2] = 1./(2.*(mu[k+1] - mu[0]));

   
    
    
    //Modify here to take orientation into account 
 /* 
  for(i = 0; i<3; i++)
   {
     for(j = 0; j<3; j++)
     {
        cout<<"S["<<k*9 + i*3 + j<<"]="<<Si[k*9 + i*3 + j] <<'\t';
     }
     cout<<endl;
   }
   */
  } 
   
  
   return 0;
}




int Homogenization::ReadMatData()
{
  FILE *fp;
  int i, j, k, tmp, stat = 0;
    
  fp = fopen("materials.dat", "r");
  if(!fp)
  {
    printf("\n Warning: Missing materials data\n");
    return -1;
  }
  
  for(i = 0; i<=num_mat; i++)
  {
    stat += fscanf(fp,"%d", &tmp);
    if(tmp!=i)
    {
       printf("\n Warning: Strange materials data file \n");
       fclose(fp);
       return -2;
    }
    stat += fscanf(fp,"%lg", &K[i]);
    stat += fscanf(fp,"%lg", &mu[i]);
  }
  if(stat != 3*(num_mat+1))
  {
       printf("\n Warning: probably incomplete materials data file \n");
       fclose(fp);
       return -3;
  }
  
  fclose(fp);
  
  
  
 for(k = 0; k<num_mat; k++)
 {
   
   for(i = 0; i<3; i++)
   {
     for(j = 0; j<3; j++)
     {
        Ci[k*9 + i*3 + j] = 0;
     }
   }
  
    Ci[k*9 + 0*3 + 0] = K[k+1] + 4.*mu[k+1]/3.;  
    Ci[k*9 + 0*3 + 1] = K[k+1] - 2.*mu[k+1]/3.;
    Ci[k*9 + 0*3 + 2] = 0.;
    
    Ci[k*9 + 1*3 + 0] = K[k+1] - 2.*mu[k+1]/3.;
    Ci[k*9 + 1*3 + 1] = K[k+1] + 4.*mu[k+1]/3.;
    Ci[k*9 + 1*3 + 2] = 0.;
   
    Ci[k*9 + 2*3 + 0] = 0.;
    Ci[k*9 + 2*3 + 1] = 0.;
    Ci[k*9 + 2*3 + 2] = 2.*mu[k+1];

   }
  
  
 
 //  THIS WORKS FOR TWO MATERIALS !!!
 K[0] = -sqrt(K[1]*K[2]);
 mu[0] = -sqrt(mu[1]*mu[2]);
 
 
 
   
 for(k = 0; k<num_mat; k++)
 {  
    
    
  for(i = 0; i<3; i++)
  {
    for(j = 0; j<3; j++)
    {
      Si[k*9 + i*3 + j] = 0;
    }
  }
  
   Si[k*9 + 0*3 + 0] = (3.*(K[k+1] - K[0])+(mu[k+1] - mu[0]))/(9.*(K[k+1] - K[0])*(mu[k+1] - mu[0]));  
   Si[k*9 + 0*3 + 1] = 1./(9.*(K[k+1] - K[0]))-1./(6.*(mu[k+1] - mu[0]));
   Si[k*9 + 0*3 + 2] = 0.;
   

   Si[k*9 + 1*3 + 0] = 1./(9.*(K[k+1] - K[0]))-1./(6.*(mu[k+1] - mu[0]));
   Si[k*9 + 1*3 + 1] = (3.*(K[k+1] - K[0])+(mu[k+1] - mu[0]))/(9.*(K[k+1] - K[0])*(mu[k+1] - mu[0]));
   Si[k*9 + 1*3 + 2] = 0.;
   
   Si[k*9 + 2*3 + 0] = 0.;
   Si[k*9 + 2*3 + 1] = 0.;
   Si[k*9 + 2*3 + 2] = 1./(2.*(mu[k+1] - mu[0]));

   
    
    
    //Modify here to take orientation into account 
 }  
  
  
   return 0;
}

void Homogenization::ComputeXi()
{
  int i, j;
  
    for(i=0; i<size_x; i++)
    {
      for(j=0; j<size_y; j++)
      {
	
	  //if(i<=size_x/2)
	  if((i<=size_x/2)&&(j<=size_y/2))
	  {
	    //Xi[0][i*size_y+ j ] = i;
           //Xi[0][i*size_y+ j ] = I*sin(2.0*M_PI*i/size_x);
	   //Xi[0][i*size_y+ j ] = (cexp(2.0*M_PI*i/size_x)-1.0);
	   Xi[0][i*size_y+ j ] =I*tan(M_PI*i/size_x)*(cexp(2.0*M_PI*i/size_x)+1.0)*(cexp(2.0*M_PI*j/size_y)+1.0);
	  }
	  else
	  {
	    //Xi[0][i*size_y+j] = i - size_x;
	    //Xi[0][i*size_y+j] = I*sin(2.0*M_PI*(i - size_x)/size_x);
	    //Xi[0][i*size_y+j] = (cexp(2.0*M_PI*(i - size_x)/size_x)-1.0);
	     Xi[0][i*size_y+j] = I*tan(M_PI*(i - size_x)/size_x)*(cexp(2.0*M_PI*(i -size_x)/size_x)+1.0)*(cexp(2.0*M_PI*(j - size_y)/size_y)+1.0);
	  }
	
      }
    }

    for(i=0; i<size_x; i++)
    {
      for(j=0; j<size_y; j++)
      {
	
	  //if(j<=size_y/2)
	  if((j<=size_y/2)&&(i<=size_x/2))
	  {
	    //Xi[1][i*size_y+ j] = j;
	    Xi[1][i*size_y+ j] = I*sin(2.0*M_PI*j/size_y);
	   //Xi[1][i*size_y+ j] = (cexp(2.0*M_PI*j/size_y)-1.);
	    Xi[1][i*size_y+ j] = I*tan(M_PI*j/size_y)*(cexp(2.0*M_PI*j/size_y)+1.)*(cexp(2.0*M_PI*i/size_x)+1.);
		}
	  else
	  {
	    //Xi[1][i*size_y + j] = j - size_y;
	    //Xi[1][i*size_y + j] = I*sin(2.0*M_PI*(j - size_y)/size_y);
            //Xi[1][i*size_y + j] = (cexp(2.0*M_PI*(j - size_y)/size_y)-1.);
	    Xi[1][i*size_y + j] = I*tan(M_PI*(j - size_y)/size_y)*(cexp(2.0*M_PI*(j -size_y)/size_y)+1.)*(cexp(2.0*M_PI*(i - size_x)/size_x)+1.);
	  }
	
      }
    }
/*
   for(i=0; i<size_x; i++)
    {
      for(j=0; j<size_y; j++)
      { 
 cout<< "Xi[0]["<<i*size_y + j<<"]="<<    Xi[0][i*size_y + j]<<'\t';
 cout<< "Xi[1]["<<i*size_y + j<<"]="<< Xi[1][i*size_y + j]<<'\t';
  }
  cout<<endl;
  }
  */
}


void Homogenization::FillGamma(double complex *G, int i, int j, int k, int h)
{
  double lm0, a, b,b1,b2;
  lm0 = K[0] - ((2./3.)*mu[0]);
  a = 1./(4.*mu[0]);
  b = (lm0 + mu[0])/(mu[0]*(lm0 + 2.*mu[0]));
  b1 = lm0 /(mu[0]*(lm0 + 2.*mu[0]));
  b2 = 1./(lm0 + 2.*mu[0]);
  
  int _i, _j ;
  long int n;
  for(_i = 0; _i<size_x; _i++)
  {
    for(_j = 0; _j<size_y; _j++)
    {
      
	  n = _i*size_y + _j ;
	  if((( Xi[0][n]*Xi[0][n]) + ( Xi[1][n]*Xi[1][n])  )  == 0) 
	  {
	    G[n] =0.;// a*( (k==i) + (h==i) + (k==j) + (h==j) ) / (3.)  - (b / 9.); 
	  }
	  else
	  {	 double r=  creal(Xi[0][n]*conj(Xi[0][n]) + Xi[1][n]*conj(Xi[1][n]));
	    G[n] = a*((k==i)*Xi[h][n]*conj(Xi[j][n]) + (h==i)*Xi[k][n]*conj(Xi[j][n]) + (k==j)*Xi[h][n]*conj(Xi[i][n]) + (h==j)*Xi[k][n]*conj(Xi[i][n])) /r  - (
	    b1*creal(Xi[i][n]*conj(Xi[j][n]))*creal(Xi[k][n]*conj(Xi[h][n]))+ b2*Xi[i][n]*Xi[j][n]*conj(Xi[k][n]*Xi[h][n])
	    )/r/r; 
	    
	  }
      
    }
    
    
  }
  
}

void Homogenization::ComputeGreen()
{
// K[0] = -sqrt(K[1]*K[2]);
  // mu[0] = -sqrt(mu[1]*mu[2]);
  
  int i, j, _i, _j, _k,  nb;
  long int n;
  
  for(i = 0; i<3; i++)
  {
    for(j = 0; j<3; j++)
    {
      C0[i][j] = 0;
    }
  }
  
  C0[0][0] = K[0] + 4.*mu[0]/3.;  
  C0[0][1] = K[0] - 2.*mu[0]/3.;
  C0[0][2] = 0.;
  
  C0[1][0] = K[0] - 2.*mu[0]/3.;
  C0[1][1] = K[0] + 4.*mu[0]/3.;
  C0[1][2] = 0.;
  
  C0[2][0] = 0.;
  C0[2][1] = 0.;
  C0[2][2] = 2.*mu[0];
  





  FillGamma(Gamma[0],0,0,0,0);     
  FillGamma(Gamma[1],0,0,1,1);   
  FillGamma(Gamma[2],0,0,0,1);   

  FillGamma(Gamma[3],1,1,1,1);   
  FillGamma(Gamma[4],1,1,0,1);
     
  FillGamma(Gamma[5],0,1,0,1);   
  
/*  All -1
1  2  3  
2  4  5  
3  5  6 
  */

  
  

if(!(size_x%2)||!(size_y%2))  
{
  for(i = 0; i<3; i++)
  {
    for(j = 0; j<3; j++)
    {
      S0[i][j] = 0;
    }
  }
  
  /*
  S0[0][0] = (3.*K[0]+mu[0])/(9.*K[0]*mu[0]);
  S0[0][1] = 1./(9.*K[0])-1./(6.*mu[0]);
  S0[0][2] = 0.;
  
  S0[1][0] = 1./(9.*K[0])-1./(6.*mu[0]);
  S0[1][1] = (3.*K[0]+mu[0])/(9.*K[0]*mu[0]);
  S0[1][2] = 0.;
  
  
  S0[2][0] = 0.;
  S0[2][1] = 0.;
  S0[2][2] = 1./(2.*mu[0]);
    */

  S0[0][0] = (1.+nu[1])/Ey[1] * (1.-nu[1]);
  S0[0][1] = (1.+nu[1])/Ey[1] * (-nu[1]);
  S0[0][2] = 0.;
  S0[1][0] = (1.+nu[1])/Ey[1] * (-nu[1]);
  S0[1][1] = (1.+nu[1])/Ey[1] * (1.-nu[1]);
  S0[1][2] = 0.;
  S0[2][0] = 0.;
  S0[2][1] = 0.;
  S0[2][2] = (1.+nu[1])/Ey[1];
  
  
  
}  

if (!size_x%2)
{
  nb = 0;
    for(i=0; i<3; i++)
    {
       for(j=i; j<3; j++)
       {
	 if (j<3)
	 {
	    for(_j = 0; _j < size_y; _j++)
	    {
	      
		_i = size_x/2; 
		Gamma[nb][_i*size_y + _j] = 0.*S0[i][j];
	      
	    }
	 }
         else
	 {
	    for(_j = 0; _j < size_y; _j++)
	    {
	      
		_i = size_x/2; 
		Gamma[nb][_i*size_y + _j] = 0.*S0[i][j]/2.;
	      
	    }
	 }
         nb++;
       }
    } 
}
    

if (!size_y%2)
{
  nb = 0;
    for(i=0; i<3; i++)
    {
       for(j=i; j<3; j++)
       {
	 if (j<3)
	 {
	    for(_i = 0; _i < size_x; _i++)
	    {
	      
		_j = size_y/2; 
		Gamma[nb][_i*size_y + _j] = 0.*S0[i][j];
	      
	    }
	 }
         else
	 {
	    for(_i = 0; _i < size_x; _i++)
	    {
	      
		_j = size_y/2; 
		Gamma[nb][_i*size_y + _j] = 0.*S0[i][j]/2.;
	      
	    }
	 }
         nb++;
       }
    } 
}




   
}


int Homogenization::ReadSample(int number)
{
  int i, j;
  int res_x, res_y, stat, in;
  long int n;
  char filename[128], tmp[10];
  FILE *fp;
  n = 0;
  
  fraction = 0;
  
  for(int k = number; k<number+1; k++)
  {
    if(k<10)    sprintf(filename, "slice000%d.pgm", k);
    if((k>=10)&&(k<100))    sprintf(filename, "slice00%d.pgm", k);
    if((k>=100)&&(k<1000))    sprintf(filename, "slice0%d.pgm", k);
    if((k>=1000))    sprintf(filename, "slice%d.pgm", k);
   
   
    fp = fopen(filename, "r");
    if(!fp)
    {
      printf("\nWarning: slice %d missing \n", k);
      return -1;
      
    }
    
    stat = 0;
    stat += fscanf(fp, "%s", tmp);
    stat += fscanf(fp, "%d", &res_y);
    stat += fscanf(fp, "%d", &res_x);
        stat += fscanf(fp, "%s", tmp);

    if((stat!=4)||(res_y!=size_y)||(res_x!=size_x))
    {
      printf("\nWarning: Some problem with header at slice %d \n", k);
      return -2;
    }


    for(i = 0; i<size_x; i++)
    {
      for(j = 0; j<size_y; j++)
      {
	 stat=fscanf(fp, "%d", &in);
	 if(!stat)	 
	 {
	    printf("\nWarning: Some problem with data at slice %d \n", k);
	    return -3;
	 }
	 sample[n] = 2-in;
	 
	 if((2-in)==1)
	 {
	   fraction +=1;  
	 }
	 n++;
	
      }
    }
    fclose(fp);

  }
  
  fraction /=num_vox;
  printf("Fraction %lg at resolution %d x %d  \n", fraction, size_x, size_y);
  
}

void Homogenization::ImposingMacroStressDirection(double deps)
{
  int i;
  time1 += deps;
  //Compute ki
  //printf("E= %lg %lg %lg \n", Ei[0], Ei[1], Ei[2]);
  //printf("Sigma= %lg %lg %lg \n", Sig[0], Sig[1], Sig[2]);
  ki = time1 + (S0[0][0]*Sig[0]+S0[0][1]*Sig[1]+S0[0][2]*Sig[2]-Ei[0])*Direc[0] + (S0[1][0]*Sig[0]+S0[1][1]*Sig[1]+S0[1][2]*Sig[2]-Ei[1])*Direc[1] + (S0[2][0]*Sig[0]+S0[2][1]*Sig[1]+S0[2][2]*Sig[2]-Ei[2])*Direc[2];
  ki /= ((S0[0][0]*Direc[0]+S0[0][1]*Direc[1]+S0[0][2]*Direc[2])*Direc[0] + (S0[1][0]*Direc[0]+S0[1][1]*Direc[1]+S0[1][2]*Direc[2])*Direc[1] + (S0[2][0]*Direc[0]+S0[2][1]*Direc[1]+S0[2][2]*Direc[2])*Direc[2]);
  //printf("time1 = %lg ki = %lg S0 = %lg\n", time1, ki, S0[0][0]);

  // Compute Macro Strain
  for(i=0; i<3; i++)
  {
    Ei[i] += ki * (S0[i][0]*Direc[0]+S0[i][1]*Direc[1]+S0[i][2]*Direc[2]) - (S0[i][0]*Sig[0]+S0[i][1]*Sig[1]+S0[i][2]*Sig[2]);
  }
}

void Homogenization::Initialisation()
{
    int i;
    long int n;
    #pragma omp parallel for private(n)
    for(n =0; n<num_vox; n++)
    {
      for(i=0; i<3; i++)
      {
        epsilon[i][n] = epsilonn[i][n] + (epsilonn[i][n] - epsilonn1[i][n]);
      }
    }
}

void Homogenization::RadicalReturn()
{
  double complex vdeps[3]; 
  double trdeps, sigmaeq, trsigma;
  long int n;
  int i;
  #pragma omp parallel for private(n)
  for(n =0; n<num_vox; n++)
  {
    for(i=0; i<3; i++)
      {
        vdeps[i] = epsilon[i][n] - epsilonn[i][n];
      }
    trdeps = creal(vdeps[0] + vdeps[1]);
    ss[0][n] += 2.*mu[sample[n]]*(vdeps[0]-trdeps/3.);
    ss[1][n] += 2.*mu[sample[n]]*(vdeps[1]-trdeps/3.);
    ss[2][n] += 2.*mu[sample[n]]*(vdeps[2]);
      
    sigmaeq = sqrt(3./2.*cabs(ss[0][n]*conj(ss[0][n])+ss[1][n]*conj(ss[1][n])+2.*ss[2][n]*conj(ss[2][n])));
    printf("sigmaeq = %lg \n", sigmaeq);
    if (sigmaeq > (Si0[sample[n]]+H[sample[n]]*pn[sample[n]]))
    { 
      printf("get in %lg %ld\n", Si0[sample[n]], n);
      pn[sample[n]] *= (3.*mu[sample[n]]);
      pn[sample[n]] += (sigmaeq-Si0[sample[n]]);
      pn[sample[n]] /= (H[sample[n]]+3.*mu[sample[n]]);
      for(i=0; i<3; i++)
      {
        ss[i][n] *=  (Si0[sample[n]]+H[sample[n]]*pn[sample[n]])/sigmaeq;
      }
    }
    printf("ss0 = %lg ss1 = %lg ss2 = %lg\n", creal(ss[0][n]), creal(ss[1][n]), creal(ss[2][n]));
    trsigma = creal(sigma[0][n] + sigma[1][n]) + 3.*K[sample[n]]*trdeps;
    sigma[0][n] = 1./3.*trsigma + ss[0][n];
    sigma[1][n] = 1./3.*trsigma + ss[1][n];
    sigma[2][n] = ss[2][n];
    printf("sig0 = %lg sig1 = %lg sig2 = %lg\n", creal(sigma[0][n]), creal(sigma[1][n]), creal(sigma[2][n]));
  }

}

void Homogenization::FFT(double acc)
{
  double comp_err, eq_err;
  comp_err = 1; 
  eq_err = 1;
  int i, j, num_iter;
  long int n;

  // Initialize epsilon
  // Initialisation();

  // Compute sigma, pn
  RadicalReturn();

  //Loop
  num_iter = 0;

  while ((comp_err > acc)&&(eq_err > acc))
  {
    num_iter++;
    printf(" %d comp_err = %lg, eq_err = %lg \n", num_iter, comp_err, eq_err);
    // Step a
    #pragma omp barrier     
    if(comp_err < acc)
    {
      #pragma omp parallel for 
        for(i = 0; i<3; i++)
  {
    fftw_execute(p_sigma_forward[i]);
  }
    #pragma omp barrier 
        eq_err = eq_error();
    }    
    else
    {
        eq_err = 1.;  
    }

    // Polarization
    #pragma omp parallel for private(n, j)
    for(i = 0; i<3; i++)
    {
  for(n = 0; n<num_vox; n++)
  {
     tau[i][n] = sigma[i][n];
     for(j = 0; j<3; j++)
     {
             tau[i][n] += C0[i][j]*epsilon[j][n];
     }
  }
    }
    #pragma omp barrier
     
     #pragma omp parallel for
     for(i = 0; i<3; i++)
     {
    fftw_execute(p_tau_forward[i]);
     }    
    #pragma omp barrier

     //Green operator appied to polarization
    
   #pragma omp parallel sections private(n)
   { 
    #pragma omp section
    for(n = 0; n<num_vox; n++)  
    { 
      ecomp[0][n] = (Gamma[0][n]*tau[0][n]) + (Gamma[1][n]*tau[1][n])  + 2.*(Gamma[2][n]*tau[2][n]) ;  
    }
    #pragma omp section
    for(n = 0; n<num_vox; n++)  
    { 
      ecomp[1][n] = (conj(Gamma[1][n])*tau[0][n]) + (Gamma[3][n]*tau[1][n])  + 2.*(Gamma[4][n]*tau[2][n]) ;    
    }
    #pragma omp section
    for(n = 0; n<num_vox; n++)  
    {
      ecomp[2][n] = (conj(Gamma[2][n])*tau[0][n]) + (conj(Gamma[4][n])*tau[1][n])  + 2.*(Gamma[5][n]*tau[2][n]);  
    }
   } 
    #pragma omp barrier

   // Force the mean value      
  for(i = 0; i<3; i++)
  {
    ecomp[i][0] = Ei[i]*num_vox;  //CHECK normalization convention
  }
  #pragma omp parallel for 
   for(i = 0; i<3; i++)
   {
  fftw_execute(p_ecomp_backward[i]);   //The result is almost real
   }    
        #pragma omp barrier 
     
      //Normalization   CHECK
   #pragma omp parallel for private(n)
   for(i = 0; i<3; i++)
    {
     for(n = 0; n<num_vox; n++)
      {
       ecomp[i][n] /= (double)num_vox;
      }
    }   
       #pragma omp barrier

    //ecomp - epsilon
   #pragma omp parallel for private(n)
    for(i = 0; i<3; i++)
    {
  for(n = 0; n<num_vox; n++)
  {
       ecomp[i][n] -= epsilon[i][n];
  }
    }
        #pragma omp barrier
  

   comp_err = comp_error();
    
    // d= C0:(ecomp-epsilon)
  #pragma omp parallel for private(n, j)
    for(i = 0; i<3; i++)
    {
  for(n = 0; n<num_vox; n++)
  {
     d[i][n] = 0.;
     for(j = 0; j<3; j++)
     {
             d[i][n] += C0[i][j]*ecomp[j][n];
       
     }
  }
    }
       #pragma omp barrier
    
   
    // f = ((dc)^-1):C0:(ecomp-epsilon)
    #pragma omp parallel for private(n, j)
    for(i = 0; i<3; i++)
    {
  for(n = 0; n<num_vox; n++)
  {
     f[i][n] = 0.;
     for(j = 0; j<3; j++)
     {
             f[i][n] += Si[sample[n]*9 + i*3 + j]*d[j][n];
     }
  }
    }
     #pragma omp barrier
 
 
 
    
    //  eps n+1 = eps n - 2((dc)^-1):C0:(ecomp-epsilon)
    #pragma omp parallel for private(n)
    for(i = 0; i<3; i++)
    {
  for(n = 0; n<num_vox; n++)
  {
     
             epsilon[i][n] -= 2.*f[i][n];
  }
    }
        #pragma omp barrier

    //Step e
    RadicalReturn();



  }

}


 
double Homogenization::eq_error()
{
  double err;
  long int n;
  
  err = 0;
  #pragma omp parallel for private(n)
  for(n = 0; n<num_vox; n++)
  {
    err +=  cabs(Xi[0][n]*sigma_f[0][n] + Xi[1][n]*sigma_f[2][n])*cabs(Xi[0][n]*sigma_f[0][n] + Xi[1][n]*sigma_f[2][n])+
    cabs(Xi[0][n]*sigma_f[2][n]+Xi[1][n]*sigma_f[1][n])*cabs(Xi[0][n]*sigma_f[2][n] +Xi[1][n]*sigma_f[1][n]);
  }
  
  #pragma omp barrier

  err = sqrt(err/num_vox);
   
  err /= cabs( sigma_f[0][0]*conj(sigma_f[0][0]) + sigma_f[1][0]*conj(sigma_f[1][0]) +2.*sigma_f[2][0]*conj(sigma_f[2][0])) ;

  
  
  return err;
  
  
}

double Homogenization::comp_error()
{
  double err;
  long int n;
  
  err = 0;
  #pragma omp parallel for private(n)
  for(n = 0; n<num_vox; n++)
  {
    double complex e11=ecomp[0][n];
    double complex e22=ecomp[1][n];
    double complex e12=ecomp[2][n];
    err += creal(e11*conj(e11)+e22*conj(e22)+2.*e12*conj(e12));
    
    //err += creal(ecomp[0][n]*conj(ecomp[0][n]))+ creal(ecomp[1][n]*conj(ecomp[1][n]))+	   2.*creal(ecomp[2][n]*conj(ecomp[2][n]));
    
    
  }
  /*
  for(n = 0; n<num_vox; n++)
  {
    err += creal(ecomp[1][n]*conj(ecomp[1][n]));
  }
  for(n = 0; n<num_vox; n++)
  {
    err += 2.*creal(ecomp[2][n]*conj(ecomp[2][n]));
  }
*/
  

  err = sqrt(err/num_vox);
  
  err /= sqrt(Ei[0]*Ei[0] + Ei[1]*Ei[1] + 2.*Ei[2]*Ei[2]);
  
  return err;
}

void Homogenization::PrintC()
{
  int i, j;
  FILE *fp;
  fp = fopen(name, "a");
  
//   fprintf(fp," Rigidity matrix: \n");
  fprintf(fp," \n");
  for(i =0; i<3; i++)
  {
    //fprintf(fp,"|");
    for(j =0; j<3; j++)
    {
      fprintf(fp," %lg ", C_hom[i][j]);
    }
    fprintf(fp,"\n");
  }
  
  printf(" \n");
  for(i =0; i<3; i++)
  {
    printf("|");
    for(j =0; j<3; j++)
    {
      printf(" %lg ", C_hom[i][j]);
    }
    printf("|\n");
  }

  
  
   
   
  double K, MU, E, nu;
   K = C_hom[0][0] + 2*(C_hom[0][1] + C_hom[1][0]) + C_hom[1][1] ; // = 6K
   MU = C_hom[0][0] + C_hom[1][1] +C_hom[2][2]-(C_hom[0][1] +C_hom[1][0]); // = 6Mu
		   
   MU /=6. ;
   K /=6.;
  
   
   E = (9*K*MU)/(3*K + MU);
   nu = (3*K - 2*MU)/(2*(3*K + MU));
   
   
   
   
   fprintf(fp, "\n %lg %lg   %lg %lg \n", K, MU, E, nu);
 printf("\n K = %lg, MU(G) = %lg,  E = %lg, nu = %lg \n", K, MU, E, nu);
   
//     fprintf(fp,"\n");
  fclose(fp);
}

void Homogenization::PrintSample()
{
  long int n;
  
  for(n = 0; n<num_vox; n++)
  {
    if(n%size_y == 0) printf("\n");
    if(n%(size_x*size_y) == 0) printf("\n");
    printf("%d", sample[n]);
  }
  
}

void Homogenization::Nonlinearnalysis()
{
  
  int i;
  long int n;

  // Initialisation
  time1 = 0.;
  Direc[0] =1.;
  Direc[1] =0.;
  Direc[2] =0.;

  #pragma omp parallel for private(n)
  for(i=0; i<3; i++)
  {
    Ei[i] = 0.;
    Sig[i] = 0.;
    for(n=0; n<num_vox; n++)
    {
      epsilonn1[i][n] = 0.;
      epsilonn[i][n] = 0.;
      ss[i][n] = 0.;
      pn[n] = 0.;
    }
  }
  printf("E= %lg %lg %lg \n", Ei[0], Ei[1], Ei[2]);
  printf("Sigma= %lg %lg %lg \n", Sig[0], Sig[1], Sig[2]);
  
  double deps = 1e-5; 
  ImposingMacroStressDirection(deps);

  printf("E= %lg %lg %lg \n", Ei[0], Ei[1], Ei[2]);

  #pragma omp parallel for private(n)
  for(i=0; i<3; i++)
  {
    for(n=0; n<num_vox; n++)
    {
      epsilon[i][n] = Ei[i];
      //printf("epsilon = %lg %lg %d\n", creal(epsilon[i][n]), Ei[i], i);
    }
  }

  
  // Compute Sig
  FFT(1e-4);

  double complex eps, sig;

  for(i = 0; i<3; i++)
  {
  sig = 0.;
  eps = 0.;
  for(n = 0; n<num_vox; n++)
  {
    sig += sigma[i][n];
    eps += epsilon[i][n];
  }
  Sig[i] = creal(sig/num_vox);
  printf("eps = %lg", creal(eps));
  
  }
  printf("Sigma= %lg %lg %lg \n", Sig[0], Sig[1], Sig[2]);

}

