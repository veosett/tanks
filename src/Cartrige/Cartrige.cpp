#include "Cartrige.h"

Cartrige::Cartrige (Texture &image, int x, int y) {
  sprite.setTexture(image);
  rect = FloatRect(16 * 16, 16 * 16, x, y);

  dx = dy = 0.1;
  currentFrame = 0;
}

void Cartrige::Collision (int num) {
  for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
    for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++) {
      if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') ||
          (TileMap[i][j] == 'r') || (TileMap[i][j] == 't')) {
        if (dy > 0 && num == 1) {
          rect.top = i * 16 - rect.height;
          dy = 0;
          onGround = true;
        }
        if (dy < 0 && num == 1) {
          rect.top = i * 16 + 16;
          dy = 0;
        }
        if (dx > 0 && num == 0) { rect.left = j * 16 - rect.width; }
        if (dx < 0 && num == 0) { rect.left = j * 16 + 16; }
      }

      if (TileMap[i][j] == 'c') {
        // TileMap[i][j]=' ';
      }
    }
}

void Cartrige::Update (float time, string status)
{
  if (dx != 0)
  {
    rect.left += dx * time;
    dy = 0;
  } else if (dy != 0)
  {
    rect.top += dy * time;
  }
  Collision(0);

//        if (!onGround) {
//            dy = dy + 0.0005 * time;
//        }

//        rect.top += dy * time;
//        onGround = false;
  Collision(1);

  currentFrame += time * 0.005;
  if (currentFrame > 2)
  {
    currentFrame -= 2;
  }

  if (dx > 0)
  {
    sprite.setTextureRect(IntRect(16 * 6 + 16 * int(currentFrame), 16 * 8, 16, 16));
  }
  if (dx < 0)
  {
    sprite.setTextureRect(IntRect(16 * 2 + 16 * int(currentFrame), 0, 16, 16));
  }
  if (dy < 0)
  {
    sprite.setTextureRect(IntRect(0 + 16 * int(currentFrame), 0, 16, 16));
  }
  if (dy > 0)
  {
    sprite.setTextureRect(IntRect(16 * 4 + 16 * int(currentFrame), 0, 16, 16));
  }

  sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

  dx = dy = 0;
}
