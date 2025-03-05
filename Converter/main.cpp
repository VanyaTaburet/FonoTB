#include "converter.hpp"
#include <iostream>
#include <fstream>

int main() {
  std::string filename;
  uint16_t encoding;
  uint16_t channels;
  uint32_t sample_rate;

  std::cout << "File name\n";
  std::cin >> filename;
  std::cout << "Encoding (x-bit PCM)\n";
  std::cin >> encoding;
  std::cout << "Channels\n";
  std::cin >> channels;
  std::cout << "Sample rate\n";
  std::cin >> sample_rate;

  std::string hex_data;
  std::ifstream input("../raw/" + filename);
  std::getline(input, hex_data);

  std::vector<int16_t> samples = hex_to_samples(hex_data);
  std::string outfile = "../audiosamples/" + filename.substr(0, filename.find('.')) + ".wav";
  write_wav(outfile, samples, encoding, channels, sample_rate);

  return 0;
}