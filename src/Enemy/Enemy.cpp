#include "Enemy.h"

void Enemy::Collision ()
{
  for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
  {
    for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
    {
      if ((TileMap[i][j] == 'P') || (TileMap[i][j] == '0'))
      {
        if (dx > 0)
        {
          rect.left = j * 16 - rect.width;
          dx *= -1;
        } else if (dx < 0)
        {
          rect.left = j * 16 + 16;
          dx *= -1;
        }
      }
    }
  }
}

void Enemy::Set(Texture &image, int x, int y) {
  sprite.setTexture(image);
  rect = FloatRect(x, y, 16, 16);

  dx = 0.05;
  dy = 0;
  currentFrame = 0;
  life = true;
}

void Enemy::Update (float time) {
  rect.left += dx * time;

  Collision();

  currentFrame += time * 0.005;
  if (currentFrame > 2) {
    currentFrame -= 2;
  }

  if (dx > 0) {
    sprite.setTextureRect(IntRect(16 * 14 + 16 * int(currentFrame), 0, 16, 16));
  }
  if (dx < 0) {
    sprite.setTextureRect(IntRect(16 * 10 + 16 * int(currentFrame), 0, 16, 16));
  }
  if (dy < 0) {
    sprite.setTextureRect(IntRect(16 * 8 + 16 * int(currentFrame), 0, 16, 16));
  }
  if (dy > 0) {
    sprite.setTextureRect(IntRect(16 * 12 + 16 * int(currentFrame), 0, 16, 16));
  }

  if (!life) {
    sprite.setTextureRect(IntRect(0, 0, 16, 16));
  }

  sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

}

