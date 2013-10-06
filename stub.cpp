#include "3d_def.h"


const int OLD_OBJTYPE_SIZE = 70;
const int OLD_STATOBJ_T_SIZE = 12;
const int OLD_DOOROBJ_T_SIZE = 16;


//
// Offsets of variables in data segment.
//

const int OBJLIST_OFFSET = 0xFFFF - (MAXACTORS * OLD_OBJTYPE_SIZE);
const int STATOBJLIST_OFFSET = 0xFFFF - (MAXSTATS * OLD_STATOBJ_T_SIZE);
const int DOOROBJLIST_OFFSET = 0xFFFF - (MAXDOORS * OLD_DOOROBJ_T_SIZE);


void ogl_update_screen();


void VL_WaitVBL (Uint32 vbls)
{
    SDL_Delay(8 * vbls);
}

void VH_UpdateScreen()
{
    ogl_update_screen();
}

void VL_ScreenToScreen(
    int source,
    int dest,
    int width,
    int height)
{
    source *= 4;
    dest *= 4;
    width *= 4;

    const Uint8* src = &vga_memory[source];
    Uint8* dst = &vga_memory[dest];

    for (int y = 0; y < height; ++y) {
        std::move(src, &src[width], dst);
        src += vanilla_screen_width;
        dst += vanilla_screen_width;
    }
}

void SDL_SetDS()
{
}

void SDL_t0FastAsmService()
{
}

void SDL_t0SlowAsmService()
{
}

Sint16 VL_VideoID ()
{
    return 5;
}

objtype* ui16_to_actor(Uint16 value)
{
    int offset = value - OBJLIST_OFFSET;

    if (offset >= 0) {
        int index = offset / OLD_OBJTYPE_SIZE;
        assert((offset % OLD_OBJTYPE_SIZE) == 0);
        return &objlist[index];
    }

    return NULL;
}

Uint16 actor_to_ui16(const objtype* actor)
{
    ptrdiff_t index = actor - objlist;

    if (index >= 0) {
        ptrdiff_t offset = OBJLIST_OFFSET + (index * OLD_OBJTYPE_SIZE);
        assert(offset <= 0xFFFF);
        return static_cast<Uint16>(offset);
    }

    return 0;
}

statobj_t* ui16_to_static_object(Uint16 value)
{
    int offset = value - STATOBJLIST_OFFSET;

    if (offset >= 0) {
        int index = offset / OLD_STATOBJ_T_SIZE;
        assert((offset % OLD_STATOBJ_T_SIZE) == 0);
        return &statobjlist[index];
    }

    return NULL;
}

Uint16 static_object_to_ui16(const statobj_t* static_object)
{
    ptrdiff_t index = static_object - statobjlist;

    if (index >= 0) {
        ptrdiff_t offset = STATOBJLIST_OFFSET + (index * OLD_STATOBJ_T_SIZE);
        assert(offset <= 0xFFFF);
        return static_cast<Uint16>(offset);
    }

    return 0;
}

doorobj_t* ui16_to_door_object(Uint16 value)
{
    int offset = value - DOOROBJLIST_OFFSET;

    if (offset >= 0) {
        int index = offset / OLD_DOOROBJ_T_SIZE;
        assert((offset % OLD_DOOROBJ_T_SIZE) == 0);
        return &doorobjlist[index];
    }

    return NULL;
}

Uint16 door_object_to_ui16(const doorobj_t* door_object)
{
    ptrdiff_t index = door_object - doorobjlist;

    if (index >= 0) {
        ptrdiff_t offset = DOOROBJLIST_OFFSET + (index * OLD_DOOROBJ_T_SIZE);
        assert(offset <= 0xFFFF);
        return static_cast<Uint16>(offset);
    }

    return 0;
}
