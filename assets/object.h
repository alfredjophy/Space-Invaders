#include "objectsGraphics.h"

class object
{
private:
    float x, y, prev_x, prev_y;
    float velocity_x, velocity_y;
    int height, width;
    float strength; //damage/health

    ObjectGraphics *Obj;

public:
    object *f_link, *b_link;
    object(float,float,int);
    ~object();

    void drawObject(WINDOW *win=stdsrc)
    {
        Obj->eraseObject(prev_y, prev_x, win);
        Obj->drawObject(y, x,win);
    }
    void getDimensions(char &h, char &w)
    {
        Obj->getDimensions(h, w);
    }
    float getStrength()
    {
        return strength;
    }
    float getx()
    {
        return x;
    }
    float gety()
    {
        return y;
    }
    float getPrev_x()
    {
        return prev_x;
    }
    float getPrev_y()
    {
        return prev_y;
    }
    void move()
    {
        //add velocity*dt to both coords
        //check boundary conditions
    }
    void revVelocity()
    {
        velocity_x *= -1;
    }
};

object::object(float x, float y, int type)
{
    //initialize object graphic
    //get dimensions
    //assign rest of attributes
}

object::~object()
{
    //clear memory
    f_link = b_link = nullptr;
    Obj = nullptr;
}

class ObjectList
{
private:
    /* data */
public:
    ObjectList(/* args */);
    ~ObjectList();
};

ObjectList::ObjectList(/* args */)
{
}

ObjectList::~ObjectList()
{
}
