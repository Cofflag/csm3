#include "global.h"
#include "copy.h"
#include "gba/syscall.h"
#include "data.h"
#include "functions.h"

const u8 gUnk_080BAAEC[3][4] = {
        8, 0x10, 0x20, 0x40,
        8,    8, 0x10, 0x20,
     0x10, 0x20, 0x20, 0x40,
};

const u8 gUnk_080BAAF8[3][4] = {
        8, 0x10, 0x20, 0x40,
     0x10, 0x20, 0x20, 0x40,
        8,    8, 0x10, 0x20,
};

u16 sub_08009238(u8 a1, u8 a2)
{
    u16 result;
    u8 array1[3][4];
    u8 array2[3][4];
    const struct Unk_030040C0_8_4 *var2, *var;
    u32 id1, id2;
    u32 r0, r1;

    memcpy(array1, gUnk_080BAAF8, sizeof(gUnk_080BAAF8));
    memcpy(array2, gUnk_080BAAEC, sizeof(gUnk_080BAAEC));
    var2 = gUnk_030040C0[a1].unk8->unk4;
    var = var2 + a2;
    id1 = var->unk0 / 0x40;
    id2 = var->unk1 / 0x40;
    result = array2[id1][id2] * array1[id1][id2];
    // swap registers
    r1 = gUnk_030040C0[a1].unk0;
    r0 = 1;
    r0 &= r1;
    if (!r0)
        result /= 2;
    return result;
}

void sub_080092B0(void)
{
    sub_08009684();
    sub_080092EC();
    gUnk_03003CB0[1] = 0;
    gUnk_03003CB0[3] = 0;
}

void DmaCopyBufferToOam(void)
{
    DmaCopy32(3, gOamBuffer, OAM, OAM_SIZE);
}

void sub_080092EC(void)
{
    CpuFastFill(0x2e4, gOamBuffer, OAM_SIZE);
    CpuFill32(-1, gUnk_030037A0, 0x10);
    gUnk_03003CB0[0] = 0;
    gUnk_03003CB0[2] = 0;
}

void sub_08009334(u8 a1, struct Unk_08009334 *a2, u32 tilesVram, u32 *a4)
{
    struct Unk_030040C0 *var = &gUnk_030040C0[a1];

    var->unk0 = a2->unk0;
    var->unk2 = (tilesVram - 0x6010000) / 32; // 4BPP
    var->unk4 = a2->unk10;
    var->unk8 = a2->unk18;
    var->unkC = a4;
}

void sub_08009364(u8 a1, u16 a2, struct Unk_030040C0_8 *a3)
{
    struct Unk_030040C0 *var = &gUnk_030040C0[a1];

    var->unk0 = a2;
    var->unk8 = a3;
}

u32 *sub_08009378(u8 a1)
{
    struct Unk_030040C0 *var = &gUnk_030040C0[a1];

    return var->unkC;
}

u32 sub_08009388(u8 a1)
{
    return gUnk_030040C0[a1].unk2;
}

u8 sub_08009398(void)
{
    return gUnk_03003CB0[2];
}

void CpuClear16Bytes(void *a)
{
    CpuFill32(0, a, 0x10);
}

void sub_080093C0(struct Unk_08009400 *a)
{
    u32 v1 = gUnk_03003CB0[0];
    struct Unk_03003CC0 *var = &gUnk_03003CC0[v1];
    if (v1 != 0x80)
    {
        var->unk0 = a;
        var->unk4 = gUnk_030037A0[a->unk8];
        gUnk_030037A0[a->unk8] = v1;
        gUnk_03003CB0[0] = gUnk_03003CB0[0] + 1;
    }
}

void sub_08009400(struct Unk_08009400 *r0, u8 r1, u8 r2)
{
    struct Unk_030040C0_8_4 *var = gUnk_030040C0[r1].unk8->unk4;
    struct Unk_030040C0_8_4 *r3 = var + r2;
    u16 idx2;

    r0->unkC = r3->unk0;
    r0->unkD = r3->unk1;
    idx2 = r3->unk2;
    r0->unkE = gUnk_030040C0[r1].unk2 + idx2;
}

