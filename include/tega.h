#pragma once

#define _XOPEN_SOURCE_EXTENDED

#include <stddef.h>
#include <stdint.h>
#include <wchar.h>

// tile = 1 x 1
// chunk = 3 x 2 tiles
// sector = 4 x 4 chunks
// zone = 4 x 4 sectors
// region = 4 x 4 zones

// Position within the terminal screen
typedef struct TE_TermPos {
    int32_t x;
    int32_t y;
} TE_TermPos;

// Position within a window
typedef struct TE_WinPos {
    int32_t x;
    int32_t y;
} TE_WinPos;

// Not guaranteed to be unique
typedef struct TEGA_Id {
    const uint32_t val;
} TEGA_Id;

typedef struct TEGA_Map {
    const TEGA_Id id;
    int32_t width;
    int32_t height;
    uint8_t region_count;
} TEGA_Map;

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

// Int representation of `TEGA_CharAttr`
// for more efficient memory usage
typedef uint8_t TEGA_CharAttrInt;

// Character attributes
typedef enum TEGA_CharAttr {
    TEGA_char_attr_normal = 0,
    TEGA_char_attr_bold = 1,
    TEGA_char_attr_blink = 2,
    TEGA_char_attr_underline = 3,
    TEGA_char_attr_reverse = 4,
    TEGA_char_attr_dimmed = 5,
    TEGA_char_attr_italic = 6,
} TEGA_CharAttr;

// Properties required to display an object
typedef struct TEGA_ViewProps {
    TEGA_ColorPairId color;
    TEGA_CharAttrInt attr;
    TEGA_Char character;
} TEGA_ViewProps;

// Int representation of `TEGA_Solidity`
// for more efficient memory usage
typedef uint8_t TEGA_SolidityInt;

// Traversability and visibility
typedef enum TEGA_Solidity {
    // can move but cannot see
    // good to fill in invisible areas
    TEGA_solidity_empty = 0,
    // can move and can see through
    TEGA_solidity_floor = 1,
    // can move but cannot see through
    TEGA_solidity_portal = 2,
    // cannot move but can see through
    TEGA_solidity_window = 3,
    // cannot move but can always see
    // good for behind walls
    TEGA_solidity_decor = 4,
    // cannot move and cannot see through
    // good for single tile walls
    TEGA_solidity_solid = 5,
    // cannot move and cannot see
    // good to fill in unreadable areas
    TEGA_solidity_void = 6,
} TEGA_Solidity;

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
