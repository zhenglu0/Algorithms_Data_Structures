#ifndef __PRNG_H
#define __PRNG_H

typedef long long int64;

class PRNG {
public:
  
  PRNG(int64 seed) 
  {
    state = (seed ^ A) & (M - 1);
    for (int j = 0; j < 100; j++)
      next();
  }
   
  double nextDouble()
  {
    int64 v = next();
    return (double) v / (double) (1L << 32);
  }
    
  ///////////////////////////////////////////////////
  
private:
  
  static const int64 M = (1LL << 48);
  static const int64 A = 25214903917LL;
  static const int64 C = 11LL;
			   
  int64 state;
    
  int64 next()
  {
    state = (A * state + C) & (M - 1);
    return (state >> 16);
  }
};

#endif
