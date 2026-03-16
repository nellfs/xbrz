#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xbrz.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

static int has_png_extension(const char *path) {
    const char *ext = strrchr(path, '.');
    return ext && strcmp(ext, ".png") == 0;
}

static char *make_output_name(const char *input, int scale) {
    const char *dot = strrchr(input, '.');
    if (!dot) return NULL;

    size_t base_len = dot - input;
    // "-xbrzNx.png" + null = 12 chars at most (scale is 1 digit)
    char *out = malloc(base_len + 12);
    if (!out) return NULL;

    memcpy(out, input, base_len);
    sprintf(out + base_len, "-xbrz%dx.png", scale);
    return out;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s image.png\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    if (!has_png_extension(path)) {
        fprintf(stderr, "error: input must be a .png file\n");
        return 1;
    }

    int w, h;
    unsigned char *img = stbi_load(path, &w, &h, NULL, 4);
    if (!img) {
        fprintf(stderr, "error: failed to load '%s'\n", path);
        return 1;
    }
    printf("loaded %dx%d\n", w, h);

    const int scale = 6;
    uint32_t *scaled = xbrz_scale6x((uint32_t *)img, w, h);
    stbi_image_free(img);

    if (!scaled) {
        fprintf(stderr, "error: scaling failed (out of memory?)\n");
        return 1;
    }

    char *outname = make_output_name(path, scale);
    if (!outname) {
        fprintf(stderr, "error: failed to create output filename\n");
        free(scaled);
        return 1;
    }

    int ok = stbi_write_png(outname, w * scale, h * scale, 4, scaled, w * scale * 4);
    free(scaled);

    if (!ok) {
        fprintf(stderr, "error: failed to save '%s'\n", outname);
        free(outname);
        return 1;
    }

    printf("saved: %s\n", outname);
    free(outname);
    return 0;
}
