#include <SFML/Graphics.hpp>

#include "mouse_wheel/mouse_wheel.hpp"

void camera_check_hid_events();

int get_camera_x();
int get_camera_y();
float get_camera_zoom();

int move_camera_x(int);
int move_camera_y(int);
float change_camera_zoom(float);

void set_camera_x(int);
void set_camera_y(int);
void set_camera_zoom(float);