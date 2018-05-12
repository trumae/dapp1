#ifndef __CPPJSINDEX__
#define __CPPJSINDEX__

#include<cstdint> 

namespace cppjsindex {
  /**
   * number by https://github.com/trumae/bigprimewithndigits and parameter 13 digits and nbase 100
   */
  const uint64_t prime = 9999999999299;

  uint64_t index(const char* s) {
    uint64_t r = 1;
    int i = 0;

    while(s[i]) {
      r *= s[i];
      r ++;
      r = r % prime;
      i++;
    }
    
    return r;
  }
}
#endif
