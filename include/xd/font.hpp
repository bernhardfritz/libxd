#ifndef FONT_HPP
#define FONT_HPP

#include <stddef.h>
#include <stdint.h>
#include <xd/texture.hpp>

namespace xd {

typedef struct
{
    uint32_t codepoint;
    float kerning;
} xd_kerning_t;

typedef struct
{
    uint32_t codepoint;
    int width, height;
    int offset_x, offset_y;
    float advance_x, advance_y;
    float s0, t0, s1, t1;
    size_t kerning_count;
    xd_kerning_t* kerning;
} xd_texture_glyph_t;

typedef struct
{
    size_t tex_width;
    size_t tex_height;
    size_t tex_depth;
    char* tex_data;
    float size;
    float height;
    float linegap;
    float ascender;
    float descender;
    size_t glyphs_count;
    xd_texture_glyph_t* glyphs;
} xd_texture_font_t;

class Font {
public:
    xd_texture_font_t f;
    Texture* texture;
    Font(void* p, size_t max_kerning_count);
    ~Font();

    void init();
};

} // namespace xd

#endif /* FONT_HPP */