#pragma once

#include <nlohmann/json.hpp>

#include "Entity.h"

class EntitySerializer
{

public:

    static nlohmann::json serialize_entity(Entity* e);

private:

};
