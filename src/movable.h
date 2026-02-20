#pragma once

namespace game{

    class movable {
    public:
        virtual ~movable() = default;

        virtual void updateMovable(float dt) = 0;

    };

};


