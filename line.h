#ifndef LINE_H
#define LINE_H


#include "visualobject.h"

class Line : public VisualObject
{
public:
    Line(const gsml::Vector3d& direction, const gsml::Matrix4x4& positionMatrix, gsml::Vector3d color = gsml::Vector3d(1,0,0));
    void init(GLint matrixUniform) override;
    void draw() override;
    void scale(float s);

    //Must be set!
    const gsml::Vector3d* mDirection{nullptr};
    const gsml::Matrix4x4* mObjPosition{nullptr};
};

#endif // LINE_H
