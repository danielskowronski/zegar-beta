#include "tools.h"

int obetnij(int wejscie, int max, bool symetric){
  if (symetric){
    if (wejscie<0-max) return max;
    if (wejscie>max) return 0-max;
  }
  else{
    if (wejscie<0) return max;
    if (wejscie>max) return 0;
  }
  return wejscie;
}
