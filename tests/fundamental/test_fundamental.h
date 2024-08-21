#pragma once

#define TEST_ArrayList(_exp_ptr, _exp_len, _exp_cap, _list)                    \
    ({                                                                         \
        EXPECT(_exp_len == _list.len);                                         \
        EXPECT(_exp_cap == _list.cap);                                         \
        EXPECT(_exp_ptr == _list.ptr);                                         \
    })

#define TEST_ArrayList_notNull(_exp_len, _exp_cap, _list)                      \
    ({                                                                         \
        EXPECT(_exp_len == _list.len);                                         \
        EXPECT(_exp_cap == _list.cap);                                         \
        EXPECT(NULL != _list.ptr);                                             \
    })

#define TEST_ArrayList_notPtr(_not_ptr, _exp_len, _exp_cap, _list)             \
    ({                                                                         \
        EXPECT(_exp_len == _list.len);                                         \
        EXPECT(_exp_cap == _list.cap);                                         \
        EXPECT(_not_ptr != _list.ptr);                                         \
    })

#define TEST_ByteRes(_byte, _res)                                              \
    ({                                                                         \
        ASSERT(TERR_Res_success == _res.err);                                  \
        EXPECT(_byte == _res.byte);                                            \
    })

void testTFUN_addSaturate();
void testTFUN_ResTypes();
void testTFUN_Bytes();
