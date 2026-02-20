#pragma once

namespace game {

    class renderable {
          public:
            virtual void draw() = 0;
            virtual ~renderable() = default;
    };

};
