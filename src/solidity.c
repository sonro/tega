#include "tega.h"

static const bool is_seeable[] = {
    [TEGA_solidity_floor] = true,       [TEGA_solidity_window] = true,
    [TEGA_solidity_portal] = true,      [TEGA_solidity_solid] = true,

    [TEGA_solidity_decor] = true,       [TEGA_solidity_prism] = true,
    [TEGA_solidity_stage] = true,       [TEGA_solidity_fixture] = true,

    [TEGA_solidity_empty] = false,      [TEGA_solidity_void] = false,
    [TEGA_solidity_distortion] = false, [TEGA_solidity_dark_matter] = false,
};

static const bool is_perma_visible[] = {
    [TEGA_solidity_floor] = false,      [TEGA_solidity_window] = false,
    [TEGA_solidity_portal] = false,     [TEGA_solidity_solid] = false,

    [TEGA_solidity_decor] = true,       [TEGA_solidity_prism] = true,
    [TEGA_solidity_stage] = true,       [TEGA_solidity_fixture] = true,

    [TEGA_solidity_empty] = false,      [TEGA_solidity_void] = false,
    [TEGA_solidity_distortion] = false, [TEGA_solidity_dark_matter] = false,
};

static const bool is_transparent[] = {
    [TEGA_solidity_floor] = true,       [TEGA_solidity_window] = true,
    [TEGA_solidity_portal] = false,     [TEGA_solidity_solid] = false,

    [TEGA_solidity_decor] = true,       [TEGA_solidity_prism] = true,
    [TEGA_solidity_stage] = false,      [TEGA_solidity_fixture] = false,

    [TEGA_solidity_empty] = true,       [TEGA_solidity_void] = true,
    [TEGA_solidity_distortion] = false, [TEGA_solidity_dark_matter] = false,
};

static const bool is_traversable[] = {
    [TEGA_solidity_floor] = true,      [TEGA_solidity_window] = false,
    [TEGA_solidity_portal] = true,     [TEGA_solidity_solid] = false,

    [TEGA_solidity_decor] = true,      [TEGA_solidity_prism] = false,
    [TEGA_solidity_stage] = true,      [TEGA_solidity_fixture] = false,

    [TEGA_solidity_empty] = true,      [TEGA_solidity_void] = false,
    [TEGA_solidity_distortion] = true, [TEGA_solidity_dark_matter] = false,
};

bool TEGA_solidityIsSeeable(TEGA_Solidity solidity) {
    return is_seeable[solidity];
}

bool TEGA_solidityIsPermaVisible(TEGA_Solidity solidity) {
    return is_perma_visible[solidity];
}

bool TEGA_solidityIsInvisible(TEGA_Solidity solidity) {
    return !is_seeable[solidity];
}

bool TEGA_solidityIsTransparent(TEGA_Solidity solidity) {
    return is_transparent[solidity];
}

bool TEGA_solidityIsOpaque(TEGA_Solidity solidity) {
    return !is_transparent[solidity];
}

bool TEGA_solidityIsTraversable(TEGA_Solidity solidity) {
    return is_traversable[solidity];
}

bool TEGA_solidityIsObstructive(TEGA_Solidity solidity) {
    return !is_traversable[solidity];
}
