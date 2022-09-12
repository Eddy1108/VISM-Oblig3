#include "rollingball.h"

RollingBall::RollingBall(int n) : OctahedronBall (n)
{
    //mVelocity = gsml::Vector3d{1.0f, 1.0f, -0.05f};
    mPosition.translate(0,0,0.25);
    mScale.scale(0.25,0.25,0.25);
}
RollingBall::~RollingBall()
{

}
void RollingBall::move(float dt)
{
    std::vector<gsml::Vertex>& vertices = dynamic_cast<TriangleSurface*>(triangle_surface)->get_vertices();

    mMatrix = mPosition * mScale; //Remove later

    return;

    for (size_t i = 0; i < vertices.size(); i++)
    {
        //Finn trekantens vertices v0, v1, v2
        //Finn ballens posisjon i xy-planet
        //S�k etter triangel som ballen er p� n�
        // - med barysentriske koordinater

        if (true /*barysentrisk koordinater mellom 0 og 1*/)
        {
            //beregn normal
            //beregn akselerasjonvektor - ligning (7)

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
    }




    //mMatrix = mPosition * mScale;

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
