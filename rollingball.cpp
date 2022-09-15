#include "rollingball.h"
#include <QtMath>

RollingBall::RollingBall(int n) : OctahedronBall (n)
{
    //mVelocity = gsml::Vector3d{1.0f, 1.0f, -0.05f};
    mPosition.translate(0.5,0.5,0.5);
    mScale.scale(0.25f,0.25f,0.25f);
}
RollingBall::~RollingBall()
{

}
void RollingBall::move(float dt)
{
    std::vector<gsml::Vertex>& vertices = dynamic_cast<TriangleSurface*>(triangle_surface)->get_vertices();

    //mMatrix = mPosition * mScale; //Remove later

    //return;

    for (size_t i = 0; i < vertices.size(); i += 3)
    {
        //Finn trekantens vertices v0, v1, v2
        gsml::Vector3d v0 = vertices.at(i).getXYZ() * 10; // Multiplying with 10
        gsml::Vector3d v1 = vertices.at(i+1).getXYZ() * 10;
        gsml::Vector3d v2 = vertices.at(i+2).getXYZ() * 10;
        //Finn ballens posisjon i xy-planet
        gsml::Vector3d result = getPosition().barycentricCoordinates(v0, v1, v2);
        //std::cout << i << " = " << result << "\n";
        //Sæk etter triangel som ballen er på nå
        // - med barysentriske koordinater

        //Checks if the ball is within the triangle shape (on x and y axis only)
        if (result.x <= 1 && result.x >= 0 &&
                result.y <= 1 && result.y >= 0)
        {
            std::cout << "er innenfor trekant " << i/3 << "\n";
            //beregn normal  // Kunne bli lagret i minne senere, slikt at vi slipper å kalkulere det hver gang.
            gsml::Vector3d normal = findNormal(v0, v1, v2);
            std::cout << normal << " i trekant " << i/3 << "\n";

            //beregn akselerasjonvektor - ligning (7)
            //gsml::Vector3d N_force = m * g * ;

            //Oppdatere hastighet og posisjon

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
