#include <assert.h>
#include <string.h>
#include <stdio.h>

#define FTOA_IMPLEMENTATION
#include "ftoa.h"

#define STB_SPRINTF_IMPLEMENTATION
#include "vendor/stb_sprintf.h"

#define CHECK_END()                                                            \
   if ((int)stb_len != ftoa_len || strncmp(stb_buf, ftoa_buf, stb_len)) {      \
     printf("< '%s'\n> '%s'\n", stb_buf, ftoa_buf);                            \
     assert(!"Fail");                                                          \
   }

typedef struct Float_Single_Test {
   double value;
   long prec;
   char fmt;
   char *printf_fmt;
} Float_Single_Test;

typedef struct Float_Double_Test {
   double value[2];
   long prec;
   char fmt;
   char *printf_fmt;
} Float_Double_Test;

int main(void)
{
   char stb_buf[1024] = {0};
   char ftoa_buf[1024] = {0};

   Float_Single_Test tests_single[] = {
      { -3.0, -1, 'f', "%f" },
      { -8.88888888, 10, 'f', "%.10f" },
      { -880.88888888, 10, 'f', "%.10f" },
      { 4.1, 1, 'f', "%.1f" },
      { 0.1, 0, 'f', "%.0f" },
      { 1e-4, 2, 'f', "%.2f" },
      { -5.2, 2, 'f', "%.2f" },
      { 0., 1, 'f', "%.1f" },
      { -0., -1, 'f', "%f" },
      { 9.09834e-07, -1, 'f', "%f" },
      { 38685626227668133590597632.0, 1, 'f', "%.1f" },
      { 5e-7, 24, 'f', "%.24f" },
      { 1e-8, 10, 'f', "%.10f" },
      { 100056789.0, 1, 'f', "%.1f" },
      { 1.23, 2, 'f', "%.2f" },
      { -3.0, -1, 'e', "%e" },
      { 4.1, 1, 'E', "%.1E" },
      { -5.2, 2, 'e', "%.2e" },
      { 3.1415962, -1, 'g', "%g" },
      { 4.1, 1, 'G', "%.1G" },
      { 3e-300, -1, 'g', "%g" },
      { 1.2, 0, 'g', "%.0g" },
   };

   Float_Double_Test tests_double[] = {
      {{0.3, -3.0}, -1, 'g', "%g %g"},
      {{3.704, 3.706}, 3, 'g', "%.3g %.3g"},
   };


   puts("Starting tests...\n");
   for (size_t i = 0; i < sizeof(tests_single) /
         sizeof(tests_single[0]); i += 1) {
      Float_Single_Test test = tests_single[i];

      int ftoa_len = ftoa(ftoa_buf, test.fmt, test.prec, test.value, 0);
      stbsp_sprintf(stb_buf, test.printf_fmt, test.value);
      size_t stb_len = strlen(stb_buf);

      CHECK_END();
   }

   for (size_t i = 0; i < sizeof(tests_double) /
         sizeof(tests_double[0]); i += 1) {
      Float_Double_Test test = tests_double[i];

      int ftoa_len = ftoa(ftoa_buf, test.fmt, test.prec, test.value[0], 0);
      ftoa_buf[ftoa_len++] = ' ';
      ftoa_len += ftoa(&ftoa_buf[ftoa_len], test.fmt, test.prec, test.value[1], 0);

      stbsp_sprintf(stb_buf, test.printf_fmt, test.value[0], test.value[1]);
      size_t stb_len = strlen(stb_buf);

      CHECK_END();
   }
   puts("Tests passed!\n");
}
