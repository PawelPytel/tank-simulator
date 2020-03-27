#include "tank.h"
#include "modifiers.h"

using namespace glm;
Tank::Tank()
{
    body_angle=0;
    total_angle=0;
    turret_angle=0;
    gun_angle=0;
    wheels_angle=0;
    M=mat4(1);
}
mat4 Tank::get_M()
{
    return M;
}
mat4 Tank::get_V()
{
    return V;
}
vec4 Tank::get_cam_and_count_V()
{
    vec4 position=M*vec4(0,0,0,1);
    vec4 cam=vec4(position.x,position.y,position.z,1)+vec4(sin(total_angle)*15.0f,8.0f,cos(total_angle)*-15.0f,0);
    V=lookAt(vec3(cam.x,cam.y,cam.z),
             vec3(position.x,position.y+3,position.z),
             vec3(0,1,0));
    return cam;
}

void Tank::reset()
{
    angle=0;
    speed=0;
    fire_speed=0;
}
void Tank::set_angle(Mods mods)
{
    angle+=mods.lr*glfwGetTime();
    body_angle-=angle;
}
void Tank::set_turret_angle(Mods mods)
{
    turret_angle+=mods.turret_lr*glfwGetTime();
    total_angle=body_angle-turret_angle;
}
void Tank::set_gun_angle(Mods mods)
{
    if(gun_angle>0.03)
    {
        if(mods.up<=0)
        {
            gun_angle+=mods.up*glfwGetTime();
        }
    }
    else if (gun_angle<-0.3)
    {
        if(mods.up>=0)
        {
            gun_angle+=mods.up*glfwGetTime();
        }
    }
    else
        gun_angle+=mods.up*glfwGetTime();
}
void Tank::set_ls(Mods mods)
{
    if(mods.frd==0 && mods.lr>0)
        ls=-1;
    else
        ls=1;
}
void Tank::set_rs(Mods mods)
{
    if(mods.frd==0 && mods.lr<0)
        rs=-1;
    else
        rs=1;
}
void Tank::set_wheels_angle(Mods mods)
{
    if(mods.frd!=0 || mods.lr!=0)
    {
        wheels_angle+=mods.whl*glfwGetTime();
    }
}
void Tank::set_fire_speed(Mods mods)
{
    if (mods.fire==BULLET_SPEED)
    {
        fire_speed+=mods.fire*glfwGetTime();
    }
    else if(mods.fire==0)
        fire_speed=0;
}
void Tank::set_speed(Mods mods)
{
    speed+=mods.frd*glfwGetTime();
}
void Tank::move_body(Surr surr)
{
    M=rotate(M,angle,vec3(0,1,0));
    mat4 tmp=translate(M,vec3(0,0,speed));
    vec4 position=tmp*vec4(0,0,0,1);
    if(position.z>=surr.positions[3].z&&position.x<=surr.positions[2].x&&position.z<=surr.positions[1].z&&position.x>=surr.positions[0].x)
        M=tmp;
}
mat4 Tank::from_body_to_turret()
{
    mat4 tmp=rotate(M,turret_angle,vec3(0,1,0));;
    tmp=translate(tmp,vec3(0,0.7f,0.7f));
    return tmp;
}
mat4 Tank::from_turret_to_gun(mat4 tmp)
{
    mat4 tmp2=translate(tmp,vec3(0,0,1));
    tmp2=rotate(tmp2,gun_angle,vec3(1,0,0));
    return tmp2;
}
mat4 Tank::get_BM()
{
    return BM;
}
void Tank::fire(Surr &surr,Mods &mods,mat4 tmp)
{
    vec4 bull_pos=BM*vec4(0,0,0,1);
    if(bull_pos.z>=surr.positions[0].z&&mods.fire==BULLET_SPEED)
    {
        mods.fire=-1;
        while(abs(bull_pos.z-surr.positions[0].z)>0.05)
        {
            BM=translate(BM,vec3(0,0,-0.01));
            bull_pos=BM*vec4(0,0,0,1);
        }
        surr.holes[0].push_back(BM);

    }
    if(bull_pos.x>=surr.positions[1].x&&mods.fire==BULLET_SPEED)
    {
        mods.fire=-1;
        while(abs(bull_pos.x-surr.positions[1].x)>0.05)
        {
            BM=translate(BM,vec3(0,0,-0.01));
            bull_pos=BM*vec4(0,0,0,1);
        }
        surr.holes[1].push_back(BM);
    }
    if(bull_pos.z<=surr.positions[2].z&&mods.fire==BULLET_SPEED)
    {
        mods.fire=-1;
        while(abs(bull_pos.z-surr.positions[2].z)>0.05)
        {
            BM=translate(BM,vec3(0,0,-0.01));
            bull_pos=BM*vec4(0,0,0,1);
        }
        surr.holes[2].push_back(BM);
    }

    if(bull_pos.x<=surr.positions[3].x&&mods.fire==BULLET_SPEED)
    {
        mods.fire=-1;
        while(abs(bull_pos.x-surr.positions[3].x)>0.05)
        {
            BM=translate(BM,vec3(0,0,-0.01));
            bull_pos=BM*vec4(0,0,0,1);
        }
        surr.holes[3].push_back(BM);
    }
    if(mods.fire==20)
    {
        BM=translate(tmp,vec3(0,0,fire_speed));
        mods.fire=BULLET_SPEED;
    }
    else if (mods.fire==BULLET_SPEED)
    {
        BM=translate(BM,vec3(0,0,fire_speed));
    }
}
mat4 Tank::get_left_small_wheels(int j)
{
    mat4 tmp=M;
    tmp=glm::translate(tmp,vec3(1.5f,-0.3f,2.8f));
    tmp=translate(tmp,vec3(0,0,-5.6f*j));
    return tmp;
}
mat4 Tank::get_right_small_wheels(int j)
{
    mat4 tmp=M;
    tmp=rotate(tmp,PI,vec3(0,1,0));
    tmp=glm::translate(tmp,vec3(1.5f,-0.3f,2.8f));
    tmp=translate(tmp,vec3(0,0,-5.6f*j));
    return tmp;
}
mat4 Tank::get_track(int j)
{
    mat4 tmp=M;
    tmp=translate(tmp,vec3(-2.8*j,0,0));
    return tmp;
}
mat4 Tank::get_left_wheels(mat4 tmp,int i)
{
    mat4 tmp2=glm::translate(tmp,vec3(0.0f,-0.25f,0.8f*i));
    tmp2=rotate(tmp2,ls*wheels_angle,vec3(1,0,0));
    return tmp2;
}
mat4 Tank::get_right_wheels(mat4 tmp,int i)
{
    mat4 tmp2=glm::translate(tmp,vec3(0.0f,-0.25f,0.8f*i));
    tmp2=rotate(tmp2,-rs*wheels_angle,vec3(1,0,0));
    return tmp2;
}
mat4 Tank::rotate_left_wheels(mat4 tmp)
{
    return rotate(tmp,ls*wheels_angle,vec3(1,0,0));
}
mat4 Tank::rotate_right_wheels(mat4 tmp)
{
    return rotate(tmp,-rs*wheels_angle,vec3(1,0,0));
}