void sub_08009434(struct Unk_08009400 *r0, struct Unk_030040C0_8 *r1, u16 r2)
{
    r0->unkC = r1->unk0;
    r0->unkD = r1->unk1;
    r0->unkE = r2 + r1->unk2;
}

void sub_08009448(struct Unk_08009400 *r0, u8 b)
{
    r0->unk2 = b;
}

void sub_0800944C(struct Unk_08009400 *r0, u8 b, u8 c)
{
    r0->unk8 = b;
    r0->unk9 = c;
}

void sub_08009454(struct Unk_08009400 *r0, u32 r1, u32 r2)
{
    if (r1 == 1)
    {
        r0->unk0 &= ~1;
        r0->unk0 |= 0x80;
    }
    else
    {
        r0->unk0 &= ~0x80;
    }
    if (r2 == 1)
    {
        r0->unk0 &= ~1;
        r0->unk0 |= 0x40;
    }
    else
    {
        r0->unk0 &= ~0x40;
    }
}

void sub_08009490(struct Unk_08009400 *r0, u8 r1)
{
    r0->unk1 = r1;
}

void sub_08009494(struct Unk_08009400 *r0, u16 r1, u8 r2)
{
    if (r1 == 1)
    {
        r0->unk0 |= 2;
    }
    else
    {
        r0->unk0 &= ~2;
    }
    if (r2 != 0xff)
    {
        r0->unk0 &= ~0xc0;
        r0->unk0 |= 1;
        r0->unk3 = r2;
    }
    else
    {
        r0->unk0 &= ~1;
        r0->unk3 = 0;
    }
}

void sub_080094D8(struct Unk_080094D8 *r0, u16 r1)
{
    if (r1 == 1)
    {
        r0->unk0 |= 0x10;
    }
    else
    {
        r0->unk0 &= ~0x10;
    }
}

void sub_080094F8(struct Unk_080094D8 *r0, u16 *r1, u16 *r2) //no reference
{
    if (r0->unk0 & 1)
    {
        *r1 = 0;
        *r2 = 0;
    }
    else
    {
        if (r0->unk0 & 0x80)
            *r1 = 1;
        else
            *r1 = 0;
        if (r0->unk0 & 0x40)
            *r2 = 1;
        else
            *r2 = 0;
    }
}

u8 sub_08009538(u8 a1, u8 a2)
{
    u8 array[3][4];
    const struct Unk_030040C0_8_4 *var2, *var;

    memcpy(array, gUnk_080BAAEC, sizeof(gUnk_080BAAEC));
    var2 = gUnk_030040C0[a1].unk8->unk4;
    var = var2 + a2;
    return array[var->unk0 / 0x40][var->unk1 / 0x40];
}

u8 sub_08009584(u8 a1, u8 a2)
{
    u8 array[3][4];
    const struct Unk_030040C0_8_4 *var2, *var;

    memcpy(array, gUnk_080BAAF8, sizeof(gUnk_080BAAF8));
    var2 = gUnk_030040C0[a1].unk8->unk4;
    var = var2 + a2;
    return array[var->unk0 / 0x40][var->unk1 / 0x40];
}

void sub_080095D0(u8 a1, u8 a2, u16 *a3, u16 *a4)
{
    u8 array1[3][4];
    u8 array2[3][4];
    const struct Unk_030040C0_8_4 *var2, *var;

    memcpy(array1, gUnk_080BAAF8, sizeof(gUnk_080BAAF8));
    memcpy(array2, gUnk_080BAAEC, sizeof(gUnk_080BAAEC));
    var2 = gUnk_030040C0[a1].unk8->unk4;
    var = var2 + a2;
    *a3 = array1[var->unk0 / 0x40][var->unk1 / 0x40];
    *a4 = array2[var->unk0 / 0x40][var->unk1 / 0x40];
}

u32 sub_08009654(u8 a1, u8 a2)
{
    const struct Unk_030040C0 *var3 = &gUnk_030040C0[a1];
    const struct Unk_030040C0_8_4 *var2 = var3->unk8->unk4;
    const struct Unk_030040C0_8_4 *var = var2 + a2;

    return ((var->unk2 & 0x3FF) + var3->unk2) * 0x20 + 0x06010000;
}
