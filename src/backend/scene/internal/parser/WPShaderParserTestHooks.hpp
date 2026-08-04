#pragma once

#include <string>
#include <string_view>

namespace wallpaper::test
{
std::string NormalizePackedAudioSpectrumAccess(std::string_view source);
std::string NormalizeLegacyAudioSpectrumClamp(std::string_view source);
} // namespace wallpaper::test
