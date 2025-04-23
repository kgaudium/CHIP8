//
// Created by gaudium on 13.01.2025.
//

#ifndef ROM_H
#define ROM_H
#include <cstddef>
#include <fstream>
#include <string>
#include <vector>


inline uint16_t ROM_START_ADDRESS = 0x200;
inline uint16_t MAX_ROM_LENGTH = 0xFFF - ROM_START_ADDRESS + 1;

inline std::vector<uint8_t> GetRomFileBytes(const std::string &filename) {
    std::ifstream fileStream(filename, std::ios_base::binary | std::ios_base::ate);
    if (!fileStream) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    const std::streamsize fileSize = fileStream.tellg();
    if (fileSize > MAX_ROM_LENGTH) {
        throw std::runtime_error(std::format("ROM is too large: {} > {}", fileSize, MAX_ROM_LENGTH));
    }
    fileStream.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(fileSize);

    if (!fileStream.read(reinterpret_cast<char *>(buffer.data()), fileSize)) {
        throw std::runtime_error("Error reading file: " + filename);
    }
    fileStream.close();

    return buffer;
}

class ROM {
    std::vector<uint8_t> bytes;

public:
    explicit ROM(const std::string &filename) {
        bytes = GetRomFileBytes(filename);
    }

    [[nodiscard]] const std::vector<uint8_t> &GetByteArray() const {
        return bytes;
    }

    void LoadToChip8(Chip8 &chip8) const {
        chip8.CopyToMemory(ROM_START_ADDRESS, bytes);
    }
};


#endif //ROM_H
