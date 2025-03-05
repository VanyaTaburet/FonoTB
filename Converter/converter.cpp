#include "converter.hpp"
#include <iostream>
#include <fstream>

std::vector<int16_t> hex_to_samples(const std::string& hex)
{
  std::vector<int16_t> samples;
  for (size_t i = 0; i + 3 < hex.size(); i += 4) {
    std::string low_byte  = hex.substr(i, 2);
    std::string high_byte = hex.substr(i+2, 2);
    auto lb = static_cast<uint8_t>(std::stoi(low_byte,  nullptr, 16));
    auto hb = static_cast<uint8_t>(std::stoi(high_byte, nullptr, 16));
    auto sample = static_cast<int16_t>((hb << 8) | lb);
    samples.push_back(sample);
  }
  return samples;
}

void write_wav(const std::string& filename, const std::vector<int16_t>& samples, uint16_t bps, uint16_t channels, uint32_t sample_rate)
{
  std::ofstream out(filename, std::ios::binary);
  if (!out.is_open()) {
    std::cerr << "Failed to create file " << filename << "!\n";
    return;
  }

  uint32_t data_size = samples.size() * sizeof(int16_t);
  uint32_t subchunk_size = 16;
  uint16_t audio_format = 1;
  uint32_t byte_rate = sample_rate * channels * (bps / 8);
  uint16_t block_align = channels * (bps / 8);
  uint32_t chunk_size = 36 + data_size;

  out.write("RIFF", 4);

  out.put(static_cast<char>(chunk_size & 0xFF));
  out.put(static_cast<char>((chunk_size >> 8) & 0xFF));
  out.put(static_cast<char>((chunk_size >> 16) & 0xFF));
  out.put(static_cast<char>((chunk_size >> 24) & 0xFF));

  out.write("WAVE", 4);

  out.write("fmt ", 4);

  out.put(static_cast<char>(subchunk_size & 0xFF));
  out.put(static_cast<char>((subchunk_size >> 8) & 0xFF));
  out.put(static_cast<char>((subchunk_size >> 16) & 0xFF));
  out.put(static_cast<char>((subchunk_size >> 24) & 0xFF));

  out.put(static_cast<char>(audio_format & 0xFF));
  out.put(static_cast<char>((audio_format >> 8) & 0xFF));

  out.put(static_cast<char>(channels & 0xFF));
  out.put(static_cast<char>((channels >> 8) & 0xFF));

  out.put(static_cast<char>(sample_rate & 0xFF));
  out.put(static_cast<char>((sample_rate >> 8) & 0xFF));
  out.put(static_cast<char>((sample_rate >> 16) & 0xFF));
  out.put(static_cast<char>((sample_rate >> 24) & 0xFF));

  out.put(static_cast<char>(byte_rate & 0xFF));
  out.put(static_cast<char>((byte_rate >> 8) & 0xFF));
  out.put(static_cast<char>((byte_rate >> 16) & 0xFF));
  out.put(static_cast<char>((byte_rate >> 24) & 0xFF));

  out.put(static_cast<char>(block_align & 0xFF));
  out.put(static_cast<char>((block_align >> 8) & 0xFF));

  out.put(static_cast<char>(bps & 0xFF));
  out.put(static_cast<char>((bps >> 8) & 0xFF));

  out.write("data", 4);

  out.put(static_cast<char>(data_size & 0xFF));
  out.put(static_cast<char>((data_size >> 8) & 0xFF));
  out.put(static_cast<char>((data_size >> 16) & 0xFF));
  out.put(static_cast<char>((data_size >> 24) & 0xFF));

  out.write(reinterpret_cast<const char*>(samples.data()), data_size);

  out.close();
  std::cout << "File " << filename << " was successfully created!\n";
}