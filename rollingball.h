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
    void move(double* dt) override;
    void setSurface(VisualObject* surface);
    gsml::Vector3d getPosition();
    gsml::Vector3d findNormal(gsml::Vector3d v0, gsml::Vector3d v1, gsml::Vector3d v2);
protected:
    VisualObject* triangle_surface{nullptr};
private:
    int oldTriangleIndex{-1};
    gsml::Vector3d oldNormal{0.0, 0.0, 1.0};
    gsml::Vector3d mVelocity_0{0,0,0};
    gsml::Vector3d mVelocity{0,0,0};
    gsml::Vector3d mAcceleration{0,0,0};
    gsml::Vector3d mGravity{0,0,-9.80665};

    float mMass {0.0175f}; //kg
    //float mRadius {0.175f}; // m
    float mRadius {0.03f};
};
#endif // ROLLINGBALL_H
