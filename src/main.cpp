#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Player/Player.h"

float offsetX = 0, offsetY = 0;

const int H = 32;
const int W = 32;


String TileMap[H] = {
        "00000000000000000000000000000000",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "0                              0",
        "00000000000000000000000000000000",

};


int main () {

  RenderWindow window(VideoMode(512, 512), "Tanks C++");

  Texture tileSet;
  tileSet.loadFromFile("images/tanks.png");


  PLAYER Tank(tileSet);
  ENEMY enemy;
  enemy.set(tileSet, 1 * 16, 1 * 16);


  Sprite tile(tileSet);

  SoundBuffer buffer;
  buffer.loadFromFile("Jump.wav");
  Sound sound(buffer);

  Music music;
  if (!music.openFromFile("Tank_Theme.ogg")) {
    music.openFromFile("Tank_Theme.ogg");
  }

  music.play();

  Clock clock;

  while (window.isOpen()) {

    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();

    time = time / 1000;  // speed of game

    if (time > 20) {
      time = 20;
    }

    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
      }
    }

    if (Keyboard::isKeyPressed(Keyboard::Left)) {
      Tank.dx = -0.1;
    }

    if (Keyboard::isKeyPressed(Keyboard::Right)) {
      Tank.dx = 0.1;
    }

    if (Keyboard::isKeyPressed(Keyboard::Up)) {
//            if (Tank.onGround) {
//                Tank.dy = -0.27;
//                Tank.onGround = false;
//                sound.play();
//            }
      Tank.dy = -0.1;
    }

    if (Keyboard::isKeyPressed(Keyboard::Down)) {
      Tank.dy = 0.1;
    }

    Tank.update(time);
    enemy.update(time);

    if (Tank.rect.intersects(enemy.rect)) {
      if (enemy.life) {
        if (Tank.dy > 0) {
          enemy.dx = 0;
          Tank.dy = -0.2;
          enemy.life = false;
        } else {
          Tank.sprite.setColor(Color::Red);
        }
      }
    }

//        if (Tank.rect.left > 200) {
//            offsetX = Tank.rect.left - 200; //смещение
//        }

    window.clear(Color(0, 0, 0));

    for (int i = 0; i < H; i++)
      for (int j = 0; j < W; j++) {
        //if (TileMap[i][j] == 'P') tile.setTextureRect(IntRect(1, 1, 16, 16));
//
//                if (TileMap[i][j] == 'k') tile.setTextureRect(IntRect(143, 112, 16, 16));
//
//                if (TileMap[i][j] == 'c') tile.setTextureRect(IntRect(143 - 16, 112, 16, 16));
//
//                if (TileMap[i][j] == 't') tile.setTextureRect(IntRect(0, 47, 32, 95 - 47));
//
//                if (TileMap[i][j] == 'g') tile.setTextureRect(IntRect(0, 16 * 9 - 5, 3 * 16, 16 * 2 + 5));
//
//                if (TileMap[i][j] == 'G') tile.setTextureRect(IntRect(145, 222, 222 - 145, 255 - 222));
//
//                if (TileMap[i][j] == 'd') tile.setTextureRect(IntRect(0, 106, 74, 127 - 106));
//
//                if (TileMap[i][j] == 'w') tile.setTextureRect(IntRect(99, 224, 140 - 99, 255 - 224));
//
//                if (TileMap[i][j] == 'r') tile.setTextureRect(IntRect(143 - 32, 112, 16, 16));

        if (TileMap[i][j] == '0') tile.setTextureRect(IntRect(256, 16, 16, 16));

        if (TileMap[i][j] == ' ') continue;

        tile.setPosition(j * 16 - offsetX, i * 16 - offsetY);
        window.draw(tile);
      }


    window.draw(Tank.sprite);
    window.draw(enemy.sprite);

    window.display();
  }

  return 0;
}
