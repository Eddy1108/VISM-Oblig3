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
protected:
    VisualObject* triangle_surface;
private:
    gsml::Vector3d mvelocity_0{0,0,0};
    gsml::Vector3d mvelocity{0,0,0};
    float macceleration{0};
    float gravity{9.80665};
};
#endif // ROLLINGBALL_H
