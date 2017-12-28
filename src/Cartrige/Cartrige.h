#ifndef TANKS_CARTRIGE_H
#define TANKS_CARTRIGE_H

class Cartrige
{
public:
    void Collision (int num);
    Cartrige (Texture &image, int x, int y);
    void Update (float time, string status);

private:
    double dx;
    double dy;
    FloatRect rect;
    bool onGround;
    Sprite sprite;
    double currentFrame;
};

#endif //TANKS_CARTRIGE_H
