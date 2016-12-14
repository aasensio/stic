/* -------------------------------------
   
  Various math routines in template format

  Coded by J. de la Cruz Rodriguez (ISP-SU 2016)

  -------------------------------------- */

#ifndef MATH_H
#define MATH_H

#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdio>

namespace mth{

  inline double sqr(double a){return a*a;};
  inline float sqr(float a){return a*a;};

  
  /* --- sqr --- */
  
  template <class T> T sqr(T a){return a*a;};
  /* ------------------------------------------------------------------------------- */

  /* --- Sum, mean, stdev --- */
  
  template <class T> T sum(size_t n, T* a){
    T tot = 0;
    for(size_t ii=0;ii<n;ii++) tot += a[ii];
    return tot;
  }
  /* ------------------------------------------------------------------------------- */
  
  template <class T> T mean(size_t n, T* a){
    T tot = sum<T>(n, a);
    return tot/n;
  }
  /* ------------------------------------------------------------------------------- */
  
  template <class T> double stdev(size_t n, T* a){
    double res = 0.0;
    double a_mean = sum<T>(n, a) / (double)n;
    //
    for(size_t ii=0; ii<n; ii++) res += sqr<double>((double)a[ii]-a_mean);
    //
    return sqrt(res/(n-1.0));
  }
  /* ------------------------------------------------------------------------------- */
  
  /* --- more accurate Kahan addition --- */
  
  template <class T> double ksum(size_t n, T* arr){
    
    long double sum = 0.0L, c = 0.0L;
    
    for(size_t kk = 0; kk<n; kk++){
      long double y = arr[kk] - c;
      long double t = sum + y;
      c = (t - sum) - y;
      sum = t;
    }
    return (double)sum;
  }
  /* ------------------------------------------------------------------------------- */

  template <class T> double ksum2(size_t n, T* arr){
    
    long double sum = 0.0L, c = 0.0L;
    
    for(size_t kk = 0; kk<n; kk++){
      long double y = arr[kk]*arr[kk] - c;
      long double t = sum + y;
      c = (t - sum) - y;
      sum = t;
    }
    return (double)sum;
  }
  /* ------------------------------------------------------------------------------- */

  /* --- Dot product of vectors --- */

  template <class T> double dot(size_t n, T *a, T *b){
    double res = 0.0;
    for(size_t ii=0; ii<n; ii++) res += a[ii]*b[ii];
    return res;
  }
  /* ------------------------------------------------------------------------------- */

  template <class T> double kdot(size_t n, T *a, T* b){
    long double sum = 0.0L, c = 0.0L;
    for(size_t kk = 0; kk<n; kk++){
      long double y = a[kk]*b[kk] - c;
      long double t = sum + y;
      c = (t - sum) - y;
      sum = t;
    }
    return (double)sum;
  }
  /* ------------------------------------------------------------------------------- */
  
  template <class T> size_t argmax(size_t n, T *a){
    T mm = 0;
    size_t idx = 0;
    for(size_t ii=1; ii<n; ii++) if(a[ii] > mm){
	mm = a[ii];
	idx = ii;
      }
    return idx;
  }
  /* ------------------------------------------------------------------------------- */
  
  template <class T> size_t argmin(size_t n, T *a){
    T mm = 0;
    size_t idx = 0;
    for(size_t ii=1; ii<n; ii++) if(a[ii] < mm){
	mm = a[ii];
	idx = ii;
      }
    return idx;
  }
  /* ------------------------------------------------------------------------------- */
  
  template <class T> void convolve1D(size_t n, T *sp, size_t npsf, T *psf){
    
    size_t npsf2 = npsf / 2, ii = 0;
    double *tmp = new double [n];
    
    for(size_t ww = 0; ww < n; ww++){
      
      /* --- Define limits to integrate with the PSF --- */
      
      int w0 = std::max(ww-npsf2, 0), w1 = std::min(ww+npsf2, n-1), ii = w0 - (ww - npsf2);
      double sum = 0.0;

      /* --- Accumulate both the area of the PSF and the integrated data --- */
      
      for(int kk = w0; kk <= w1; kk++){
	tmp[ww] += psf[ii+kk-w0]*sp[kk];
	sum += psf[ii+kk-w0];
      }

      /* --- nomalize by the area of the PSF --- */
      
      tmp[ww] /= sum; 
    }

    
    /* --- Copy back array, cannot assume same type to use memcpy --- */
    
    for(size_t ii=0; ii<n; ii++) sp[ii] = (T)tmp[ii];

    
    /* --- Clean-up --- */
    
    delete [] tmp;
  }
  /* ------------------------------------------------------------------------------- */

} // namespace

#endif
