#include <cstdint>
#include <cstdlib>

#include "../xBRZ_1.9/xbrz.h"

extern "C" std::uint32_t *xbrz_scale6x(const std::uint32_t *src, int w, int h)
{
    if (!src || w <= 0 || h <= 0)
        return nullptr;

    const std::size_t factor = 6;
    const std::size_t outW = static_cast<std::size_t>(w) * factor;
    const std::size_t outH = static_cast<std::size_t>(h) * factor;

    std::uint32_t *dst = static_cast<std::uint32_t *>(
        std::malloc(outW * outH * sizeof(std::uint32_t)));
    if (!dst)
        return nullptr;

    xbrz::ScalerCfg cfg;
    xbrz::scale(factor, src, dst, w, h, xbrz::ColorFormat::argb, cfg, 0, h);

    return dst;
}

