#include <assert.h>
#include <string.h>
#include <stdio.h>

#define FTOA_IMPLEMENTATION
#include "ftoa.h"

#define STB_SPRINTF_IMPLEMENTATION
#include "vendor/stb_sprintf.h"

# define SPRINTF stbsp_sprintf
# define SNPRINTF stbsp_snprintf

// ftoa / stbsp_sprintf
#define CHECK_END()                                                           \
      if (stb_ret != ftoa_ret || strncmp(sprintf_buf, ftoa_buf, stb_ret)) {   \
         printf("< '%s'\n> '%s'\n", sprintf_buf, ftoa_buf);                   \
         assert(!"Fail");                                                     \
      }

int main(void)
{
   char sprintf_buf[1024] = {0};
   char ftoa_buf[1024] = {0};
   const double pow_2_75 = 37778931862957161709568.0;
   const double pow_2_85 = 38685626227668133590597632.0;

   // Tests taken from the library
   puts("Starting tests...\n");
   // floating-point numbers
   {
      double value = -3.0;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', -1, value);
      CHECK_END();
   }
   {
      double value = -8.88888888;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.10f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', 10, value);
      CHECK_END();
   }
   {
      double value = 880.08888888;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.10f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', 10, value);
      CHECK_END();
   }
   {
      double value = 4.1;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.1f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', 1, value);
      CHECK_END();
   }
   {
      double value = 0.1;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.0f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', 0, value);
      CHECK_END();
   }
   {
      double value = 1e-4;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.2f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', 2, value);
      CHECK_END();
   }
   {
      double value = -5.2;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.2f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', 2, value);
      CHECK_END();
   }
   {
      double value = 0.;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.1f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', 1, value);
      CHECK_END();
   }
   {
      double value = -0.;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', -1, value);
      CHECK_END();
   }
   {
      double value = 9.09834e-07;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', -1, value);
      CHECK_END();
   }
   {
      double value = 38685626227668133590597632.0;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.1f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', 1, value);
      CHECK_END();
   }
   {
      double value = 5e-7;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.24f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', 24, value);
      CHECK_END();
   }
   {
      double value = 2e-17;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.24f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', 24, value);
      CHECK_END();
   }
   {
      double value = 1e-8;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.10f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', 10, value);
      CHECK_END();
   }
   {
      double value = 100056789.0;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.1f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', 1, value);
      CHECK_END();
   }
   {
      double value = 1.23;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.2f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', 2, value);
      CHECK_END();
   }
   {
      double value = -3.0;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%e", value);
      int ftoa_ret = ftoa(ftoa_buf, 'e', -1, value);
      CHECK_END();
   }
   {
      double value = 4.1;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.1E", value);
      int ftoa_ret = ftoa(ftoa_buf, 'E', 1, value);
      CHECK_END();
   }
   {
      double value = -5.2;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.2e", value);
      int ftoa_ret = ftoa(ftoa_buf, 'e', 2, value);
      CHECK_END();
   }
   {
      double value1 = 0.3;
      double value2 = -3.0;

      int stb_ret = stbsp_sprintf(sprintf_buf, "%g %g", value1, value2);
      int ftoa_ret = ftoa(ftoa_buf, 'g', -1, value1);
      ftoa_buf[ftoa_ret++] = ' ';
      ftoa_ret += ftoa(&ftoa_buf[ftoa_ret], 'g', -1, value2);
      CHECK_END();
   }
   {
      double value = 4.1;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.1G", value);
      int ftoa_ret = ftoa(ftoa_buf, 'g', 1, value);
      CHECK_END();
   }
   {
      double value = 3e-300;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%g", value);
      int ftoa_ret = ftoa(ftoa_buf, 'g', -1, value);
      CHECK_END();
   }
   {
      double value = 1.2;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%.0g", value);
      int ftoa_ret = ftoa(ftoa_buf, 'g', 0, value);
      CHECK_END();
   }
   {
      double value = -3.0;
      int stb_ret = stbsp_sprintf(sprintf_buf, "%f", value);
      int ftoa_ret = ftoa(ftoa_buf, 'f', -1, value);
      CHECK_END();
   }
   {
      double value1 = 3.704;
      double value2 = 3.706;

      int stb_ret = stbsp_sprintf(sprintf_buf, "%.3g %.3g", value1, value2);
      int ftoa_ret = ftoa(ftoa_buf, 'g', 3, value1);
      ftoa_buf[ftoa_ret++] = ' ';
      ftoa_ret += ftoa(&ftoa_buf[ftoa_ret], 'g', 3, value2);
      CHECK_END();
   }
   {
      double value1 = 0.3;
      double value2 = -3.0;

      int stb_ret = stbsp_sprintf(sprintf_buf, "%g %g", value1, value2);
      int ftoa_ret = ftoa(ftoa_buf, 'g', -1, value1);
      ftoa_buf[ftoa_ret + 1] = ' ';
      ftoa_ret += 1;
      ftoa_ret += ftoa(&ftoa_buf[ftoa_ret], 'g', -1, value2);
      CHECK_END();
   }

   puts("Tests passed!\n");
}
