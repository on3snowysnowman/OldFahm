#pragma once

#include "Script.h"
#include "../Components/TransformComponent.h"
#include "../Entity.h"

struct CameraTrack : public Script
{
    Entity* camera;

    CameraTrack(Entity* _camera)
    {
        name = "TrackCamera";
        camera = _camera;
    }

    Script* clone() override
    {
        return new CameraTrack(camera);
    }

    void update() override
    {
        TransformComponent* camera_t_comp = 
            camera->get_component<TransformComponent>();

        TransformComponent* entity_t_comp =
            entity->get_component<TransformComponent>();

        camera_t_comp->set_position(entity_t_comp->x_pos, 
            entity_t_comp->y_pos);
    }
};
