#include "mp3_reader.h"

#include <cstring>
#include <iostream>

#include <SFML/System/InputStream.hpp>
#include <SFML/Audio/SoundFileFactory.hpp>

void mp3_reader::init() {
    if (mpg123_init() != MPG123_OK)
		std::cerr << "Failed to initialize mpg123" << std::endl;
	else {
		std::atexit(mpg123_exit);
	    sf::SoundFileFactory::registerReader<mp3_reader>();
    }
}

mp3_reader::mp3_reader() {
    handle_ = mpg123_new(nullptr, nullptr);

	if (handle_)
		mpg123_replace_reader_handle(handle_, read_cb, lseek_cb, nullptr);
}

mp3_reader::~mp3_reader() {
    mpg123_close(handle_);
	mpg123_delete(handle_);
}

bool mp3_reader::check(sf::InputStream& in) {
    char buf[3];
	in.read(buf, 3);

	return std::strncmp(buf, "ID3", 3) == 0 || (buf[0] = 0xff && (buf[1] & 0xf8) == 0xf8);
}

bool mp3_reader::open(sf::InputStream& in, Info& info) {
    if (!handle_)
		return false;

	if (mpg123_open_handle(handle_, &in) != MPG123_OK)
		return false;

	if (mpg123_scan(handle_) != MPG123_OK)
		return false;

	long rate;
	int channels;

	if (mpg123_getformat(handle_, &rate, &channels, nullptr) != MPG123_OK)
		return false;

	buf_size_ = mpg123_outblock(handle_);
	buf_ = std::make_unique<unsigned char[]>(buf_size_);

	info.sampleCount = static_cast<sf::Uint64>(mpg123_length(handle_)) * channels;
	info.channelCount = channels;
	info.sampleRate = rate;

	return true;
}

void mp3_reader::seek(sf::Uint64 sample_offset) {
    mpg123_seek(handle_, static_cast<off_t>(sample_offset), SEEK_SET);
}

sf::Uint64 mp3_reader::read(sf::Int16* samples, sf::Uint64 max_count) {
    size_t done;

	mpg123_read(handle_, buf_.get(), buf_size_, &done);
	std::memcpy(samples, buf_.get(), done);

	return done / sizeof(short);
}

ssize_t mp3_reader::read_cb(void* data, void* buf, std::size_t num) {
    auto in = static_cast<sf::InputStream*>(data);
	return in->read(buf, num);
}

off_t mp3_reader::lseek_cb(void* data, off_t offset, int whence) {
    auto in = static_cast<sf::InputStream*>(data);
	auto pos = 0LL;

	switch (whence) {
	case SEEK_CUR:
		pos = in->seek(in->tell() + offset);
		break;
	case SEEK_END:
		pos = in->seek(in->getSize() + offset);
		break;
	case SEEK_SET:
		pos = in->seek(offset);
		break;
	default:
		pos = in->tell();
		break;
	}

	return static_cast<off_t>(pos);
}
