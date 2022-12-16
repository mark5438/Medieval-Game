#include "animation.hpp"

Frame::Frame(int tileid, int duration)
{
    this->tile_id = tileid;
    this->duration = duration;
}

Animation::Animation(int tileid, rapidxml::xml_node<> * node)
{
    this->tile_id = tileid;
    for (rapidxml::xml_node<> *frame_node = node->first_node("frame"); frame_node; frame_node = frame_node->next_sibling("frame"))
    {
        int tile_id = atoi(frame_node->first_attribute("tileid")->value());
        int duration = atoi(frame_node->first_attribute("duration")->value());
        this->duration += duration;
        this->frames.push_back(new Frame(tile_id, duration));
    }
}

int Animation::get_animation_sprite_id_now()
{
    int animation_time = get_elapsed_time() % this->duration;
    int counted_time = 0;
    for (std::list<Frame*>::iterator it = this->frames.begin(); it != this->frames.end(); ++it)
    {
        counted_time += it.operator*()->get_duration();
        if (counted_time >= animation_time)
        {
            it.operator*()->get_tile_id();
        }
    }
    return NULL;
}