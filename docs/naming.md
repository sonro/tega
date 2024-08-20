# TEGA Naming conventions

## General rules

Unless otherwise noted, all identifiers follow these rules:

- Abreviations not in all capitals. So `RPC` becomes `Rpc`.
- All 'public' identifiers have a [namespace](#namespaces).
- Shared internal identifiers(AKA 'internal') are namespaced and
  prefixed with `I_`.
- Internal identifiers that are _not_ shared(AKA 'private') omit the
  namespace and prefix, but must follow the same other rules as public
  identifiers.

## Namespaces

- `TEGA`: From [tega.h]. Core functionality of the game engine.
- `TFUN`: Primitive programming utilities. See [tega/fundamental.h].
  Useful abstractions over bytes and strings etc.
- `TLOG`: Logging features. See [tega/log.h].
- `TERR`: Error handling and reporting from [tega/error.h].
- `TERM`: Terminal screen interaction (primarily for internal use).
  See [tega/terminal.h].
- `TSYN`: For multithreading control. See [tega/sync.h].

Internal namespaces are prefixed with `I_`. So `I_TSYN` is internal
multithreading.

## Types

All types include the top level namespace, an underscore (`_`), and then
the type name in PascalCase e.g. `TSYN_MspcChannel`.

An internal type would be `I_TSYN_MspcChannel` and a private type
should just be `MspcChannel`.

Types are defined via `typedef`, and should be named twice.

```c
typedef struct TSYN_MspcChannel {
    // ...
} TSYN_MspcChannel;
```

## `#define` constants

`#define` constants are snake_case after the top level namespace e.g.
`TSYN_max_channels`(public), `I_LOG_message_size`(internal), or 
`global_log_level`(private).

## Global variables

Global variables should rarely be used in TEGA. When they are, they
must follow the same rules as `#define` constants - namespace then
snake_case e.g. `TERR_errno`.

## Struct fields

Struct fields are snake_case and are _never_ namespaced.

## Enum variants

Enum variants are namespaced to the enum's type, and then in snake_case.

```c
typedef enum TEGA_QuestKind {
    TEGA_QuestKind_boring,
    TEGA_QuestKind_well_done,
    // etc
} TSYN_LogLevel;
```

## Functions

Function names are camelCase. If the function is of an ascociated type,
then the type name is prefixed. e.g. `void TEGA_beAwesome()`,
`void I_TSYN_MspcChannel_beAwesome(I_TSYN_MspcChannel *channel)`.,

A private function should be `static` e.g. `static void callMe()`.

Functions that create a new object should just have the name `new` after
any prefixes. e.g. `TSYN_MspcChannel *TSYN_MspcChannel_new()`.

Functions that initialize an object should just have the name `init`
after any prefixes e.g.
`void TSYN_MspcChannel_init(TSYN_MspcChannel *channel)`.

Functions that make assumtions about safety should use the `Unsafe`
suffix e.g.
`void TFUN_Bytes_appendUnsafe(TFUN_Bytes *bytes, uint8_t byte)`.

Functions that destroy an object should just have the name `deinit`
after any prefixes e.g.
`void TSYN_MspcChannel_deinit(TSYN_MspcChannel *channel)`

## Variables

Variable names, including function parameters, are snake_case and are
_never_ namespaced.

## Files

Internal source files are _not_ namespaced and must be snake_case e.g.
`solidity.c` and `mspc_channel.c`.

Pubilc facing header files should be placed in the `include/tega/`
directory and be snake_case. Internal header files should be kept in
`src/` and be prefixed with `i_` e.g. `i_log.h`.

[tega.h]: /include/tega.h
[tega/fundamental.h]: /include/tega/fundamental.h
[tega/log.h]: /include/tega/log.h
[tega/error.h]: /include/tega/error.h
[tega/terminal.h]: /include/tega/terminal.h
[tega/sync.h]: /include/tega/sync.h
