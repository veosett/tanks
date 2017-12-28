#ifndef TANKS_PLAYER_H
#define TANKS_PLAYER_H

#define SIZE_OF_TILE 16

class Player {
public:
    void Collision (int num);
    void Update (float time);
private:
    float dx, dy;
    FloatRect rect;
    bool onGround;
    Sprite sprite;
    float currentFrame;

    Player(Texture &image) {
      sprite.setTexture(image);
      rect = FloatRect(16 * 16, 16 * 16, 16, 16);

      dx = dy = 0.1;
      currentFrame = 0;
    }






};


#endif //TANKS_PLAYER_H
