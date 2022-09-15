#include "rollingball.h"
#include <QtMath>

RollingBall::RollingBall(int n) : OctahedronBall (n)
{
    //mVelocity = gsml::Vector3d{1.0f, 1.0f, -0.05f};
    mPosition.translate(0.1,0.1,0.2);
    mScale.scale(mRadius*0.1,mRadius*0.1,mRadius*0.1);
}
RollingBall::~RollingBall()
{

}
void RollingBall::move(float dt)
{
    std::vector<gsml::Vertex>& vertices = dynamic_cast<TriangleSurface*>(triangle_surface)->get_vertices();

    //mMatrix = mPosition * mScale; //Remove later


    for (size_t i = 0; i < vertices.size(); i += 3)
    {
        //Finn trekantens vertices v0, v1, v2
        gsml::Vector3d v0 = vertices.at(i).getXYZ(); // Multiplying with 10
        gsml::Vector3d v1 = vertices.at(i+1).getXYZ();
        gsml::Vector3d v2 = vertices.at(i+2).getXYZ();
        //Finn ballens posisjon i xy-planet
        gsml::Vector3d result = getPosition().barycentricCoordinates(v0, v1, v2);

        std::cout << "ball position: " << getPosition() << std::endl;
        std::cout << "Position v0: " << v0 << ", v1: " << v1 << ", v2: " << v2 << std::endl;
        std::cout << i << " = " << result << "\n";
        //Sæk etter triangel som ballen er på nå
        // - med barysentriske koordinater

        //Checks if the ball is within the triangle shape (on x and y axis only)
        if (result.x + result.y + result.z >= 0.99999 && result.x + result.y + result.z <= 1.00001)
        {
            std::cout << "er innenfor trekant " << i/3 << "\n";
            //beregn normal  // Kunne vært lagret i minne, slikt at vi slipper å kalkulere det hver render.
            gsml::Vector3d planeNormal = findNormal(v0, v1, v2);
            std::cout << planeNormal << " i trekant " << i/3 << "\n";

            //beregn akselerasjonvektor - ligning (7)
            float alpha = gsml::Vector3d(0,0,1).dotProduct(planeNormal); // Finner vinkel mellom normal til xy-aksen og bakken sin normal
            //float alpha = planeNormal.Z; // da får man cos(alpha) og ikke alpha
            std::cout << "Alpha: " << alpha << "\n";
            gsml::Vector3d N_force = planeNormal* mGravity.abs().z * mMass * cos(alpha);

            gsml::Vector3d acceleration = (N_force+(mGravity*mMass)) / mMass;

            std::cout << "Normal Force: " << N_force << std::endl;
            std::cout << "Acceleration: " <<  acceleration << std::endl;

            //Oppdatere hastighet og posisjon
            mVelocity = mVelocity + acceleration * 0.1f;
            mPosition.translate(mVelocity.x * dt, mVelocity.y * dt, mVelocity.z * dt);


            if (true /*ny indeks != forrige index*/)
            {
                // ballen har rullet over paa nytt triangel
                // beregn normalen til kollisjonsplanet, se ligning (9)
                // Korrigere posisjon oppover i normalens retning
                // Oppdater hastighetsvektoren, se ligning (8)
                // Oppdater posisjon i retning den nye hastighetsvektoren
            }
        }
        else {
            std::cout << "er utenfor trekant " << i/3 << "\n";
        }
    }

    mMatrix = mPosition * mScale;
    return;
}

gsml::Vector3d RollingBall::findNormal(gsml::Vector3d v0, gsml::Vector3d v1, gsml::Vector3d v2)
{
    gsml::Vector3d ac = v2 - v0;
    gsml::Vector3d ab = v1 - v0;
    gsml::Vector3d result = ab.cross(ac);

    return result.getNormalized();
}

void RollingBall::setSurface(VisualObject *surface)
{
    triangle_surface = surface;
}

gsml::Vector3d RollingBall::getPosition()
{
    return gsml::Vector3d(mPosition(0,3), mPosition(1,3), mPosition(2,3));
}

void RollingBall::init(GLint matrixUniform)
{
   mMatrixUniform = matrixUniform;
   initializeOpenGLFunctions();

   //Vertex Array Object - VAO
   glGenVertexArrays( 1, &mVAO );
   glBindVertexArray( mVAO );

   //Vertex Buffer Object to hold vertices - VBO
   glGenBuffers( 1, &mVBO );
   glBindBuffer( GL_ARRAY_BUFFER, mVBO );

   glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof(gsml::Vertex), mVertices.data(), GL_STATIC_DRAW );

   glBindBuffer(GL_ARRAY_BUFFER, mVBO);
   glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,sizeof(gsml::Vertex), (GLvoid*)0);
   glEnableVertexAttribArray(0);

   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(gsml::Vertex),  (GLvoid*)(3 * sizeof(GLfloat)) );
   glEnableVertexAttribArray(1);

   glBindVertexArray(0);
}

void RollingBall::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_TRUE, mMatrix.constData());
   glDrawArrays(GL_TRIANGLES, 0, mVertices.size());//mVertices.size());
}
