#include "surrounding.h"

Surr::Surr()
{
    mat4 tmp,tmp2;
    vec4 tmp_pos;
    tmp=translate(mat4(1),vec3(-50,0,70))*scale(mat4(1),vec3(4,4,4));
    for(int k=1; k<3; k++)
    {
        for(int j=0; j<4; j++)
        {
            for(int i=0; i<7; i++)
            {
                tmp2=translate(tmp,vec3(4*i,0,0));
                matrices.push_back(tmp2);
                if(i==0&&k==1)
                {
                    tmp_pos=tmp2*vec4(0,0,0,1);
                    positions.push_back(tmp_pos);
                }

            }
            tmp=rotate(tmp2,PI/2,vec3(0,1,0));
            tmp=translate(tmp,vec3(2,0,2));
        }
        tmp=translate(tmp,vec3(0,4,0));
    }
    tmp=translate(mat4(1),vec3(0,-1.0f,0.0f))*scale(mat4(1),vec3(5,5,5));
    matrices.push_back(tmp);
}
void Surr::set_first()
{
    first=(last+1)%4;
}
void Surr::update_outside(vec4 cam)
{
    last=3;
    for(int i=0; i<4; i++)
        outside[i]=0;
    if(cam.z>positions[0].z)
    {
        last=0;
        outside[0]=1;
    }
    if(cam.x>positions[1].x)
    {
        last=1;
        outside[1]=1;
    }
    if(cam.z<positions[2].z)
    {
        last=2;
        outside[2]=1;
    }

    if(cam.x<positions[3].x)
    {
        last=3;
        outside[3]=1;
    }
    if (last==3&&outside[3]==1&&outside[0]==1)
        last=0;
}
bool Surr::check_transparency(int j)
{

    return          (j==3&&outside[last]==1)
                    ||(j==0&&outside[last]==1&&outside[(last+1)%4]==1)
                    ||(j==2&&outside[last]==1&&outside[(last-1)%4]==1)
                    ||(j==2&&outside[3]==1&&outside[0]==1);
}
void Surr::set_wallT(float val)
{
    wallT=val;
}
mat4 Surr::get_next_wall(int i, int j, int k)
{
    return matrices[k*4*7+(first+j)%4*7+i];
}
mat4 Surr::get_plane()
{
    return matrices.back();
}
int Surr::get_holes_count(int j)
{
    return holes[(first+j)%4].size();
}
mat4 Surr::get_next_hole(int i, int j)
{
    return holes[(j+first)%4][i];
}
float Surr::get_wallT()
{
    return wallT;
}
