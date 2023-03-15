#include <stdio.h>
#include <stdint.h>

#define DEBUG 1

typedef unsigned int uint;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef enum {
    PBM,
    PGM,
    PPM,
} file_type;

typedef struct {
    uint width, height;
    u32* pixels;
    file_type ft;
    FILE* file;
} image_t;

#define RED(p)          ((0xFF000000 & (p))>>(8*3))
#define GREEN(p)        ((0x00FF0000 & (p))>>(8*2))
#define BLUE(p)         ((0x0000FF00 & (p))>>(8*1))
#define ALPHA(p)        ((0x000000FF & (p))>>(8*0))
#define RGBA(r,g,b,a)   ((((RED(r))&0xFF)<<(8*3)) | (((GREEN(g))&0xFF)<<(8*2)) | (((BLUE(b))&0xFF)<<(8*1)) | (((ALPHA(a))&0xFF)<<(8*0)))

static inline int check_ft(file_type current, file_type correct) {
    return (current == correct) ? 0 : 1;
}

void ppm(image_t img) {
    if (check_ft(img.ft, PPM)) return;

    // header of filetype
    fprintf(img.file, "P3\n%i %i\n255\n", img.width, img.height);

    for (int y = 0; y < img.height; ++y) {
// TODO: May not need this debug
#if DEBUG
        fprintf(stderr, "\rScanlines done: %i/%i", y, img.height-1);
        fflush(stderr);
#endif
        for (int x = 0; x < img.width; ++x) {
            fprintf(img.file, "%i %i %i\n", RED(img.pixels[y * img.width + x]), GREEN(img.pixels[y * img.width + x]), BLUE(img.pixels[y * img.width + x]));
        }
    }
}

int main(void)
{
    uint width, height = 500;
    u32 nice[width * height];

    image_t image = (image_t){
        .width = 500,
        .height = 500,
        .pixels = nice,
        //.file = fopen(),
        .ft = PPM,
    };

    // for (int y = 0; y < height; ++y) {
    //     fprintf(stderr, "\rScanlines done: %i/%i", y, height-1);
    //     fflush(stderr);
    //     for (int x = 0; x < width; ++x) {
    //         float r = (double)x / (width - 1);
    //         float g = (double)y / (height - 1);
    //         float b = 0.25f;

    //         int ir = (int)(255.999 * r);
    //         int ig = (int)(255.999 * g);
    //         int ib = (int)(255.999 * b);

    //         // printf("%i %i %i\n", ir, ig, ib);
    //         nice[y * width + x] = ;
    //     }
    // }

    u32 red = 0xFF000000;
    u32 green = 0x00FF0000;
    u32 blue = 0x0000FF00;
    u32 alpha = 0x000000FF;

    u32 final = RGBA(red, green, blue, alpha);
    printf("%i %i %i %i %i\n", red, green, blue, alpha, final);

    return 0;
}
