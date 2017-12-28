//
// Created by vld on 12/28/17.
//

#ifndef TANKS_ENEMY_H
#define TANKS_ENEMY_H


class ENEMY {

public:
    void Set(Texture &image, int x, int y);
    void Update (float time);
    void Collision ();

private:
    float dx, dy;
    FloatRect rect;
    Sprite sprite;
    float currentFrame;
    bool life;
};
#endif //TANKS_ENEMY_H
