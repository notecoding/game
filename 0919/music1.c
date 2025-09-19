#include <stdio.h>
#include <math.h>

void print_frequency(int octave);

int main(void) {
    char *scale[] = { "도", "도#", "레", "레#", "미", 
                      "파", "파#", "솔", "솔#", "라", "라#", "시" };

    int i, octave;

    printf("음계와 주파수\n\n");
    printf("옥타브\t");

    for (i = 0; i < 12; i++) {
        printf("%-6s", scale[i]);
    }

    printf("\n");

    for (i = 0; i < 80; i++) {
        printf("-");
    }
    printf("\n");

    for (octave = 1; octave < 7; octave++) {
        print_frequency(octave);
    }

    return 0;
}

void print_frequency(int octave) {
    double do_scale = 32.7032;
    double ratio = pow(2.0, 1.0 / 12.0);
    double temp = do_scale * pow(2.0, octave - 1);
    int i;

    printf("%3d옥타브\t", octave);

    for (i = 0; i < 12; i++) {
        printf("%-6lu", (unsigned long)(temp + 0.5));
        temp *= ratio;
    }

    printf("\n");
}
