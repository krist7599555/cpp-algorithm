#include <ios>
long process_size_in_pages(void){
   long s = -1;
   FILE *f = fopen("/proc/self/statm", "r");
   if(f)
      fscanf(f, "%ld", &s),
      fclose(f);
   return s;
}
