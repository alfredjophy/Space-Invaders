#ifndef OBJECTS_H
#define OBJECTS_H

#include "objectsGraphics.hpp"
#include "math_additional.hpp"

class ObjectList
{
        //object definition
        class object
        {
                private:
                        OBJECT_TYPES type;

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
                        object(float, float, OBJECT_TYPES);
                        ~object();
                        void drawObject();
                        void getDimensions(int &h, int &w);
                        float getStrength();
                        float getx();
                        float gety();
                        float getPrev_x();
                        float getPrev_y();
                        float getVelocity_x();
                        float getVelocity_y();
                        OBJECT_TYPES getType();
                        bool move();
                        void revVelocity();
                        void changeDir(short dir);
                        void interact(object *obj);
                        void deleted();
                        static void set_statics(WINDOW *w)
                        {
                                win = w;
                                MAX_X = getmaxx(win);
                                MAX_Y = getmaxy(win);
                        }

        };


        private:
        object *front, *back; //front will always point to player ie SHIP_BASIC
        WINDOW *drawWindow;

        public:
        object *player;
        ObjectList(WINDOW *);
        void newObject(OBJECT_TYPES, float, float);
        object *deleteObject(object *ptr);
        void updatePositions();
        void drawObjects();
        void clearList();
        void shoot(object *ship);
        ~ObjectList();
};

#endif
