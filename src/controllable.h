#pragma once

namespace game {

    class controllable {
      public:
        virtual void getKeyBoardInput() = 0;
        virtual void getMouseInput() = 0;

        virtual ~controllable() = default;
    };

};


