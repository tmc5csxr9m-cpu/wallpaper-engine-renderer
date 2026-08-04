#include "SoundCaptureDeviceSelection.hpp"

#include <algorithm>
#include <cctype>
#include <string_view>

namespace wallpaper::audio
{
namespace
{

bool ContainsAsciiCaseInsensitive(std::string_view text, std::string_view pattern) {
    return std::search(
               text.begin(), text.end(), pattern.begin(), pattern.end(), [](char lhs, char rhs) {
                   return std::tolower(static_cast<unsigned char>(lhs)) ==
                          std::tolower(static_cast<unsigned char>(rhs));
               }) != text.end();
}

bool IsMonitorDevice(const AudioDeviceCandidate& candidate) {
    return ContainsAsciiCaseInsensitive(candidate.name, "monitor") ||
           ContainsAsciiCaseInsensitive(candidate.id, ".monitor");
}

} // namespace

std::optional<std::size_t>
SelectMonitorCaptureDevice(std::span<const AudioDeviceCandidate> playback_devices,
                           std::span<const AudioDeviceCandidate> capture_devices) {
    for (const auto& playback : playback_devices) {
        if (! playback.is_default) continue;

        if (! playback.id.empty()) {
            const std::string expected_monitor_id = playback.id + ".monitor";
            for (std::size_t index = 0; index < capture_devices.size(); ++index) {
                if (capture_devices[index].id == expected_monitor_id) return index;
            }
        }

        if (! playback.name.empty()) {
            for (std::size_t index = 0; index < capture_devices.size(); ++index) {
                const auto& capture = capture_devices[index];
                if (IsMonitorDevice(capture) &&
                    ContainsAsciiCaseInsensitive(capture.name, playback.name)) {
                    return index;
                }
            }
        }
    }

    for (std::size_t index = 0; index < capture_devices.size(); ++index) {
        if (capture_devices[index].is_default && IsMonitorDevice(capture_devices[index])) {
            return index;
        }
    }

    for (std::size_t index = 0; index < capture_devices.size(); ++index) {
        if (IsMonitorDevice(capture_devices[index])) return index;
    }

    return std::nullopt;
}

bool CaptureRouteNeedsReconnect(std::string_view current_capture_key, bool capture_started,
                                std::string_view selected_capture_key) {
    return ! capture_started || current_capture_key != selected_capture_key;
}

} // namespace wallpaper::audio
