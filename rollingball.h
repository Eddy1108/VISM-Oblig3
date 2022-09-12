#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H

#include "octahedronball.h"
#include "trianglesurface.h"

class RollingBall : public OctahedronBall
{
public:
    RollingBall(int n);
    ~RollingBall() override;
    void init(GLint matrixUniform) override;
    void draw() override;
    void move(float dt) override;
    void setSurface(VisualObject* surface) { triangle_surface = surface; }
    gsml::Vector3d getPosition();
protected:
    VisualObject* triangle_surface;
private:
    gsml::Vector3d mVelocity_0{0,0,0};
    gsml::Vector3d mVelocity{0,0,0};
    float mAcceleration{0};
    float mGravity{9.80665};
};
#endif // ROLLINGBALL_H
