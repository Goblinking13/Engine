#pragma once
#include <string>


namespace game{
    class texture {
        unsigned int tex_;
        int width_, height_, numberOfChannels_;


        public:
          texture(const char* path);
          unsigned int getTexture() const;
          int getWidth() const;
          int getHeight() const;
          void bind() const;
          std::string path;
          std::string type;


    };

};


