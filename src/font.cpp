#include <xd/font.hpp>
#include <iostream>

using namespace std;

namespace xd {

Font::Font(void* p, size_t max_kerning_count) {
    char* c = (char*) p;
    f.tex_width = *((size_t*) c);
    c += 1 * sizeof(size_t) / sizeof(char);
    f.tex_height = *((size_t*) c);
    c += 1 * sizeof(size_t) / sizeof(char);
    f.tex_depth = *((size_t*) c);
    c += 1 * sizeof(size_t) / sizeof(char);
    f.tex_data = c;
    c += f.tex_width * f.tex_height * sizeof(char) / sizeof(char);
    f.size = *((float*) c);
    c += 1 * sizeof(float) / sizeof(char);
    f.height = *((float*) c);
    c += 1 * sizeof(float) / sizeof(char);
    f.linegap = *((float*) c);
    c += 1 * sizeof(float) / sizeof(char);
    f.ascender = *((float*) c);
    c += 1 * sizeof(float) / sizeof(char);
    f.descender = *((float*) c);
    c += 1 * sizeof(float) / sizeof(char);
    f.glyphs_count = *((size_t*) c);
    c += 1 * sizeof(size_t) / sizeof(char);
    f.glyphs = new xd_texture_glyph_t[f.glyphs_count];
    for (int i = 0; i < f.glyphs_count; i++) {
        xd_texture_glyph_t& g = f.glyphs[i];
        g.codepoint = *((uint32_t*) c);
        c += 1 * sizeof(uint32_t) / sizeof(char);
        g.width = *((int*) c);
        c += 1 * sizeof(int) / sizeof(char);
        g.height = *((int*) c);
        c += 1 * sizeof(int) / sizeof(char);
        g.offset_x = *((int*) c);
        c += 1 * sizeof(int) / sizeof(char);
        g.offset_y = *((int*) c);
        c += 1 * sizeof(int) / sizeof(char);
        g.advance_x = *((float*) c);
        c += 1 * sizeof(float) / sizeof(char);
        g.advance_y = *((float*) c);
        c += 1 * sizeof(float) / sizeof(char);
        g.s0 = *((float*) c);
        c += 1 * sizeof(float) / sizeof(char);
        g.t0 = *((float*) c);
        c += 1 * sizeof(float) / sizeof(char);
        g.s1 = *((float*) c);
        c += 1 * sizeof(float) / sizeof(char);
        g.t1 = *((float*) c);
        c += 1 * sizeof(float) / sizeof(char);
        g.kerning_count = *((size_t*) c);
        c += 1 * sizeof(size_t) / sizeof(char);
        g.kerning = new xd_kerning_t[g.kerning_count];
        for (int j = 0; j < g.kerning_count; j++) {
            xd_kerning_t& k = g.kerning[j];
            k.codepoint = *((uint32_t*) c);
            c += 1 * sizeof(uint32_t) / sizeof(char);
            k.kerning = *((float*) c);
            c += 1 * sizeof(float) / sizeof(char);
        }
        c += max_kerning_count > 0 ? (max_kerning_count - g.kerning_count) * sizeof(xd_kerning_t) / sizeof(char) : 1 * sizeof(xd_kerning_t) / sizeof(char);
    }
}

void Font::init() {
    texture = new Texture(f.tex_width, f.tex_height, GL_RED, f.tex_data);
}

Font::~Font() {
    for (int i = 0; i < f.glyphs_count; i++) {
        xd_texture_glyph_t& g = f.glyphs[i];
        delete[] g.kerning;
    }
    delete[] f.glyphs;

    delete texture;
}

}