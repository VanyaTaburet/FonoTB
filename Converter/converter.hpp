#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <vector>
#include <cstdint>
#include <string>

std::vector<int16_t> hex_to_samples(const std::string& hex);
void write_wav(const std::string& filename, const std::vector<int16_t>& samples, uint16_t bps, uint16_t channels, uint32_t sample_rate);

#endif