#include "animation.hpp"

int get_animation_sprite_id_now(t_animation * animation)
{
    int animation_time = get_elapsed_time() % animation->duration;
    int counted_time = 0;
    for (std::list<t_frame>::iterator it = animation->frames.begin(); it != animation->frames.end(); ++it)
    {
        counted_time += it.operator*().duration;
        if (counted_time >= animation_time)
        {
            it.operator*().tile_id;
        }
    }
    return NULL;
}