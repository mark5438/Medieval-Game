#include "layer.hpp"

// TODO: Get lowest x and y values from chunks.
// User in Layer::get_texture_at function to check
// if the given coordinates are within the layer

Layer::Layer(rapidxml::xml_node<> *xml_node)
{
    this->id = atoi(xml_node->first_attribute("id", 2)->value());
    this->width = atoi(xml_node->first_attribute("width", 5)->value());
    this->height = atoi(xml_node->first_attribute("height", 6)->value());

    rapidxml::xml_node<> *chunk = xml_node->first_node("data", 4)->first_node("chunk", 5);

    while (chunk)
    {
        chunks.push_back(new Chunk(chunk));
        chunk = chunk->next_sibling("chunk");
    }
}

int Layer::get_texture_at(int x, int y)
{
    for (std::list<Chunk*>::iterator it = this->chunks.begin(); it != this->chunks.end(); ++it) {
        int texture = it.operator*()->get_texture_at(x, y);
        if (texture >= 0)
            return texture;
    }
    return 0;
}