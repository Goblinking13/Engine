#include "pointCloud.h"

#include <iostream>
#include <ostream>


namespace game{

    pointCloud::pointCloud(shader* sh, size_t maxPoints){
        shader_ = sh;
        maxPoints_ = maxPoints;

        points_.resize(maxPoints);

        glGenVertexArrays(1, &VAO_);
        glBindVertexArray(VAO_);
        glGenBuffers(1, &VBO_);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        //also try GL_STREAM_DRAW
        glBufferData(GL_ARRAY_BUFFER, maxPoints_*sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);


    }


    void pointCloud::addPoint(const glm::vec3& p) {

        points_[head_] = p;


        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        glBufferSubData(GL_ARRAY_BUFFER, head_ * sizeof(glm::vec3), sizeof(glm::vec3), &p);



        head_++;
        if (head_ >= maxPoints_) { head_ = 0; filed_ = true; }

    }

    void pointCloud::addPoints(const std::vector<glm::vec3>& points) {

        if(points.empty()) return;

        size_t count = points.size();
        size_t dif = maxPoints_ - head_;

        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        if(count <= dif){
            memcpy(&points_[head_], points.data(), count * sizeof(glm::vec3));

            glBufferSubData(GL_ARRAY_BUFFER, head_ * sizeof(glm::vec3), count*sizeof(glm::vec3), points.data() );


            head_ = (head_ + count) % maxPoints_;
            if (head_ == 0) filed_ = true;

        }else{


            memcpy(&points_[head_], points.data(), dif * sizeof(glm::vec3));
            glBufferSubData(GL_ARRAY_BUFFER, head_ * sizeof(glm::vec3), dif*sizeof(glm::vec3), points.data() );
            head_ = (head_ + dif) % maxPoints_;

            int rem = count - dif;

            memcpy(&points_[0], points.data() + dif, rem * sizeof(glm::vec3));
            glBufferSubData(GL_ARRAY_BUFFER, 0, rem*sizeof(glm::vec3), points.data() + dif);
            head_ = rem;
            filed_ = true;


        }



    }


    void pointCloud::clear() {
        memset(points_.data(), 0, points_.size() * sizeof(glm::vec3));
        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        glBufferSubData(GL_ARRAY_BUFFER, 0, maxPoints_*sizeof(glm::vec3), &points_[0]);


        head_ = 0;
        filed_ = false;
    }

    void pointCloud::render() {

        // std::cout << "clud render" << std::endl;

        if (!shader_) return;
        shader_->use();

        shader_->loadUniformMat4(getModelMatrix(), "model");

        glBindVertexArray(VAO_);


        size_t count = filed_ ? maxPoints_ : head_;
        glDrawArrays(GL_POINTS, 0, (GLsizei)count);

        glBindVertexArray(0);
    }



}
