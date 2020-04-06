#include "HelloWorldScene.h"
#include <cstdio>

using namespace std;

USING_NS_CC;

Vec2 deathHeartPoint = Vec2(400, 200);


Scene *HelloWorld::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

bool HelloWorld::init() {
    if (!Layer::init()) {
        return false;
    }

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    fly = Sprite::create("frame-1.png");
    fly->setPosition(Vec2(200, 200));
    auto animation = Animation::create();
    animation->addSpriteFrameWithFile("frame-1.png");
    animation->addSpriteFrameWithFile("frame-2.png");
    animation->setDelayPerUnit(0.2f);
    animation->setLoops(-1);

    // Dead sprite
    auto deadHeart = Sprite::create("deadHeart.png");
    deadHeart->setPosition(deathHeartPoint);
    this->addChild(deadHeart);

    animate = Animate::create(animation);
    /*fly->runAction(RepeatForever::create(animate));*/

    //fly->runAction(animate);
    this->addChild(fly);
    animate->retain();


    this->scheduleUpdate();


    auto deadListener = EventListenerCustom::create("flyDie", [=](EventCustom *event) {
        std::string str("Custom event 1 received, ");
        fly->setPosition(Vec2(100, 200));
    });

    _eventDispatcher->addEventListenerWithFixedPriority(deadListener, 1);

    return true;
}

void HelloWorld::update(float dt) {

    if (go_r) fly->setPosition(Vec2(fly->getPosition().x + 5, fly->getPosition().y));
    if (go_l) fly->setPosition(Vec2(fly->getPosition().x - 5, fly->getPosition().y));
    if (go_d) fly->setPosition(Vec2(fly->getPosition().x, fly->getPosition().y - 5));
    if (go_u) fly->setPosition(Vec2(fly->getPosition().x, fly->getPosition().y + 5));
    if (countOfLives == 0) {
        EventCustom event("flyDie");
        _eventDispatcher->dispatchEvent(&event);
    }

    // Зменшення кількості життя якщо перхонаж находить на серце
    Vec2 flyPoint = fly->getPosition();
    float x = flyPoint.x;
    float y = flyPoint.y;

    if (x == deathHeartPoint.x && y == deathHeartPoint.y) {
        countOfLives--;
    }
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
    if ((int) keyCode == 27) {
        go_r = false;
        fly->stopAction(animate);
    }

    if ((int) keyCode == 29) {
        go_d = false;
        fly->stopAction(animate);
    }
    if ((int) keyCode == 26) {
        go_l = false;
        fly->stopAction(animate);
    }
    if ((int) keyCode == 28) {
        go_u = false;
        fly->stopAction(animate);
    }
}


void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
    if ((int) keyCode == 27) {
        go_r = true;
        fly->runAction(animate);
    }
    if ((int) keyCode == 29) {
        go_d = true;
        fly->runAction(animate);
    }
    if ((int) keyCode == 26) {
        go_l = true;
        fly->runAction(animate);
    }
    if ((int) keyCode == 28) {
        go_u = true;
        fly->runAction(animate);
    }
}

