#pragma once
#include <string>
#include <vector>
#include <cstring>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include<fstream>

class SHA256 {
private:
    uint32_t h[8];
    uint64_t length;
    uint8_t buffer[64];
    size_t buffer_len;
    static uint32_t k[64];


    static uint32_t rotr(uint32_t x, uint32_t n) { return (x >> n) | (x << (32 - n)); }


    void process_chunk(const uint8_t* chunk) {
        uint32_t w[64];
        for (int i = 0; i < 16; ++i) {
            w[i] = (chunk[i*4] << 24) | (chunk[i*4+1] << 16) | (chunk[i*4+2] << 8) | chunk[i*4+3];
        }
        for (int i = 16; i < 64; ++i) {
            uint32_t s0 = rotr(w[i-15],7) ^ rotr(w[i-15],18) ^ (w[i-15] >> 3);
            uint32_t s1 = rotr(w[i-2],17) ^ rotr(w[i-2],19) ^ (w[i-2] >> 10);
            w[i] = w[i-16] + s0 + w[i-7] + s1;
        }

        uint32_t a=h[0], b=h[1], c=h[2], d=h[3], e=h[4], f=h[5], g=h[6], h0=h[7];
        for (int i=0;i<64;i++){
            uint32_t S1 = rotr(e,6) ^ rotr(e,11) ^ rotr(e,25);
            uint32_t ch = (e & f) ^ (~e & g);
            uint32_t temp1 = h0 + S1 + ch + k[i] + w[i];
            uint32_t S0 = rotr(a,2) ^ rotr(a,13) ^ rotr(a,22);
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = S0 + maj;
            h0 = g; g = f; f = e; e = d + temp1;
            d = c; c = b; b = a; a = temp1 + temp2;
        }

        h[0] += a; h[1] += b; h[2] += c; h[3] += d;
        h[4] += e; h[5] += f; h[6] += g; h[7] += h0;
    }

public:
    SHA256() { reset(); }

    void reset() {
        h[0]=0x6a09e667; h[1]=0xbb67ae85; h[2]=0x3c6ef372; h[3]=0xa54ff53a;
        h[4]=0x510e527f; h[5]=0x9b05688c; h[6]=0x1f83d9ab; h[7]=0x5be0cd19;
        length = 0;
        buffer_len = 0;
    }

    void update(const uint8_t* data, size_t len) {
        for(size_t i=0;i<len;i++){
            buffer[buffer_len++] = data[i];
            length += 8;
            if(buffer_len==64){
                process_chunk(buffer);
                buffer_len=0;
            }
        }
    }

    void update(const std::string& data) { update(reinterpret_cast<const uint8_t*>(data.data()), data.size()); }

    std::string final() {
        buffer[buffer_len++] = 0x80;
        if(buffer_len > 56){
            while(buffer_len<64) buffer[buffer_len++]=0;
            process_chunk(buffer);
            buffer_len=0;
        }
        while(buffer_len<56) buffer[buffer_len++]=0;
        uint64_t len_be = length;
        for(int i=7;i>=0;i--){
            buffer[buffer_len++] = (len_be >> (i*8)) & 0xff;
        }
        process_chunk(buffer);

        std::stringstream ss;
        for(int i=0;i<8;i++){
            ss<<std::hex<<std::setw(8)<<std::setfill('0')<<h[i];
        }
        return ss.str();
    }

    static std::string hashFile(const std::string& filepath) {
        std::ifstream file(filepath, std::ios::binary);
        if(!file.is_open()) return "";
        SHA256 sha;
        std::vector<char> buf(8192);
        while(file.read(buf.data(), buf.size()) || file.gcount()>0){
            sha.update(reinterpret_cast<const uint8_t*>(buf.data()), file.gcount());
        }
        return sha.final();
    }
};

