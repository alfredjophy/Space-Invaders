#include "objects.hpp"
                                                                       
ObjectGraphics _SHIP_BASIC(OBJECT_TYPES::SHIP_BASIC);
ObjectGraphics _SHIP_ENEMY_1(OBJECT_TYPES::SHIP_ENEMY_1);
ObjectGraphics _BULLET_1(OBJECT_TYPES::BULLET_1);

//object method definitions
ObjectList::object::object(float xCord, float yCord, OBJECT_TYPES t) : f_link(nullptr), b_link(nullptr)
{
        //initialize object graphic and attributes
        type = t;
        x = xCord, y = yCord;
        prev_x = xCord, prev_y = yCord;

        switch (type)
        {
                case SHIP_BASIC:
                        velocity_x = 1;
                        velocity_y = 0;
                        strength = 10;
                        Obj = &_SHIP_BASIC;
                        break;
                case SHIP_ENEMY_1:
                        velocity_x = 0.25;
                        velocity_y = 0;
                        strength = 10;
                        Obj = &_SHIP_ENEMY_1;
                        break;
                case BULLET_1:
                        velocity_x = 0;
                        velocity_y = -1;
                        strength = 10;
                        Obj = &_BULLET_1;
                        break;

                default:
                        Obj = nullptr;
                        break;
        }

        //get dimensions
        Obj->getDimensions(height, width);
}

ObjectList::object::~object()
{
        //clear memory
        f_link = b_link = nullptr;
        Obj = nullptr;
}

void ObjectList::object::drawObject()
{
        Obj->eraseObject(prev_y, prev_x, object::win);
        Obj->drawObject(y, x, object::win);
}
void ObjectList::object::getDimensions(int &h, int &w)
{
        h = height;
        w = width;
}

float ObjectList::object::getStrength(){
        return strength;
}
float ObjectList::object::getx()
{
        return x;
}
float ObjectList::object::gety()
{
        return y;
}
float ObjectList::object::getPrev_x()
{
        return prev_x;
}
float ObjectList::object::getPrev_y()
{
        return prev_y;
}
float ObjectList::object::getVelocity_x()
{
        return velocity_x;
}
float ObjectList::object::getVelocity_y()
{
        return velocity_y;
}
OBJECT_TYPES ObjectList::object::getType()
{
        return type;
}
bool ObjectList::object::move()
{
        //add velocity*dt to both coords
        //check boundary conditions

        switch (type)
        {
                case SHIP_BASIC:
                        prev_x = x;
                        x += velocity_x;
                        break;
                case SHIP_ENEMY_1:
                        prev_x = x;
                        x += velocity_x;
                        break;
                case BULLET_1:
                        prev_y = y;
                        y += velocity_y;
                        break;

                default:
                        break;
        }

        //edge collison

        if (type < 3)
        {
                if (!(x - width / 2 > 0 && x + width / 2< object::MAX_X-1))
                {
                        revVelocity();
                        //std::cout<<x<<" "<<y;
                        int i=0;

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
void ObjectList::object::revVelocity()
{
        velocity_x *= -1;
}
void ObjectList::object::changeDir(short dir)
{
        if (type != SHIP_BASIC)
                return;
        else if (dir * velocity_x < 0)
        {
                revVelocity();
        }
}
void ObjectList::object::deleted()
{
        Obj->eraseObject(prev_y, prev_x, object::win);
        prev_y = y, prev_x = x;
        Obj->eraseObject(prev_y, prev_x, object::win);
}
void ObjectList::object::interact(object *obj)
{
        //check coordinates and dimensions for collisions

        float x1 = this->x;
        float y1 = this->y;
        int h1 = this->height;
        int w1 = this->width;
        float d1 = sqrt(h1 * h1 + w1 * w1);
        float x2 = obj->getx();
        float y2 = obj->gety();
        int w2, h2;
        obj->getDimensions(h2, w2);
        float d2 = sqrt(h2 * h2 + w2 * w2);

        //if distance between centres < sum of diagonals
        if(sqrt(pow(x2-x1,2)+pow(y2-y1,2))<=d1/2+d2/2 )
        {
                //std::cout<<"coll";
                //this->revVelocity();
                obj->revVelocity();
        }
}


//objectList method definitions

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

void ObjectList::newObject(OBJECT_TYPES type, float x, float y)
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

        if (type == SHIP_BASIC) //replace with player
                player = newObj;
}

ObjectList::object *ObjectList::deleteObject(ObjectList::object *ptr)
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
        {
                if (i->move())
                {   i = deleteObject(i);
                        continue;
                }
                //}
                //interaction is needed
                //for (object *i = front; i; i = i->f_link)
                for (object *j = front; j; j = j->f_link)
                        if(i!=j)i->interact(j);
}       
}

void ObjectList::drawObjects()
{
        for (object *i = front; i; i = i->f_link)
                i->drawObject();
}
