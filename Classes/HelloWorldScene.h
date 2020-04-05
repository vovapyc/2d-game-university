#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer {
public:
    static cocos2d::Scene *createScene();

    cocos2d::Sprite *fly;
    cocos2d::Animate *animate;

    virtual bool init();

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

    virtual void update(float dt);

    CREATE_FUNC(HelloWorld);

    bool go_r = false;
    bool go_l = false;
    bool go_u = false;
    bool go_d = false;


};

#endif // __HELLOWORLD_SCENE_H__