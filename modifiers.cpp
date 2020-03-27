#include "modifiers.h"

Mods::Mods()
{
    lr=0;
    turret_lr=0;
    frd=0;
    up=0;
    whl=0;
    fire=0;
}
float Mods::get_lr()
{
    return lr;
}
float Mods::get_turret_lr()
{
    return turret_lr;
}
float Mods::get_frd()
{
    return frd;
}
float Mods::get_up()
{
    return up;
}
float Mods::get_whl()
{
    return whl;
}
float Mods::get_fire()
{
    return fire;
}

void Mods::set_lr(float val)
{
    lr=val;
}
void Mods::set_turret_lr(float val)
{
    turret_lr=val;
}
void Mods::set_frd(float val)
{
    frd=val;
}
void Mods::set_up(float val)
{
    up=val;
}
void Mods::set_whl(float val)
{
    whl=val;
}
void Mods::set_fire(float val)
{
    fire=val;
}

