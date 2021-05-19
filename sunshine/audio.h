#ifndef SUNSHINE_AUDIO_H
#define SUNSHINE_AUDIO_H

#include "thread_safe.h"
#include "utility.h"
namespace audio {
enum stream_config_e : int {
  STEREO,
  SURROUND51,
  HIGH_SURROUND51,
  SURROUND71,
  HIGH_SURROUND71,
  MAX_STREAM_CONFIG
};

struct opus_stream_config_t {
  std::int32_t sampleRate;
  int channelCount;
  int streams;
  int coupledStreams;
  const std::uint8_t *mapping;
};

extern opus_stream_config_t stream_configs[MAX_STREAM_CONFIG];

struct config_t {
  int packetDuration;
  int channels;
  int mask;

  bool high_quality;
};

using packet_t       = util::buffer_t<std::uint8_t>;
using packet_queue_t = std::shared_ptr<safe::queue_t<std::pair<void *, packet_t>>>;
void capture(safe::signal_t *shutdown_event, packet_queue_t packets, config_t config, void *channel_data);
} // namespace audio

#endif
