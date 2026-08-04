#include "host/audio/SoundCaptureDeviceSelection.hpp"

#include <cassert>
#include <vector>

int main() {
    using wallpaper::audio::AudioDeviceCandidate;
    using wallpaper::audio::CaptureRouteNeedsReconnect;
    using wallpaper::audio::SelectMonitorCaptureDevice;

    const std::vector<AudioDeviceCandidate> playback_devices {
        { "sink-sunshine-stereo", "Sunshine", false },
        { "auto_null", "Virtual output", true },
    };
    const std::vector<AudioDeviceCandidate> capture_devices {
        { "sink-sunshine-stereo.monitor", "Monitor of Sunshine", false },
        { "auto_null.monitor", "Monitor of Virtual output", false },
    };
    const auto selected = SelectMonitorCaptureDevice(playback_devices, capture_devices);
    assert(selected.has_value());
    assert(*selected == 1);

    const std::vector<AudioDeviceCandidate> default_capture {
        { "microphone", "Microphone", false },
        { "fallback.monitor", "MONITOR of fallback", true },
    };
    const auto selected_default_capture = SelectMonitorCaptureDevice({}, default_capture);
    assert(selected_default_capture.has_value());
    assert(*selected_default_capture == 1);

    const std::vector<AudioDeviceCandidate> no_monitor {
        { "microphone", "Microphone", true },
    };
    assert(! SelectMonitorCaptureDevice({}, no_monitor).has_value());

    assert(! CaptureRouteNeedsReconnect("sink.monitor", true, "sink.monitor"));
    assert(CaptureRouteNeedsReconnect("sink-a.monitor", true, "sink-b.monitor"));
    assert(CaptureRouteNeedsReconnect("sink.monitor", false, "sink.monitor"));
    return 0;
}
