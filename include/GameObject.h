#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
    private:
        int x, y;
    public:
        GameObject();
        ~GameObject();
        int getX();
        int getY();
        virtual void setX(int x);
        virtual void setY(int y);
        virtual void setPos(int nx, int ny);
};


#endif
