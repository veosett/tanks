#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;
using namespace std;


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


class PLAYER {

public:

    float dx, dy;
    FloatRect rect;
    bool onGround;
    Sprite sprite;
    float currentFrame;

    PLAYER(Texture &image) {
        sprite.setTexture(image);
        rect = FloatRect(16 * 16, 16 * 16, 16, 16);

        dx = dy = 0.1;
        currentFrame = 0;
    }


    void update(float time) {
        if (dx != 0) {
            rect.left += dx * time;
            dy = 0;
        }
        else if (dy != 0) {
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
        if (currentFrame > 3) {
            currentFrame -= 3;
        }

        if (dx > 0) {
            //sprite.setTextureRect(IntRect(0 + int(currentFrame) * 7, 16 * 6, 16, -16));
            sprite.setTextureRect(IntRect(16 * 7, 0, 16, 16));
        }
        if (dx < 0) {
            sprite.setTextureRect(IntRect(16 * 3, 0, 16, 16));
        }
        if (dy < 0) {

            sprite.setTextureRect(IntRect(0, 0, 16, 16));
        }
        if (dy > 0) {
            sprite.setTextureRect(IntRect(16 * 5, 0, 16, 16));
        }

        sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

        dx = dy = 0;
    }


    void Collision(int num) {

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

};


class ENEMY {

public:
    float dx, dy;
    FloatRect rect;
    Sprite sprite;
    float currentFrame;
    bool life;


    void set(Texture &image, int x, int y) {
        sprite.setTexture(image);
        rect = FloatRect(x, y, 16, 16);

        dx = 0.05;
        currentFrame = 0;
        life = true;
    }

    void update(float time) {
        rect.left += dx * time;

        Collision();

        currentFrame += time * 0.005;
        if (currentFrame > 2) {
            currentFrame -= 2;
        }

        sprite.setTextureRect(IntRect(16 * 9, 0, 16, 16));
        if (!life) {
            sprite.setTextureRect(IntRect(0, 0, 16, 16));
        }

        sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

    }


    void Collision() {

        for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++) {
            for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++) {
                if ((TileMap[i][j] == 'P') || (TileMap[i][j] == '0')) {
                    if (dx > 0) {
                        rect.left = j * 16 - rect.width;
                        dx *= -1;
                    }
                    else if (dx < 0) {
                        rect.left = j * 16 + 16;
                        dx *= -1;
                    }
                }
            }
        }
    }

};


int main() {

    RenderWindow window(VideoMode(512, 512), "Tanks C++");

    Texture tileSet;
    tileSet.loadFromFile("tanks.png");


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

        time = time / 1000;  // здесь регулируем скорость игры

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
                }
                else {
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
