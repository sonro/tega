# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- `TERR_Res` in `tega/err.h` for error handling.

#### `tega/fundamental.h`

Interface for general programming utilities.

- `TFUN_Bytes` a byte array-list.
- `TFUN_BSlice` a slice of a byte array.
- `TFUN_CString` and `TFUN_WString` standard C and wide character string
  array-lists.
- `TFUN_CStrSlice` and `TFUN_WStrSlice` string slices.

#### Documentation

- API, internal, and common developer docs in markdown format.
- Naming conventions used in TEGA.

### Changed

- **BREAKING**: `TE_` types moved to separate header "tega/terminal.h" and
  renamed to `TERM_`.
- **BREAKING**: Type function and enum naming revised.
  - All enums are namespaced to be the _type_ then the snake_case enum variant.
  - All functions are namespaced to be the _type_ then the camelCase function
    name.

## [0.0.1] - 2024-08-19

### Added

- Test runner.
- Outline tega types.
- Specify `TEGA_Solidity` interface.
- Implement `TEGA_Solidity` interface.
- Add `TEGA_Type` for type erasure.

## [0.0.0] - 2024-08-18

### Added

- Zig build system.
- Make build system.

[Unreleased]: https://github.com/sonro/tega/compare/v0.0.1...HEAD
[0.0.1]: https://github.com/sonro/tega/releases/tag/v0.0.1
[0.0.0]: https://github.com/sonro/tega/releases/tag/v0.0.0
