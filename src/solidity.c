#include "tega.h"

static const bool is_seeable[] = {
    [TEGA_Solidity_floor] = true,       [TEGA_Solidity_window] = true,
    [TEGA_Solidity_portal] = true,      [TEGA_Solidity_solid] = true,

    [TEGA_Solidity_decor] = true,       [TEGA_Solidity_prism] = true,
    [TEGA_Solidity_stage] = true,       [TEGA_Solidity_fixture] = true,

    [TEGA_Solidity_empty] = false,      [TEGA_Solidity_void] = false,
    [TEGA_Solidity_distortion] = false, [TEGA_Solidity_dark_matter] = false,
};

static const bool is_perma_visible[] = {
    [TEGA_Solidity_floor] = false,      [TEGA_Solidity_window] = false,
    [TEGA_Solidity_portal] = false,     [TEGA_Solidity_solid] = false,

    [TEGA_Solidity_decor] = true,       [TEGA_Solidity_prism] = true,
    [TEGA_Solidity_stage] = true,       [TEGA_Solidity_fixture] = true,

    [TEGA_Solidity_empty] = false,      [TEGA_Solidity_void] = false,
    [TEGA_Solidity_distortion] = false, [TEGA_Solidity_dark_matter] = false,
};

static const bool is_transparent[] = {
    [TEGA_Solidity_floor] = true,       [TEGA_Solidity_window] = true,
    [TEGA_Solidity_portal] = false,     [TEGA_Solidity_solid] = false,

    [TEGA_Solidity_decor] = true,       [TEGA_Solidity_prism] = true,
    [TEGA_Solidity_stage] = false,      [TEGA_Solidity_fixture] = false,

    [TEGA_Solidity_empty] = true,       [TEGA_Solidity_void] = true,
    [TEGA_Solidity_distortion] = false, [TEGA_Solidity_dark_matter] = false,
};

static const bool is_traversable[] = {
    [TEGA_Solidity_floor] = true,      [TEGA_Solidity_window] = false,
    [TEGA_Solidity_portal] = true,     [TEGA_Solidity_solid] = false,

    [TEGA_Solidity_decor] = true,      [TEGA_Solidity_prism] = false,
    [TEGA_Solidity_stage] = true,      [TEGA_Solidity_fixture] = false,

    [TEGA_Solidity_empty] = true,      [TEGA_Solidity_void] = false,
    [TEGA_Solidity_distortion] = true, [TEGA_Solidity_dark_matter] = false,
};

bool TEGA_Solidity_isSeeable(TEGA_Solidity solidity) {
    return is_seeable[solidity];
}

bool TEGA_Solidity_isPermaVisible(TEGA_Solidity solidity) {
    return is_perma_visible[solidity];
}

bool TEGA_Solidity_isInvisible(TEGA_Solidity solidity) {
    return !is_seeable[solidity];
}

bool TEGA_Solidity_isTransparent(TEGA_Solidity solidity) {
    return is_transparent[solidity];
}

bool TEGA_Solidity_isOpaque(TEGA_Solidity solidity) {
    return !is_transparent[solidity];
}

bool TEGA_Solidity_isTraversable(TEGA_Solidity solidity) {
    return is_traversable[solidity];
}

bool TEGA_Solidity_isObstructive(TEGA_Solidity solidity) {
    return !is_traversable[solidity];
}
