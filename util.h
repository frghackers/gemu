#ifndef UTIL_H
#define UTIL_H

#include "./types.h"
#include <stddef.h>

// https://gbdev.io/pandocs/STAT.html
#define LY   0xFF44
#define LYC  0xFF45
#define STAT 0xFF41

// https://gbdev.io/pandocs/Timer_and_Divider_Registers.html#ff04--div-divider-register
#define DIV 0xFF04

#define DMA 0xFF46

#define Z_BIT 7
#define N_BIT 6
#define H_BIT 5
#define C_BIT 4

#define Z_MASK (1 << Z_BIT)
#define N_MASK (1 << N_BIT)
#define H_MASK (1 << H_BIT)
#define C_MASK (1 << C_BIT)

// https://gbdev.io/pandocs/LCDC.html
#define LCDC 0xFF40

#define LCD_ENABLE          (1 << 7)
#define WINDOW_TILEMAP_AREA (1 << 6)
#define WINDOW_ENABLE       (1 << 5)
#define BG_WINDOW_DATA_AREA (1 << 4)
#define BG_TILEMAP_AREA     (1 << 3)
#define OBJ_SIZE            (1 << 2)
#define OBJ_ENABLE          (1 << 1)
#define BG_WINDOW_ENABLE    (1 << 0)

// https://gbdev.io/pandocs/OAM.html#byte-3--attributesflags
#define BG_OVER_OBJ         (1 << 7)
#define Y_FLIP              (1 << 6)
#define X_FLIP              (1 << 5)
#define PALETTE_NON_CGB_NUM (1 << 4)
#define TILE_VRAM_BANK      (1 << 3)
#define PALETTE_CGB_NUM     (0x0F & ~(1 << 3))

#define IO 0xFF00
#define IE 0xFFFF
#define IF 0xFF0F

#define IF_VBLANK   (1 << 0)
#define IF_LCD_STAT (1 << 1)
#define IF_TIMER    (1 << 2)
#define IF_SERIAL   (1 << 3)
#define IF_JOYPAD   (1 << 4)

extern const char *ROM_TYPES[256];
extern const char *NEW_LICENSEE_CODE[256];
extern const char *DESTINATION_CODE[2];
extern const char *OLD_LICENSEE_CODE[256];

// https://gbdev.io/pandocs/The_Cartridge_Header.html
typedef struct RomHeader {
  u8  entrypoint[4];
  u8  logo[0x30];
  u8  title[16];
  u16 new_lic_code;
  u8  sgb_flag;
  u8  type;
  u8  rom_size;
  u8  ram_size;
  u8  dest_code;
  u8  lic_code;
  u8  version;
  u8  checksum;
  u16 global_checksum;

} RomHeader;

// https://gbdev.io/pandocs/OAM.html
typedef struct SpriteAttribute {
  u8 yPos;
  u8 xPos;
  u8 tileIdx;
  u8 flags;
} SpriteAttribute;

typedef struct GameInput {
  bool right;
  bool left;
  bool up;
  bool down;

  bool a;
  bool b;
  bool select;
  bool start;
} GameInput;

typedef struct EmulationState {
  // Data
  u8 *mem;
  u8 *reg;
  u16 mcycle;

  // Pointer
  RomHeader       *header;
  u8              *tilemaps;
  SpriteAttribute *sprites;

  u8 *rom;
  u8 *vram;
  u8 *sram;
  u8 *wram;
  u8 *oam;
  u8 *io;
  u8 *hram;

  bool ime;

  // General Purpose Registers
  u8  *a;
  u8  *f;
  u16 *af;

  u8  *b;
  u8  *c;
  u16 *bc;

  u8  *d;
  u8  *e;
  u16 *de;

  u8  *h;
  u8  *l;
  u16 *hl;

  u16 *sp;
  u16 *pc;
} EmulationState;

void   print_bytes(void *p, size_t len);
size_t read_rom(const char *path, u8 *dst);
void   dump_file(const char *path, u8 *data, size_t length);
int    getch(void);

u8 get_palette_idx(u8 *tile_data, u8 i);

GameInput *gameinput_init();
void       gameinput_free(GameInput *input);

EmulationState *emu_init();
void            emu_print(EmulationState *emu);
void            emu_free(EmulationState *emu);

void set_flags(EmulationState *emu, char z, char n, char h, char c);

#define BIT_SET(a, n, x) \
  {                      \
    if (x)               \
      a |= (1 << n);     \
    else                 \
      a &= ~(1 << n);    \
  }
#define PRINT_BYTES(x) print_bytes(&x, sizeof(x))
#define LENGTH(x)      sizeof(x) / sizeof(x[0])

#endif // UTIL_H
