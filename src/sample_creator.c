#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("sem argumento de entrada");
    exit(1);
  }
  FILE *fp = fopen("sample.txt", "w");
  if (!fp)
    exit(1);
  int sampleSize;
  sampleSize = atoi(argv[1]);
  fprintf(fp, "%d\n\n", sampleSize);

  srand(time(NULL));

  float x, y;

  int i;
  for (i = 0; i < sampleSize; i++) {
    x = (float) rand() / (float) RAND_MAX * (sampleSize * 2) - sampleSize;
    y = (float) rand() / (float) RAND_MAX * (sampleSize * 2) - sampleSize;
    fprintf(fp, "%f %f\n", x, y);
  }

  fclose(fp);
  exit(0);
}
