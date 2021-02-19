#include "objectsGraphics.h"

class object
{
private:
    ObjectType::OBJECT_TYPES type;

    //these are actually thre [0][0] position of the matrix
    //,..should do smthng abt it
    float x, y, prev_x, prev_y;
    float velocity_x, velocity_y;
    int height, width;
    float strength; //damage/health
    static WINDOW *win;
    static int MAX_X, MAX_Y;
    ObjectGraphics *Obj;

public:
    object *f_link, *b_link;
    object(float, float, ObjectType::OBJECT_TYPES);
    ~object();
    void drawObject()
    {
        Obj->eraseObject(prev_y, prev_x, object::win);
        Obj->drawObject(y, x, object::win);
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
    bool move()
    {
        //add velocity*dt to both coords
        //check boundary conditions

        switch (type)
        {
        case ObjectType::SHIP_BASIC:
            prev_x = x;
            x += velocity_x;
            break;
        case ObjectType::SHIP_ENEMY_1:
            prev_x = x;
            x += velocity_x;
            break;
        case ObjectType::BULLET_1:
            prev_y = y;
            y += velocity_y;
            break;

        default:
            break;
        }

        //edge cases

        if (type < 3)
        {
            if (!(x - width / 2 > 0 && x + width / 2 < object::MAX_X))
            {
                revVelocity();
            }
        }
        else
        {
            if (!(y - height / 2 > 0 && y + height / 2 < object::MAX_Y))
            {
                return true; //bullets going out of view will be deleted
            }
        }

        return false;
    }
    void revVelocity()
    {
        velocity_x *= -1;
    }
    void changeDir(short dir)
    {
        if (type != ObjectType::SHIP_BASIC)
            return;
        else if (dir * velocity_x < 0)
        {
            revVelocity();
        }
    }
    void deleted()
    {
        Obj->eraseObject(prev_y, prev_x, object::win);
        prev_y = y, prev_x = x;
        Obj->eraseObject(prev_y, prev_x, object::win);
    }
    static void set_statics(WINDOW *w)
    {
        win = w;
        MAX_X = getmaxx(win);
        MAX_Y = getmaxy(win);
    }
    void interact(object *ob1, object *ob2)
    {
    }
};

WINDOW *object::win = nullptr;
int object::MAX_X = -1;
int object::MAX_Y = -1;

object::object(float xCord, float yCord, ObjectType::OBJECT_TYPES t) : f_link(nullptr), b_link(nullptr)
{

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
    case ObjectType::SHIP_ENEMY_1:
        velocity_x = 0.25;
        velocity_y = 0;
        strength = 10;
        Obj = &SHIP_ENEMY_1;
        break;
    case ObjectType::BULLET_1:
        velocity_x = 0;
        velocity_y = -1;
        strength = 10;
        Obj = &BULLET_1;
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
    void shoot(object *ship)
    {
        float x = ship->getx(), y = ship->gety();
        newObject(ObjectType::BULLET_1, x, y);
    }
    ~ObjectList();
};

ObjectList::ObjectList(WINDOW *window) : front(nullptr), back(nullptr), drawWindow(window)
{
    object::set_statics(window);
}

ObjectList::~ObjectList()
{
    clearList();
}

void ObjectList::clearList()
{

    object *temp = nullptr;
    for (object *i = front; i; i = i->f_link)
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

    newObj = new object(x, y, type);

    if (front == nullptr)
    {
        front = back = newObj;
    }
    else
    {
        back->f_link = newObj;
        newObj->b_link = back;
    }
    back = newObj;

    if (type == ObjectType::SHIP_BASIC) //replace with player
        player = newObj;
}

object *ObjectList::deleteObject(object *ptr)
{
    //will implement after 1 ship trial
    ptr->deleted();
    object *temp;
    if (ptr == front)
    {
        front = front->f_link;
        (ptr->f_link)->b_link = NULL;
        temp = front;
    }
    else
    {
        (ptr->b_link)->f_link = ptr->f_link;
        if (ptr->f_link)
            (ptr->f_link)->b_link = ptr->b_link;
        else
            temp = ptr->b_link, temp->f_link = NULL, back = temp;

        temp = ptr->b_link;
    }
    delete ptr;
    return temp;
}

void ObjectList::updatePositions()
{
    for (object *i = front; i; i = i->f_link)
        if (i->move())
            i = deleteObject(i);
}

void ObjectList::drawObjects()
{
    for (object *i = front; i; i = i->f_link)
        i->drawObject();
}