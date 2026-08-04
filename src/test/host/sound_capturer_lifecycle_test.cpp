#include "host/audio/SoundCapturer.hpp"

#include <vector>

int main() {
    // The test remains valid on headless builders: initialization may report that no monitor is
    // available, but construction and destruction must always complete without deadlocking.
    wallpaper::audio::SoundCapturer capturer;
    capturer.Init();
    std::vector<float> left;
    std::vector<float> right;
    std::vector<float> average;
    capturer.GetSpectrum(64, &left, &right, &average);
    return 0;
}
