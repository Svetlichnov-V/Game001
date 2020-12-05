#pragma once
#include "Manager.h"

void drawManager(Camera* camera, Storage* storage, float dt)
{
    Iterator iter(storage);
    while (true)
    {
        GameObject& gameObject = iter.stepIteration();
        if (gameObject.name == "NULL")
        {
            break;
        }
        gameObject.draw(camera);
        gameObject.animation(dt);
    }

}