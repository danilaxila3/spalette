#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int *hsv2rgb(float H, float S, float V) {
  float r, g, b;

  float h = H / 360;
  float s = S / 100;
  float v = V / 100;

  int i = floor(h * 6);
  float f = h * 6 - i;
  float p = v * (1 - s);
  float q = v * (1 - f * s);
  float t = v * (1 - (1 - f) * s);

  switch (i % 6) {
  case 0:
    r = v, g = t, b = p;
    break;
  case 1:
    r = q, g = v, b = p;
    break;
  case 2:
    r = p, g = v, b = t;
    break;
  case 3:
    r = p, g = q, b = v;
    break;
  case 4:
    r = t, g = p, b = v;
    break;
  case 5:
    r = v, g = p, b = q;
    break;
  }

  int *rgb = (int *)malloc(3 * sizeof(int));

  rgb[0] = r * 255;
  rgb[1] = g * 255;
  rgb[2] = b * 255;

  return rgb;
}

int main() {
  int main_size;
  int mono_size;
  int main_s;
  int tint[3];
  float mix;

  char title[] = "\033[30;107m SPalette \033[0m\n";

  printf("\033[H\033[2J%s", title);

  printf("\033[mQuantity of main colors: \033[92m");
  scanf("%i", &main_size);

  printf("\033[mQuantity of monochrome colors: \033[92m");
  scanf("%i", &mono_size);

  printf("\033[mMain color saturation: \033[92m");
  scanf("%i", &main_s);

  printf("\033[mTint color RGB: \033[92m");
  scanf("%i %i %i", &tint[0], &tint[1], &tint[2]);

  printf("\033[mMix factor between main and tint (1 - 100): \033[92m");
  scanf("%f", &mix);
  mix *= 0.01;

  printf("\033[H\033[2J%s", title);

  printf("Main colors:        ");

  for (int i = 0; i < main_size; i++) {
    int *color = hsv2rgb(i * 360.0 / main_size, main_s, 100);
    color[0] = color[0] * (1 - mix) + tint[0] * mix;
    color[1] = color[1] * (1 - mix) + tint[1] * mix;
    color[2] = color[2] * (1 - mix) + tint[2] * mix;
    printf("\033[38;2;%i;%i;%im⬤\033[m ", color[0], color[1], color[2]);
  }

  printf("\nMonochrome colors:  ");

  for (int i = 0; i < mono_size; i++) {
    int color[3] = {i * 255.0 / mono_size, i * 255.0 / mono_size,
                    i * 255.0 / mono_size};
    color[0] = color[0] * (1 - mix) + tint[0] * mix;
    color[1] = color[1] * (1 - mix) + tint[1] * mix;
    color[2] = color[2] * (1 - mix) + tint[2] * mix;
    printf("\033[38;2;%i;%i;%im⬤\033[m ", color[0], color[1], color[2]);
  }

  printf("\n\nMain colors RGB:        ");

  for (int i = 0; i < main_size; i++) {
    int *color = hsv2rgb(i * 360.0 / main_size, main_s, 100);
    color[0] = color[0] * (1 - mix) + tint[0] * mix;
    color[1] = color[1] * (1 - mix) + tint[1] * mix;
    color[2] = color[2] * (1 - mix) + tint[2] * mix;
    printf("\033[48;2;%i;%i;%im(%i, %i, %i)\033[m ", color[0], color[1],
           color[2], color[0], color[1], color[2]);
  }

  printf("\nMonochrome colors RGB:  ");

  for (int i = 0; i < mono_size; i++) {
    int color[3] = {i * 255.0 / mono_size, i * 255.0 / mono_size,
                    i * 255.0 / mono_size};
    color[0] = color[0] * (1 - mix) + tint[0] * mix;
    color[1] = color[1] * (1 - mix) + tint[1] * mix;
    color[2] = color[2] * (1 - mix) + tint[2] * mix;
    printf("\033[48;2;%i;%i;%im(%i, %i, %i)\033[m ", color[0], color[1],
           color[2], color[0], color[1], color[2]);
  }
}
