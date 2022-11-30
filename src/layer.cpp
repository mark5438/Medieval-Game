#include "layer.hpp"

Layer::Layer(rapidxml::xml_node<> *xml_node)
{
    this->id = atoi(xml_node->first_attribute("id", 2)->value());
    this->width = atoi(xml_node->first_attribute("width", 5)->value());
    this->height = atoi(xml_node->first_attribute("height", 6)->value());

    rapidxml::xml_node<> *chunk = xml_node->first_node("data", 4)->first_node("chunk", 5);

    while (chunk)
    {


        chunk = chunk->next_sibling("chunk");
    }
}