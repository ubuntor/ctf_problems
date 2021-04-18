const uint8_t tile_count = 192;
const uint8_t _rom tiles[] _at(0x10000) = {
    0x00,0x7c,0x12,0x12,0x12,0x12,0x7c,0x00,
    0x00,0x7e,0x4a,0x4a,0x4a,0x4a,0x34,0x00,
    0x00,0x3c,0x42,0x42,0x42,0x42,0x24,0x00,
    0x00,0x7e,0x42,0x42,0x42,0x42,0x3c,0x00,
    0x00,0x7e,0x4a,0x4a,0x4a,0x4a,0x42,0x00,
    0x00,0x7e,0x12,0x12,0x12,0x12,0x02,0x00,
    0x00,0x3c,0x42,0x42,0x52,0x52,0x74,0x00,
    0x00,0x7e,0x10,0x10,0x10,0x10,0x7e,0x00,
    0x00,0x42,0x42,0x7e,0x42,0x42,0x00,0x00,
    0x00,0x42,0x42,0x3e,0x02,0x02,0x00,0x00,
    0x00,0x7e,0x10,0x18,0x24,0x42,0x00,0x00,
    0x00,0x7e,0x40,0x40,0x40,0x40,0x40,0x00,
    0x00,0x7e,0x04,0x08,0x08,0x04,0x7e,0x00,
    0x00,0x7e,0x04,0x08,0x10,0x20,0x7e,0x00,
    0x00,0x3c,0x42,0x42,0x42,0x42,0x3c,0x00,
    0x00,0x7e,0x12,0x12,0x12,0x12,0x0c,0x00,
    0x00,0x3c,0x42,0x42,0x52,0x22,0x5c,0x00,
    0x00,0x7e,0x12,0x12,0x12,0x12,0x6c,0x00,
    0x00,0x24,0x4a,0x4a,0x4a,0x4a,0x32,0x00,
    0x00,0x02,0x02,0x7e,0x02,0x02,0x00,0x00,
    0x00,0x3e,0x40,0x40,0x40,0x40,0x3e,0x00,
    0x00,0x0e,0x30,0x40,0x30,0x0e,0x00,0x00,
    0x00,0x7e,0x20,0x10,0x10,0x20,0x7e,0x00,
    0x00,0x42,0x24,0x18,0x18,0x24,0x42,0x00,
    0x00,0x02,0x04,0x78,0x04,0x02,0x00,0x00,
    0x00,0x42,0x62,0x52,0x4a,0x46,0x00,0x00,
    0x00,0x38,0x44,0x44,0x24,0x7c,0x00,0x00,
    0x00,0x7e,0x44,0x44,0x44,0x38,0x00,0x00,
    0x00,0x38,0x44,0x44,0x44,0x44,0x00,0x00,
    0x00,0x38,0x44,0x44,0x44,0x7e,0x00,0x00,
    0x00,0x38,0x54,0x54,0x54,0x58,0x00,0x00,
    0x00,0x7c,0x12,0x12,0x12,0x00,0x00,0x00,
    0x00,0x98,0xa4,0xa4,0xa4,0x78,0x00,0x00,
    0x00,0x7e,0x04,0x04,0x04,0x78,0x00,0x00,
    0x00,0x00,0x00,0x7a,0x00,0x00,0x00,0x00,
    0x00,0x00,0x80,0x80,0x7a,0x00,0x00,0x00,
    0x00,0x7e,0x10,0x10,0x28,0x44,0x00,0x00,
    0x00,0x00,0x00,0x7e,0x00,0x00,0x00,0x00,
    0x00,0x7c,0x04,0x08,0x04,0x7c,0x00,0x00,
    0x00,0x7c,0x08,0x04,0x04,0x78,0x00,0x00,
    0x00,0x38,0x44,0x44,0x44,0x38,0x00,0x00,
    0x00,0xfc,0x44,0x44,0x44,0x38,0x00,0x00,
    0x00,0x38,0x44,0x44,0x44,0xfc,0x00,0x00,
    0x00,0x7c,0x08,0x04,0x04,0x08,0x00,0x00,
    0x00,0x48,0x54,0x54,0x54,0x24,0x00,0x00,
    0x00,0x3e,0x48,0x48,0x48,0x00,0x00,0x00,
    0x00,0x3c,0x40,0x40,0x20,0x7c,0x00,0x00,
    0x00,0x0c,0x30,0x40,0x30,0x0c,0x00,0x00,
    0x00,0x7c,0x40,0x20,0x40,0x7c,0x00,0x00,
    0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00,
    0x00,0x9c,0xa0,0x40,0x20,0x1c,0x00,0x00,
    0x00,0x44,0x64,0x54,0x4c,0x44,0x00,0x00,
    0x00,0x3c,0x46,0x4a,0x52,0x62,0x3c,0x00,
    0x00,0x00,0x44,0x42,0x7e,0x40,0x00,0x00,
    0x00,0x64,0x52,0x52,0x52,0x52,0x4c,0x00,
    0x00,0x42,0x42,0x42,0x4a,0x4a,0x74,0x00,
    0x00,0x1e,0x10,0x10,0x78,0x10,0x10,0x00,
    0x00,0x4e,0x4a,0x4a,0x4a,0x4a,0x32,0x00,
    0x00,0x3c,0x4a,0x4a,0x4a,0x4a,0x30,0x00,
    0x00,0x02,0x42,0x22,0x12,0x0a,0x06,0x00,
    0x00,0x34,0x4a,0x4a,0x4a,0x4a,0x34,0x00,
    0x00,0x0c,0x52,0x52,0x52,0x52,0x3c,0x00,
    0x00,0x00,0x10,0x6c,0x82,0x00,0x00,0x00,
    0x00,0x00,0x00,0x82,0x6c,0x10,0x00,0x00,
    0x00,0x40,0x60,0x70,0x70,0x60,0x40,0x00,
    0x00,0x02,0x06,0x0e,0x0e,0x06,0x02,0x00,
    0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
