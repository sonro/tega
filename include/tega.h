
/** ========================================================
 * TEGA: Terminal Game Engine
 * ========================================================*/

#pragma once

#define _XOPEN_SOURCE_EXTENDED

#include <stddef.h>
#include <stdint.h>
#include <wchar.h>

// block = 2 x 1 tiles
#define TEGA_block_width 2
#define TEGA_block_height 1

// chunk = 8 x 8 blocks
#define TEGA_chunk_width 8
#define TEGA_chunk_height 8
#define TEGA_chunk_tile_width 16
#define TEGA_chunk_tile_height 8

// region = 4 x 4 chunks
#define TEGA_region_width 4
#define TEGA_region_height 4
#define TEGA_region_tile_width 64
#define TEGA_region_tile_height 32

// Not guaranteed to be unique
typedef struct TEGA_Id {
    const uint32_t val;
} TEGA_Id;

// Int representation of `TEGA_Kind` for efficient memory usage
typedef uint8_t TEGA_KindInt;

// Used for type erasure
typedef enum TEGA_Kind {
    TEGA_Kind_id,
    TEGA_Kind_kind,

    TEGA_Kind_rgb_color,
    TEGA_Kind_color_pair,
    TEGA_Kind_char,
    TEGA_Kind_char_attr,
    TEGA_Kind_view_props,
    TEGA_Kind_solidity,

    TEGA_Kind_entity,

    TEGA_Kind_tile,
    TEGA_Kind_block,
    TEGA_Kind_chunk,
    TEGA_Kind_region,
    TEGA_Kind_map,
} TEGA_Kind;

// Type erasure
typedef struct TEGA_Type {
    void *ptr;
    TEGA_Kind kind;
} TEGA_Type;

// Position within a map
typedef struct TEGA_MapPos {
    int32_t x;
    int32_t y;
} TEGA_MapPos;

typedef struct TEGA_RgbColor {
    const uint8_t r;
    const uint8_t g;
    const uint8_t b;
} TEGA_RgbColor;

// Must be unique
typedef struct TEGA_ColorPairId {
    const uint16_t val;
} TEGA_ColorPairId;

// Foreground and background
typedef struct TEGA_ColorPair {
    const TEGA_RgbColor fg;
    const TEGA_RgbColor bg;
} TEGA_ColorPair;

// Wide character
typedef struct TEGA_Char {
    wchar_t val;
} TEGA_Char;

// Int representation of `TEGA_CharAttr` for efficient memory usage
typedef uint8_t TEGA_CharAttrInt;

// Character attributes
typedef enum TEGA_CharAttr {
    TEGA_CharAttr_normal = 0,
    TEGA_CharAttr_bold = 1,
    TEGA_CharAttr_blink = 2,
    TEGA_CharAttr_underline = 3,
    TEGA_CharAttr_reverse = 4,
    TEGA_CharAttr_dimmed = 5,
    TEGA_CharAttr_italic = 6,
} TEGA_CharAttr;

// Properties required to display an object
typedef struct TEGA_ViewProps {
    TEGA_ColorPairId color;
    TEGA_CharAttrInt attr;
    TEGA_Char character;
} TEGA_ViewProps;

// Int representation of `TEGA_Solidity` for efficient memory usage
typedef uint8_t TEGA_SolidityInt;

// Traversability and visibility
typedef enum TEGA_Solidity {
    // seeable, transparent, traversible
    TEGA_Solidity_floor = 0,
    // seeable, transparent, obstructive
    TEGA_Solidity_window = 1,
    // seeable, opaque, traversible
    TEGA_Solidity_portal = 2,
    // seeable, opaque, obstructive
    TEGA_Solidity_solid = 3,

    // perma visible, transparent, traversible
    TEGA_Solidity_decor = 4,
    // perma visible, transparent, obstructive
    TEGA_Solidity_prism = 5,
    // perma visible, opaque, traversible
    TEGA_Solidity_stage = 6,
    // perma visible, opaque, obstructive
    TEGA_Solidity_fixture = 7,

    // invisible, transparent, traversible
    TEGA_Solidity_empty = 8,
    // invisible, transparent, obstructive
    TEGA_Solidity_void = 9,
    // invisible, opaque, traversible
    TEGA_Solidity_distortion = 10,
    // invisible, opaque, obstructive
    TEGA_Solidity_dark_matter = 11,
} TEGA_Solidity;

bool TEGA_Solidity_isSeeable(TEGA_Solidity solidity);
bool TEGA_Solidity_isPermaVisible(TEGA_Solidity solidity);
bool TEGA_Solidity_isInvisible(TEGA_Solidity solidity);

bool TEGA_Solidity_isTransparent(TEGA_Solidity solidity);
bool TEGA_Solidity_isOpaque(TEGA_Solidity solidity);

bool TEGA_Solidity_isTraversable(TEGA_Solidity solidity);
bool TEGA_Solidity_isObstructive(TEGA_Solidity solidity);

// Drawable object with a variable location in a `TEGA_Map`
typedef struct TEGA_Entity {
    const TEGA_Id id;
    TEGA_Solidity solidity;
    TEGA_ViewProps view;
    TEGA_MapPos pos;
} TEGA_Entity;

// Drawable object with a fixed location in a `TEGA_Map`
typedef struct TEGA_Tile {
    const TEGA_Id id;
    TEGA_Solidity solidity;
    TEGA_ViewProps view;
} TEGA_Tile;

// Growable map
typedef struct TEGA_Map {
    const TEGA_Id id;
    uint32_t tile_width;
    uint32_t tile_height;
    uint32_t region_count;
    TEGA_Tile *tiles;
} TEGA_Map;
