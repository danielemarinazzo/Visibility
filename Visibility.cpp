// [A k k_in k_out]=Visibility(H,opt);
// input:    H        serie temporale
//           opt     1 visibilità orizzontale 2 visibilità
// output:   A       Matrice di adiacenza
//           k       Vettore nodi
//           k_in    Vettore nodi entranti
//           k_out   Vettore nodi uscenti
#include <matrix.h>
#include <mex.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <sstream>
#include <random>
#include <algorithm>
#include <iterator>
#define ISREAL2DFULLDOUBLE(P) (!mxIsComplex(P) && mxGetNumberOfDimensions(P) == 2 && !mxIsSparse(P) && mxIsDouble(P))
#define ISINTEGER2DFULLINT32(P) (mxIsInt32(P) && mxGetNumberOfDimensions(P) == 2)
#define ISREALSQUAREMATRIXDOUBLE(P) (ISREAL2DFULLDOUBLE(P) && mxGetN(P) == mxGetM(P))
#define ISINTEGERSQUAREMATRIXINT32(P) (ISINTEGER2DFULLINT32(P) && mxGetN(P) == mxGetM(P))
#define ISREALROWVECTORDOUBLE(P) (ISREAL2DFULLDOUBLE(P) && mxGetM(P) == 1)
#define ISREALCOLUMNVECTORDOUBLE(P) (ISREAL2DFULLDOUBLE(P) && mxGetN(P) == 1)
#define ISREALSCALAR(P) (ISREAL2DFULLDOUBLE(P) && mxGetNumberOfElements(P) == 1)
#define ISLOGICALCOLUMNVECTOR(P) (mxIsLogical(P) && mxGetN(P) == 1)
#define ISLOGICALMATRIX(P) (mxIsLogical(P))
#define ISINT32MATRIX(P) (mxIsInt32(P))
/* computational subroutine */
void Visibility(double *x, int n, bool *a, int *k, int *k_in, int *k_out){
    FILE * pFile;
    int i, j,ip;
    double m, new_m;
    pFile = fopen ("hfile.txt","w");
    for(i=0;i<n-1;i++){
        ip=i+1;
        a[n*i+ip]=1;
        a[n*ip+i]=1;
        fprintf(pFile,"%d %d\n",i+1,ip+1);
        k[i]++;
        k[ip]++;
        k_out[i]++;
        k_in[ip]++;
        m=x[ip]-x[i];
        for(j=1;j<n-i;j++){
            new_m= (x[i+j]-x[i])/j;
            if(m<new_m){
                ip=i+j;
                fprintf(pFile,"%d %d\n",i+1,ip+1);
                a[n*i+ip]=1;
                a[n*ip+i]=1;
                k[i]++;
                k[ip]++;
                k_out[i]++;
                k_in[ip]++;
                m=new_m;
            }
        }
    }
    fclose(pFile);
}
void HVisibility(double *x, int n, bool *a, int *k, int *k_in, int *k_out){
    FILE * pFile;
    int i, j, ip,al,l=0;
    double crit,pen;
    pFile = fopen ("hfile.txt","w");
    for(i=0;i<n-1;i++){
        ip=1+i;
        a[n*i+ip]=1;
        a[n*ip+i]=1;
        fprintf(pFile,"%d %d\n",i+1,ip+1);
        k[i]++;
        k[ip]++;
        k_out[i]++;
        k_in[ip]++;
        for(j=1;j<n-i;j++){
            if(x[ip]>=x[i]) break;
            if(x[ip]<x[i+j]){
                ip=i+j;
                a[n*i+ip]=1;
                a[n*ip+i]=1;
                k[i]++;
                k[ip]++;
                k_out[i]++;
                k_in[ip]++;
                fprintf(pFile,"%d %d\n",i+1,ip+1);
            }
        }
    }
    fclose(pFile);
}
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
//declare variables
    mxArray *H0,*H1,*H2,*H3;
    double *x;
    int i,j,n,*k,*k_in,*k_out,opt;
    bool *a;
/* Check the number of arguments */
    if(nrhs < 1 || nrhs > 2) mexErrMsgTxt("Wrong number of input arguments.");
    if(nlhs > 5) mexErrMsgTxt("Too many output arguments.");
/* Check arguments */
    if(!ISREALCOLUMNVECTORDOUBLE(prhs[0])) mexErrMsgTxt("x must be a double column vector.");
    if(!ISREALSCALAR(prhs[1])) mexErrMsgTxt("opt must be a real double scalar.");;
//get dimensions
    n=(int)mxGetM(prhs[0]);
//get scalar input
    opt=int(mxGetScalar(prhs[1]));
//associate outputs
    H0 = plhs[0] = mxCreateNumericMatrix(n,n,mxLOGICAL_CLASS,mxREAL);
    H1 = plhs[1] = mxCreateNumericMatrix(1,n,mxINT32_CLASS,mxREAL);
    H2 = plhs[2] = mxCreateNumericMatrix(1,n,mxINT32_CLASS,mxREAL);
    H3 = plhs[3] = mxCreateNumericMatrix(1,n,mxINT32_CLASS,mxREAL);
//associate pointer
    x=mxGetPr(prhs[0]);
    a =(bool *)mxGetPr(H0);
    k =(int *)mxGetPr(H1);
    k_in =(int *)mxGetPr(H2);
    k_out =(int *)mxGetPr(H3);
// do Visibility
    if(opt==1) HVisibility(x,n,a,k,k_in,k_out);
    else  Visibility(x,n,a,k,k_in,k_out);
}
