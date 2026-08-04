#pragma once

#include <cstddef>
#include <optional>
#include <span>
#include <string>
#include <string_view>

namespace wallpaper::audio
{

struct AudioDeviceCandidate {
    std::string id;
    std::string name;
    bool        is_default { false };
};

std::optional<std::size_t>
SelectMonitorCaptureDevice(std::span<const AudioDeviceCandidate> playback_devices,
                           std::span<const AudioDeviceCandidate> capture_devices);

bool CaptureRouteNeedsReconnect(std::string_view current_capture_key, bool capture_started,
                                std::string_view selected_capture_key);

} // namespace wallpaper::audio
