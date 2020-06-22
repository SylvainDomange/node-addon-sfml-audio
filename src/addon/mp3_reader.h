#pragma once

#include <memory>

#include <SFML/Audio/SoundFileReader.hpp>
#include <mpg123.h>

class mp3_reader : public sf::SoundFileReader {
public:
    static void init();

    mp3_reader();
    ~mp3_reader();

    static bool check(sf::InputStream& in);
    bool open(sf::InputStream& in, Info& info) override;
    void seek(sf::Uint64 sample_offset) override;
    sf::Uint64 read(sf::Int16* samples, sf::Uint64 max_count) override;

private:
    mpg123_handle* handle_{};
    std::size_t buf_size_{};
    std::unique_ptr<unsigned char[]> buf_;

    static ssize_t read_cb(void* data, void* buf, std::size_t num);
    static off_t lseek_cb(void* data, off_t offset, int whence);
};
