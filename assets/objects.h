#include "objectsGraphics.h"

class object
{
private:
    ObjectType::OBJECT_TYPES type;
    float x, y, prev_x, prev_y;
    float velocity_x, velocity_y;
    int height, width;
    float strength; //damage/health
    WINDOW *win;

    ObjectGraphics *Obj;

public:
    object *f_link, *b_link;
    object(float, float, ObjectType::OBJECT_TYPES, WINDOW *w);
    ~object();

    void drawObject()
    {
        Obj->eraseObject(prev_y, prev_x, win);
        Obj->drawObject(y, x, win);
    }
    void getDimensions(int &h, int &w)
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
    float getVelocity_x()
    {
        return velocity_x;
    }
    float getVelocity_y()
    {
        return velocity_y;
    }
    ObjectType::OBJECT_TYPES getType()
    {
        return type;
    }
    void move()
    {
        //add velocity*dt to both coords
        //check boundary conditions

        switch (type)
        {
        case ObjectType::SHIP_BASIC:
            prev_x = x;
            x += velocity_x;
            break;

        default:
            break;
        }
    }
    void revVelocity()
    {
        velocity_x *= -1;
    }
    void deleted()
    {
        prev_y = y, prev_x = x;
        Obj->eraseObject(prev_y, prev_x, win);
    }
};

object::object(float xCord, float yCord, ObjectType::OBJECT_TYPES t, WINDOW *w) : f_link(nullptr), b_link(nullptr)
{
    win = w;
    //initialize object graphic and attributes
    type = t;
    x = xCord, y = yCord;
    prev_x = xCord, prev_y = yCord;

    switch (type)
    {
    case ObjectType::SHIP_BASIC:
        velocity_x = 1;
        velocity_y = 0;
        strength = 10;
        Obj = &SHIP_BASIC;
        break;

    default:
        Obj = nullptr;
        break;
    }

    //get dimensions
    Obj->getDimensions(height, width);
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
    object *front, *back; //front will always point to player ie SHIP_BASIC
    WINDOW *drawWindow;

public:
    object *player;
    ObjectList(WINDOW *);
    void newObject(ObjectType::OBJECT_TYPES, float, float);
    object *deleteObject(object *ptr);
    void updatePositions();
    void drawObjects();
    void clearList();
    ~ObjectList();
};

ObjectList::ObjectList(WINDOW *window) : front(nullptr), back(nullptr), drawWindow(window)
{
}

ObjectList::~ObjectList()
{
    clearList();
}

void ObjectList::clearList()
{

    object *temp = nullptr;
    for (object *i = front; i; front = front->f_link)
    {
        delete temp;
        temp = i;
    }
    delete temp;
    //JUST TO MAKE SURE ,lol
    // delete front, delete back;
    front = back = player = nullptr;
}

void ObjectList::newObject(ObjectType::OBJECT_TYPES type, float x, float y)
{
    object *newObj;

    newObj = new object(x, y, type, drawWindow);

    if (front == nullptr)
        front = back = newObj;

    back->f_link = newObj;
    newObj->b_link = back;

    back = newObj;

    if (type == ObjectType::SHIP_BASIC) //replace with player
        player = newObj;
}

object *ObjectList::deleteObject(object *ptr)
{
    //will implemet after 1 ship trial
    return nullptr;
}

void ObjectList::updatePositions()
{
    for (object *i = front; i; front = front->f_link)
        i->move();
}

void ObjectList::drawObjects()
{
    for (object *i = front; i; front = front->f_link)
        i->drawObject();
}