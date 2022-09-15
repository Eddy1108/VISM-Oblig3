#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H

#include "octahedronball.h"
#include "trianglesurface.h"
#include "Math/Barycentric.h"

class RollingBall : public OctahedronBall
{
public:
    RollingBall(int n);
    ~RollingBall() override;
    void init(GLint matrixUniform) override;
    void draw() override;
    void move(float dt) override;
    void setSurface(VisualObject* surface);
    gsml::Vector3d getPosition();
    gsml::Vector3d findNormal(gsml::Vector3d v0, gsml::Vector3d v1, gsml::Vector3d v2);
protected:
    VisualObject* triangle_surface{nullptr};
private:
    gsml::Vector3d old_normal{0.0, 0.0, 1.0};
    gsml::Vector3d mvelocity_0{0,0,0};
    gsml::Vector3d mvelocity{0,0,0};
    gsml::Vector3d macceleration{0,0,0};
    gsml::Vector3d mGravity{0,0,-9.80665};

    float ballMass {17.5f}; //g
    float ballRadius {17.5f}; // mm
};
#endif // ROLLINGBALL_H
