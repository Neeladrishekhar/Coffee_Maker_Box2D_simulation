/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 251 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * 
 */


#include "cs251_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs251
{
  /**  
   * The following mentioned pbjects are constructed in this class which will render on release
   */ 
  
  dominos_t::dominos_t()
  {
    /*! \section Ground
     * - this initializes the ground as a straight line segment below the simulation
     */ 
    b2Body* b1;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-110.0f, -79.5f), b2Vec2(90.0f, -79.5f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
/*
// signature : T
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(50,-75.5);
      bd->fixedRotation = true;

      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.0;
      fd->friction = 0.5;
      fd->restitution = 0.f;
      fd->shape = new b2PolygonShape;
      b2PolygonShape bs;
      bs.SetAsBox(0.5,4, b2Vec2(0.0f,4.0f), 0);
      fd->shape = &bs;

      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(4,0.5, b2Vec2(0.0f,8.0f), 0);
      fd1->shape = &bs1;


      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd);
      box1->CreateFixture(fd1);
    }

// signature : r
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(54,-75.5);
      bd->fixedRotation = true;

      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.0;
      fd->friction = 0.5;
      fd->restitution = 0.f;
      fd->shape = new b2PolygonShape;
      b2PolygonShape bs;
      bs.SetAsBox(0.5,3, b2Vec2(0.0f,3.0f), 0);
      fd->shape = &bs;

      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.5, b2Vec2(2.0f,6.0f), 0);
      fd1->shape = &bs1;

      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(2,0.5, b2Vec2(2.0f,3.0f), 0);
      fd2->shape = &bs2;

      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 1.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.5,2, b2Vec2(4.0f,4.5f), 0);
      fd3->shape = &bs3;

      b2FixtureDef *fd4 = new b2FixtureDef;
      fd4->density = 1.0;
      fd4->friction = 0.5;
      fd4->restitution = 0.f;
      fd4->shape = new b2PolygonShape;
      b2PolygonShape bs4;
      bs4.SetAsBox(1.8,0.5, b2Vec2(3.0f,1.5f), -1);
      fd4->shape = &bs4;

      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
      box1->CreateFixture(fd4);
    }

// signature : i
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(60,-75.5);
      bd->fixedRotation = true;

      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.0;
      fd->friction = 0.5;
      fd->restitution = 0.f;
      fd->shape = new b2PolygonShape;
      b2PolygonShape bs;
      bs.SetAsBox(0.5,3, b2Vec2(0.0f,3.0f), 0);
      fd->shape = &bs;

      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd);
    }
*/

    /*! \section Water-Container
     * - This will be responsible mostly for guiding our water molecules and not allowing it to get spilled
     * - This has two parts :
     * \subsection Vertical-column
     * - The parallel vertical bars that are long and contain our water initially
     * \subsection Funneling-column
     * - The two tilted bars on either sides that lead the water to flow out in a convergent manner on our next mechanism 
     */ 
    { b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(1.6,0.2, b2Vec2(-5.1f,-7.5f), -1);
      fd1->shape = &bs1;
      
      b2FixtureDef *fd4 = new b2FixtureDef;
      fd4->density = 10.0;
      fd4->friction = 0.5;
      fd4->restitution = 0.f;
      fd4->shape = new b2PolygonShape;
      b2PolygonShape bs4;
      bs4.SetAsBox(1.6,0.2, b2Vec2(5.1f,-7.5f), 1);
      fd4->shape = &bs4;
      
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,10.0, b2Vec2(6.0f,4.f), 0);
      fd2->shape = &bs2;

      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,10.0, b2Vec2(-6.0f,4.f), 0);
      fd3->shape = &bs3;

      b2BodyDef bd3;
      bd3.position.Set(-10.0f, 35.0f);
      b2Body* body3 = m_world->CreateBody(&bd3);
      body3->CreateFixture(fd1);
      body3->CreateFixture(fd2);
      body3->CreateFixture(fd3);
      body3->CreateFixture(fd4);
    }

    /*! \section Upper-planks
     * - This will help us initialise our simulation
     * - They will hold our train of spheres and dominoes on both the sides initially
     * - It has 4 parts :
     * -- Two on the left and another two on the right of which the upper one holds the train of dominoes and the
     * lower one holds the train of spheres which will start moving when hit by the dominoes from the top
     */ 
// right plank for train of spheres and dominoes    
    {
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(7.8,0.2, b2Vec2(40.9f,0.0f), 0);
      fd1->shape = &bs1;

      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(8,0.2, b2Vec2(57.0f,5.0f), 0);
      fd2->shape = &bs2;

      b2BodyDef bd3;
      bd3.position.Set(-10.0f, 50.0f);
      b2Body* body3 = m_world->CreateBody(&bd3);
      body3->CreateFixture(fd1);
      body3->CreateFixture(fd2);
    }

//left plank for train of spheres and dominoes
    {
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(8,0.2, b2Vec2(-40.9f,0.0f), 0);
      fd1->shape = &bs1;

      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(8,0.2, b2Vec2(-57.0f,5.0f), 0);
      fd2->shape = &bs2;

      b2BodyDef bd3;
      bd3.position.Set(-10.0f, 50.0f);
      b2Body* body3 = m_world->CreateBody(&bd3);
      body3->CreateFixture(fd1);
      body3->CreateFixture(fd2);
    }

    /*! \section Upper-pendlums
     * - This will be resposible to initialise our simulation
     * - Its initially set to swing such that it hits the outside dominoe which in turn will make all
     * the dominoes fall in the train
     * - It has 3 parts :
     * - The \b gong of the pendulum which is set as a dynamic body, another invisible body fixed with respect to ground
     * and the anchor point.
     * - A revolute joint is defined between the two bodies through the anchor making it work as a pendulum as
     * only one body is dynamic
     */ 

//right top pendulum
    {
      b2Body* b2;
      {
        b2PolygonShape shape;
        shape.SetAsBox(0.f, 0.f);
          
        b2BodyDef bd;
        bd.position.Set(55.5f, 65.0f);
        b2 = m_world->CreateBody(&bd);
        b2->CreateFixture(&shape, 10.0f);
      }
  
      b2Body* b4;
      {
        b2PolygonShape shape;
        shape.SetAsBox(0.25f, 0.25f);
          
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(60.0f, 58.3f);
        b4 = m_world->CreateBody(&bd);
        b4->CreateFixture(&shape, 100.0f);
      }
  
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(55.0f, 65.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }

//left top pendulum
    {
      b2Body* b2;
      {
        b2PolygonShape shape;
        shape.SetAsBox(0.f, 0.f);
          
        b2BodyDef bd;
        bd.position.Set(-75.5f, 65.0f);
        b2 = m_world->CreateBody(&bd);
        b2->CreateFixture(&shape, 10.0f);
      }
  
      b2Body* b4;
      {
        b2PolygonShape shape;
        shape.SetAsBox(0.25f, 0.25f);
          
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(-80.0f, 58.3f);
        b4 = m_world->CreateBody(&bd);
        b4->CreateFixture(&shape, 100.0f);
      }
  
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-75.0f, 65.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
   /*! \section Train-Of-Dominoes
    * - This part of the code constructs the array of dominoes on both sides
    * - The first one gets hit by the pendulum and the last one falls of the platform over the train
    * of spheres thus giving them a push in the required direction.
    */
    //right side Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 70.0f;
      fd.friction = 0.1f;
    
      for (int i = 0; i < 16; ++i)
  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(54.7f - 1.0f * i, 56.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);
  }
    }

    //left side Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 70.0f;
      fd.friction = 0.1f;
    
      for (int i = 0; i < 16; ++i)
  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(-74.7f + 1.0f * i, 56.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);
  }
    }

   /*! \section Train-of-Spheres
    * These are initialized on both sides.
    * - They have alternate \b high and \b low density in the sequence
    * - Hence as balls from both side of the system fall at the same time they have different masses and thus
    * there is a difference in weights in the pulley system it was being collected
    * - This leads to an oscillating motion for the wedge below the water thus allowing water to go from both sides
    */
//right side train of spheres
    {
      b2Body* spherebody;
  
      b2CircleShape circle;
      circle.m_radius = 0.5;
  
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 80.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
  
      for (int i = 0; i < 10; ++i)
  {
    if(i%2==1){ballfd.density = 10.0f;}

    b2BodyDef ballbd;
    ballbd.type = b2_dynamicBody;
    ballbd.position.Set(36.0f - i*1.0, 50.7f);
    spherebody = m_world->CreateBody(&ballbd);
    spherebody->CreateFixture(&ballfd);

    ballfd.density = 80.0f;
  }
    }
//left side train of spheres
    {
      b2Body* spherebody;
  
      b2CircleShape circle;
      circle.m_radius = 0.5;
  
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 10.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
  
      for (int i = 0; i < 10; ++i)
  {
    if(i%2==1){ballfd.density = 80.0f;}

    b2BodyDef ballbd;
    ballbd.type = b2_dynamicBody;
    ballbd.position.Set(-56.0f + i*1.0, 50.7f);
    spherebody = m_world->CreateBody(&ballbd);
    spherebody->CreateFixture(&ballfd);

    ballfd.density = 10.0f;
  }
    }

   /*! \section Water-molecules
    * - These are initialized to small sized spheres inside its container
    * - they fall and continue only when the \b sea-saw mechanism on which they are initialised moves
    */
//water molecules
    {
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 0.2;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = .6f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.2f;
      for (int j=0; j<15 ; ++j){
	      for (int i = 0; i < 29; ++i)
		{
		  b2BodyDef ballbd;
		  ballbd.type = b2_dynamicBody;
		  ballbd.position.Set(-15.7f + i*0.4, 31.2f + j*0.7);
		  spherebody = m_world->CreateBody(&ballbd);
		  spherebody->CreateFixture(&ballfd);
		  
		  b2BodyDef ballbd1;
		  ballbd1.type = b2_dynamicBody;
		  ballbd1.position.Set(-15.5f + i*0.4, 31.55f + j*0.7);
		  spherebody = m_world->CreateBody(&ballbd1);
		  spherebody->CreateFixture(&ballfd);
		}
      }
    } 

  /*! \section Coffee-molecules
    * - These are initialized to medium and large sized spheres inside its container
    * - They are of two types:
    * \n Smaller ones which will mix with the water molecules and get drained for sugar addition and
    * \n Larger ones which will also mix with water molecules but will remain in the \b strainer
    * - they fall and continue only when the \b heavy pendulum pushes of the larger molecules of the pores of the strainer
    */
//coffee molecules
    {//not edible
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 1.;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.8f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.2f;
      for (int i = 0; i <14; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-22.5f + i*2.0, 20.f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
      
    } 

    {//edible
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 0.4;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.8f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.2f;
      for (int i = 0; i <37; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-24.5f + i*.8, 21.4f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	  
	  b2BodyDef ballbd1;
	  ballbd1.type = b2_dynamicBody;
	  ballbd1.position.Set(-24.1f + i*.8, 22.1f);
	  spherebody = m_world->CreateBody(&ballbd1);
	  spherebody->CreateFixture(&ballfd);
	}
      
    } 

   /*! \section Churner
    * - This is just a pendulum with a very heavy gong.
    * - This is initialised by the three rotator system which in turn are rotated by the falling water molecules
    * - This pendulum pushes the heavy coffee molecules of the pores of the strainer continuously so that the water and
    * small coffee molecules pass through it
    */
//*******The pendulum that churns
    {
      b2Body* b2;
      {
      	b2PolygonShape shape;
      	shape.SetAsBox(0.0f, 0.f);
      	  
      	b2BodyDef bd;
      	bd.position.Set(-10.0f, 23.0f);
      	b2 = m_world->CreateBody(&bd);
      	b2->CreateFixture(&shape, 23.0f);
      }
	
      b2Body* b4;
      {
        b2PolygonShape shape;
        shape.SetAsBox(0.25f, 0.25f);
  	
        b2FixtureDef ballfd;
        ballfd.shape = &shape;
        ballfd.density = 3000.0f;
        ballfd.friction = 0.5f;
        ballfd.restitution = 0.0f;
        b2BodyDef ballbd;
        ballbd.type = b2_dynamicBody;
        ballbd.position.Set(-20.0f, 23.225f);
        b4 = m_world->CreateBody(&ballbd);
        b4->CreateFixture(&ballfd);
      }

      b2RopeJointDef jd;
      jd.bodyA=b2; 
      jd.bodyB=b4;
      jd.localAnchorA.Set(0.0f, 0.0f) ; 
      jd.localAnchorB.Set(0.0f, 0.0f) ; 
      jd.maxLength = 10.4f;
      m_world->CreateJoint(&jd);
    }

    /*! \section Pulley-System
    * This exists on both sides of the water container
    * \n It collects the one-by-one falling spheres and in an open box and both these boxes are in turn attached to the 
    * opposite sides of the sea-saw mechanism
    * - Hence due to the weight difference on the two sides spheres we get the sea-saw system to change its
    * \b tilt direction, which in turn leads to water falling from both sides of the sea-saw.
    */
//The pulley system
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-30,50);
      bd->fixedRotation = true;

      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(3,0.2, b2Vec2(-10.f,-11.9f), 0);
      fd1->shape = &bs1;

      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,3, b2Vec2(-7.5f,-9.5f), 0);
      fd2->shape = &bs2;

      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 1.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,3, b2Vec2(-12.5f,-9.5f), 0);
      fd3->shape = &bs3;

      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
// the other side also has similar fixtures
      b2BodyDef *bd11 = new b2BodyDef;
      bd11->type = b2_dynamicBody;
      bd11->position.Set(30,50);
      bd11->fixedRotation = true;

      b2Body* box2 = m_world->CreateBody(bd11);
      box2->CreateFixture(fd1);
      box2->CreateFixture(fd2);
      box2->CreateFixture(fd3);

      //wedge inside the water container
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(-10.0f, 29.35f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge inside the water coontainer
      b2PolygonShape shape;
      shape.SetAsBox(5.6f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(-10.0f, 30.85f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      
      b2FixtureDef *fd4 = new b2FixtureDef;
      fd4->density = 1.f;
      fd4->shape = new b2PolygonShape;
      fd4->shape = &shape;
      body->CreateFixture(fd4);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-10.0f,30.85f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2PulleyJointDef* myjoint2 = new b2PulleyJointDef();
      
      b2Vec2 anchor1(-40.2, 50); 
      b2Vec2 anchor2(-15.2,50);
      b2Vec2 anchor3(20.3,50);
      b2Vec2 anchor4(-4.8,50);
      b2Vec2 body2anchor(-15.2,30.85) ;
      b2Vec2 body2anchor2(-4.8,30.85) ;
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, body, anchor1, anchor2, box1->GetWorldCenter(), body2anchor, ratio);
      myjoint2->Initialize(box2, body, anchor3, anchor4, box2->GetWorldCenter(), body2anchor2, ratio);
      m_world->CreateJoint(myjoint);
      m_world->CreateJoint(myjoint2);
    }

    /*! \section Tri-rotators
    * This is the part of the simulation will initialise our \b churner mechanism
    * It consistes of 3 rotators with their rotating axis fixed with respect to ground.
    * \n The leftmost one has the pendulum sitting on top of it, such that rotating the rightmost one will rotate it
    * The rightmost one is rotated by the falling water molecules
    */
//rotator1 for the pendulum that churns
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.5f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(-10.0f, 23.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = .1f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2BodyDef bd2;
      bd2.position.Set(-10.0f, 23.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

//rotator2 for the pendulum that churns
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.8f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(-15.0f, 23.5f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2BodyDef bd2;
      bd2.position.Set(-15.0f, 23.5f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

//rotator3 for the pendulum that churns
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.5f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(-20.0f, 23.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2BodyDef bd2;
      bd2.position.Set(-20.0f, 23.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
      
      b2Body* b4;
      b2BodyDef bd3;
      b2PolygonShape shape1;
      shape1.SetAsBox(0.f, 0.f);
      bd3.position.Set(-21.25f, 22.75f);
      b4 = m_world->CreateBody(&bd3);
      b4->CreateFixture(&shape1, 2.0f);
    }
/*
//checking with extra ball
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.5;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(-40.0f, 50.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }

    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.5;
  
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(20.0f, 100.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }
*/
/////lower jar where the water and coffee mixture is heated
    /*! \section Heater-box
    * - This is the part where we collect the mixture of water and coffee and heat it
    * - Heating is depicted by the forced \b fixed \b rotating \b wheels inside it made by declaring it as a
    * \b b2_kineticbody type b2BodyDef and giving an initial angular velocity
    * - It has two holes along its wall from where the hot mixture is passed below for addition of sugar
    */
     {
      b2BodyDef *bd = new b2BodyDef;
      bd->position.Set(-10,15);
      bd->fixedRotation = true;

      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(4.65,0.2, b2Vec2(4.6f,-15.5f), -0.1);
      fd1->shape = &bs1;

      b2FixtureDef *fd11 = new b2FixtureDef;
      fd11->density = 1.0;
      fd11->friction = 0.5;
      fd11->restitution = 0.f;
      fd11->shape = new b2PolygonShape;
      b2PolygonShape bs11;
      bs11.SetAsBox(4.65,0.2, b2Vec2(-4.6f,-15.5f), 0.1);
      fd11->shape = &bs11;

      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,6, b2Vec2(10.3f,-11.f), 0);
      fd2->shape = &bs2;

      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 1.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,6, b2Vec2(-10.3f,-11.f), 0);
      fd3->shape = &bs3;
      
      b2FixtureDef *fd4 = new b2FixtureDef;
      fd4->density = 1.0;
      fd4->friction = 0.5;
      fd4->restitution = 0.f;
      fd4->shape = new b2PolygonShape;
      b2PolygonShape bs4;
      bs4.SetAsBox(0.2,3.9, b2Vec2(13.5f,-3.f), -1);
      fd4->shape = &bs4;
      
      b2FixtureDef *fd5 = new b2FixtureDef;
      fd5->density = 1.0;
      fd5->friction = 0.5;
      fd5->restitution = 0.f;
      fd5->shape = new b2PolygonShape;
      b2PolygonShape bs5;
      bs5.SetAsBox(0.2,3.9, b2Vec2(-13.5f,-3.f), 1);
      fd5->shape = &bs5;
       
      b2FixtureDef *fd6 = new b2FixtureDef;
      fd6->density = 1.0;
      fd6->friction = 0.5;
      fd6->restitution = 0.f;
      fd6->shape = new b2PolygonShape;
      b2PolygonShape bs6;
      bs6.SetAsBox(0.2,4.7, b2Vec2(-16.9f,4.f), 0);
      fd6->shape = &bs6;

      b2FixtureDef *fd7 = new b2FixtureDef;
      fd7->density = 1.0;
      fd7->friction = 0.5;
      fd7->restitution = 0.f;
      fd7->shape = new b2PolygonShape;
      b2PolygonShape bs7;
      bs7.SetAsBox(0.2,4.7, b2Vec2(16.9f,4.f), 0);
      fd7->shape = &bs7;

      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd11);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
      box1->CreateFixture(fd4);
      box1->CreateFixture(fd5);
      box1->CreateFixture(fd6);
      box1->CreateFixture(fd7);
      }

      //the churner container with pores in it
/*! \section Strainer
* It has pores through which only the small coffee molecules and water can pass.
* \n This is where we initially place all the coffee molecules but they don't fall as the larger molecules \b block all
* the \b pores of the strainer
* - Its size and shape is set according to the \b churner so that the churner doesn't get stuck in the pores
* - Its extended so that the mixture does not gets spilled
*/
{
      b2BodyDef *bd = new b2BodyDef;
      bd->position.Set(0,25);
      bd->fixedRotation = true;
      
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.0; // center
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(1.3,0.2, b2Vec2(-11.9f,-13.f), 0);
      fd1->shape = &bs1;
      
      b2FixtureDef *fd15 = new b2FixtureDef;
      fd15->density = 1.0; // center
      fd15->friction = 0.5;
      fd15->restitution = 0.f;
      fd15->shape = new b2PolygonShape;
      b2PolygonShape bs15;
      bs15.SetAsBox(1.3,0.2, b2Vec2(-8.f,-13.f), 0);
      fd15->shape = &bs15;

      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.0; 
      fd2->friction = 0.5; //third from right
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,1.8, b2Vec2(-1.f,-9.f), -0.7);
      fd2->shape = &bs2;
      
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 1.0;
      fd3->friction = 0.5; //third from left
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,1.8, b2Vec2(-19.f,-9.f), 0.7);
      fd3->shape = &bs3;

	  b2FixtureDef *fd6 = new b2FixtureDef;
      fd6->density = 1.0;
      fd6->friction = 0.5; //second from left
      fd6->restitution = 0.f;
      fd6->shape = new b2PolygonShape;
      b2PolygonShape bs6;
      bs6.SetAsBox(0.2,1.8, b2Vec2(-22.5f,-6.f), 1.1);
      fd6->shape = &bs6;

	  b2FixtureDef *fd7 = new b2FixtureDef;
      fd7->density = 1.0;
      fd7->friction = 0.5; //leftmost
      fd7->restitution = 0.f;
      fd7->shape = new b2PolygonShape;
      b2PolygonShape bs7;
      bs7.SetAsBox(0.2,8.8, b2Vec2(-28.5f,2.8f), 0.5);
      fd7->shape = &bs7;

      b2FixtureDef *fd8 = new b2FixtureDef;
      fd8->density = 1.0;
      fd8->friction = 0.5; //second from right
      fd8->restitution = 0.f;
      fd8->shape = new b2PolygonShape;
      b2PolygonShape bs8;
      bs8.SetAsBox(0.2,1.8, b2Vec2(2.5f,-6.f), -1.1);
      fd8->shape = &bs8;

	  b2FixtureDef *fd9 = new b2FixtureDef;
      fd9->density = 1.0;
      fd9->friction = 0.5; //rightmost
      fd9->restitution = 0.f;
      fd9->shape = new b2PolygonShape;
      b2PolygonShape bs9;
      bs9.SetAsBox(0.2,8.8, b2Vec2(8.5f,2.8f), -0.5);
      fd9->shape = &bs9;
      
      b2FixtureDef *fd4 = new b2FixtureDef;       
      fd4->density = 1.0;
      fd4->friction = 0.5; // fourth from right
      fd4->restitution = 0.f;
      fd4->shape = new b2PolygonShape;
      b2PolygonShape bs4;
      bs4.SetAsBox(0.2,1.4, b2Vec2(-4.45f,-11.75f), -1);
      fd4->shape = &bs4;

      b2FixtureDef *fd5 = new b2FixtureDef;
      fd5->density = 1.0;
      fd5->friction = 0.5; 
      fd5->restitution = 0.f; // fourth from left
      fd5->shape = new b2PolygonShape;
      b2PolygonShape bs5;
      bs5.SetAsBox(0.2,1.4, b2Vec2(-15.45f,-11.75f), 1);
      fd5->shape = &bs5;

      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
      box1->CreateFixture(fd4);
      box1->CreateFixture(fd5);
      box1->CreateFixture(fd15);
      
      box1->CreateFixture(fd6);
      box1->CreateFixture(fd7);
      box1->CreateFixture(fd8);
      box1->CreateFixture(fd9);
      }
/*! \section Heater
* - These are kinematic bodies which rotate at a constant speed which lead to heating up the things it touches
* - Its an eight sided pinwheel having its axis of rotation rotation fixed w.r.t to ground
* - two of them are initiallized in either sides of the \ Heater-box .
*/
// creating the pin wheel that acts as the heater leftwards
    {

      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 0.1;
      fd->shape = new b2PolygonShape;
      b2PolygonShape bs;
      bs.SetAsBox(0.2,2.5, b2Vec2(0.0f,0.0f), 0);
      fd->shape = &bs;

      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 0.1;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2.5,0.2, b2Vec2(0.0f,0.0f), 0);
      fd1->shape = &bs1;

      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 0.1;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(2.5,0.2, b2Vec2(0.0f,0.0f), 0.75);
      fd2->shape = &bs2;

      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.1;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(2.5,0.2, b2Vec2(0.0f,0.0f), -0.75);
      fd3->shape = &bs3;

      b2BodyDef bd;
      bd.position.Set(-17.0f, 2.5f);

      bd.type = b2_kinematicBody;
      
      b2Body* body = m_world->CreateBody(&bd);
      body->CreateFixture(fd);
      body->CreateFixture(fd1);
      body->CreateFixture(fd2);
      body->CreateFixture(fd3);

      body->SetAngularVelocity(-6.0f);
    }

// creating another pin wheel that acts as the heater rightwards
    {

      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 0.1;
      fd->shape = new b2PolygonShape;
      b2PolygonShape bs;
      bs.SetAsBox(0.2,2.5, b2Vec2(0.0f,0.0f), 0);
      fd->shape = &bs;

      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 0.1;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2.5,0.2, b2Vec2(0.0f,0.0f), 0);
      fd1->shape = &bs1;

      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 0.1;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(2.5,0.2, b2Vec2(0.0f,0.0f), 0.75);
      fd2->shape = &bs2;

      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.1;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(2.5,0.2, b2Vec2(0.0f,0.0f), -0.75);
      fd3->shape = &bs3;

      b2BodyDef bd;
      bd.position.Set(-3.0f, 2.5f);

      bd.type = b2_kinematicBody;
      
      b2Body* body = m_world->CreateBody(&bd);
      body->CreateFixture(fd);
      body->CreateFixture(fd1);
      body->CreateFixture(fd2);
      body->CreateFixture(fd3);

      body->SetAngularVelocity(6.0f);
   }

/*! \section Mixture-collector
* - This is where the Hot mixture containing water and coffee is drained to and is passed on for addition of sugar cubes.
* - It has two freely rotating pin-wheels that rotate when the mixture falls on it.
*/
//collector for the sugar simulator
      {
        b2FixtureDef *fd2 = new b2FixtureDef;
        fd2->density = 0.1;
        fd2->shape = new b2PolygonShape;
        b2PolygonShape bs2;
        bs2.SetAsBox(5.3,0.2, b2Vec2(10.0f,-2.0f), 0.2);
        fd2->shape = &bs2;

        b2FixtureDef *fd21 = new b2FixtureDef;
        fd21->density = 0.1;
        fd21->shape = new b2PolygonShape;
        b2PolygonShape bs21;
        bs21.SetAsBox(0.2,1.0, b2Vec2(14.8f,0.0f), 0);
        fd21->shape = &bs21;

        b2FixtureDef *fd1 = new b2FixtureDef;
        fd1->density = 0.1;
        fd1->shape = new b2PolygonShape;
        b2PolygonShape bs1;
        bs1.SetAsBox(5.3,0.2, b2Vec2(-10.0f,-2.0f), -0.2);
        fd1->shape = &bs1;

        b2FixtureDef *fd11 = new b2FixtureDef;
        fd11->density = 0.1;
        fd11->shape = new b2PolygonShape;
        b2PolygonShape bs11;
        bs11.SetAsBox(0.2,1.0, b2Vec2(-14.8f,0.0f), 0);
        fd11->shape = &bs11;

        b2BodyDef bd;
        bd.position.Set(-10.0f, -6.5f);
        b2Body* body = m_world->CreateBody(&bd);
        body->CreateFixture(fd2);
        body->CreateFixture(fd1);
        body->CreateFixture(fd21);
        body->CreateFixture(fd11);
      }

/*! \section Add-Sugar-column
* This is where we create the various layers for adding and mixing sugar at the same time to the heated mixture
* The idea is to make the sugar molecules slide a certain distance so that they do not get added at the same time 
* in different layers
*/
      //slots to add sugar
    {
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 0.1;
      fd2->friction = 0.0;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(3.0,0.2, b2Vec2(3.0f,0.0f), 0.25);
      fd2->shape = &bs2;

      b2FixtureDef *fd21 = new b2FixtureDef;
      fd21->density = 0.1;
      fd21->friction = 0.0;
      fd21->shape = new b2PolygonShape;
      b2PolygonShape bs21;
      bs21.SetAsBox(0.2,1.0, b2Vec2(5.8f,2.0f), 0);
      fd21->shape = &bs21;

      b2FixtureDef *fd22 = new b2FixtureDef;
      fd22->density = 0.1;
      fd22->friction = 0.0;
      fd22->shape = new b2PolygonShape;
      b2PolygonShape bs22;
      bs22.SetAsBox(2.5,0.05, b2Vec2(3.5f,3.0f), 0.25);
      fd22->shape = &bs22;

      b2FixtureDef *fd23 = new b2FixtureDef;
      fd23->density = 0.1;
      fd23->friction = 0.0;
      fd23->shape = new b2PolygonShape;
      b2PolygonShape bs23;

      b2FixtureDef *fd24 = new b2FixtureDef;
      fd24->density = 0.1;
      //fd24->friction = 0.0;
      fd24->shape = new b2PolygonShape;
      b2PolygonShape bs24;

      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 0.1;
      fd1->friction = 0.0;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(3.0,0.2, b2Vec2(-3.0f,-2.0f), -0.25);
      fd1->shape = &bs1;

      b2FixtureDef *fd11 = new b2FixtureDef;
      fd11->density = 0.1;
      fd11->friction = 0.0;
      fd11->shape = new b2PolygonShape;
      b2PolygonShape bs11;

      b2FixtureDef *fd12 = new b2FixtureDef;
      fd12->density = 0.1;
      fd12->friction = 0.0;
      fd12->shape = new b2PolygonShape;
      b2PolygonShape bs12;
      bs12.SetAsBox(2.5,0.05, b2Vec2(-3.5f,1.0f), -0.25);
      fd12->shape = &bs12;

      b2FixtureDef *fd13 = new b2FixtureDef;
      fd13->density = 0.1;
      fd13->friction = 0.0;
      fd13->shape = new b2PolygonShape;
      b2PolygonShape bs13;

      b2FixtureDef *fd14 = new b2FixtureDef;
      fd14->density = 0.1;
      //fd14->friction = 0.0;
      fd14->shape = new b2PolygonShape;
      b2PolygonShape bs14;

      for(int i = 1 ; i <= 10 ; ++i){
        b2BodyDef bd;
        bd.position.Set(-10.0f, -8.5f- 4*i);
        b2Body* body = m_world->CreateBody(&bd);
        body->CreateFixture(fd2);
        body->CreateFixture(fd1);
        body->CreateFixture(fd21);
        if(i==1){
      bs11.SetAsBox(0.2,2.0, b2Vec2(-5.8f,1.0f), 0);
      fd11->shape = &bs11;
        }
        body->CreateFixture(fd11);
        bs11.SetAsBox(0.2,1.0, b2Vec2(-5.8f,0.0f), 0);
        fd11->shape = &bs11;

        if(i>4){
      bs23.SetAsBox(7.5+((i-5)*3),0.05, b2Vec2(13.4f+((i-5)*3),3.62f), 0);
      fd23->shape = &bs23;
      bs24.SetAsBox(3.5,0.05, b2Vec2(24.4f+((i-5)*6),3.66f), 0.01);
      fd24->shape = &bs24;
      bs13.SetAsBox(7.5+((i-5)*3),0.05, b2Vec2(-13.4f-((i-5)*3),1.62f), 0);
      fd13->shape = &bs13;
      bs14.SetAsBox(3.5,0.05, b2Vec2(-24.4f-((i-5)*6),1.66f), -0.01);
      fd14->shape = &bs14;

          body->CreateFixture(fd22);
          body->CreateFixture(fd23);
          body->CreateFixture(fd24);
          body->CreateFixture(fd12);
          body->CreateFixture(fd13);
          body->CreateFixture(fd14);
        }
      }
    }

//sugar cubes
    {
      b2FixtureDef *fd2 = new b2FixtureDef;
      //fd2->density = 0.1;
      fd2->friction = 0.0;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;

      b2BodyDef bd;
      bd.type = b2_dynamicBody;
      bd.position.Set(-30.0f, -6.5f);

      for(int i = 0 ; i < 6 ; ++i){
      for(int j = 0 ; j < 6 ; ++j){
        if(j==0){ fd2->density = 0.9;}
        else{fd2->density = 0.1;}
      b2Body* body = m_world->CreateBody(&bd);
      bs2.SetAsBox(0.2,0.2, b2Vec2(-6.0f+(0.7*j)-(6*i),-20.0f-4*i),0);
      fd2->shape = &bs2;
      body->CreateFixture(fd2);
      }
      }
    }
/*! \section Sugar-initializer
* This is the mechanism by which we let the sugar cubes to start moving only after the mixture has reached
* the \b Add-Sugar-column.
* - The pin wheels edge is attached to the \b stopper of the sugar cubes such that once the pin-wheel starts rotating
* the stopper is lifted and the sugar cubes start moving towards the column for mixing. 
*/
// creating the pin wheel collector in left for initializing the sugar to start trail
    {

      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 0.1;
      fd->shape = new b2PolygonShape;
      b2PolygonShape bs;
      bs.SetAsBox(0.2,2.5, b2Vec2(0.0f,0.0f), 0);
      fd->shape = &bs;

      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 0.1;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2.5,0.2, b2Vec2(0.0f,0.0f), 0);
      fd1->shape = &bs1;

      b2Body* b4;
      b2BodyDef bd3;
      b2PolygonShape shape1;
      shape1.SetAsBox(0.f, 0.f);
      bd3.position.Set(-22.5f, -2.2f);
      b4 = m_world->CreateBody(&bd3);
      b4->CreateFixture(&shape1, 2.0f);

      b2BodyDef bd;
      bd.position.Set(-22.2f, -4.5f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      body->CreateFixture(fd);
      body->CreateFixture(fd1);

      b2BodyDef bd2;
      bd2.position.Set(-22.2f, -4.5f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    
      b2FixtureDef *fd22 = new b2FixtureDef;
      fd22->density = .2;
      fd22->friction = 1.0;
      fd22->shape = new b2PolygonShape;
      b2PolygonShape bs22;

      b2BodyDef bd22;
      bd22.type = b2_dynamicBody;
      bd22.position.Set(-30.0f, -6.5f);
      
      for(int i = 0 ; i < 6 ; ++i){
      b2Body* body2 = m_world->CreateBody(&bd22);
      bs22.SetAsBox(0.3,0.3, b2Vec2(-6.0f+(0.7*6)-(6*i),-20.0f-4*i),0);
      fd22->shape = &bs22;
      body2->CreateFixture(fd22);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      
      b2Vec2 anchor1(-36.0f+(0.7*6)-(6*i), -2.2); 
      b2Vec2 anchor2(-36.0f+(0.7*6)-(6*i), -2.2);
      b2Vec2 body2anchor(-22.2,-2.2) ;
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(body, body2, anchor1, anchor2, body2anchor, body2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);

      }

    }

//the sugar cubes on the right side
    {
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->friction = 0.0;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;

      b2BodyDef bd;
      bd.type = b2_dynamicBody;
      bd.position.Set(10.0f, -6.5f);

      for(int i = 0 ; i < 6 ; ++i){
      for(int j = 0 ; j < 6 ; ++j){
        if(j==0){ fd2->density = 0.9;}
        else{fd2->density = 0.1;}
      b2Body* body = m_world->CreateBody(&bd);
      bs2.SetAsBox(0.2,0.2, b2Vec2(6.0f-(0.7*j)+(6*i),-18.0f-4*i),0);
      fd2->shape = &bs2;
      body->CreateFixture(fd2);
      }
      }
    }

// creating the pin wheel collector in the right for initializing the sugar to start trail
    {

      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 0.1;
      fd->shape = new b2PolygonShape;
      b2PolygonShape bs;
      bs.SetAsBox(0.2,2.5, b2Vec2(0.0f,0.0f), 0);
      fd->shape = &bs;

      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 0.1;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2.5,0.2, b2Vec2(0.0f,0.0f), 0);
      fd1->shape = &bs1;

      b2Body* b4;
      b2BodyDef bd3;
      b2PolygonShape shape1;
      shape1.SetAsBox(0.f, 0.f);
      bd3.position.Set(2.3f, -2.2f);
      b4 = m_world->CreateBody(&bd3);
      b4->CreateFixture(&shape1, 2.0f);

      b2BodyDef bd;
      bd.position.Set(2.1f, -4.5f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      body->CreateFixture(fd);
      body->CreateFixture(fd1);

      b2BodyDef bd2;
      bd2.position.Set(2.1f, -4.5f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);

      b2FixtureDef *fd22 = new b2FixtureDef;
      fd22->density = .2;
      fd22->friction = 1.0;
      fd22->shape = new b2PolygonShape;
      b2PolygonShape bs22;

      b2BodyDef bd22;
      bd22.type = b2_dynamicBody;
      bd22.position.Set(10.0f, -6.5f);
      
      for(int i = 0 ; i < 6 ; ++i){
      b2Body* body2 = m_world->CreateBody(&bd22);
      bs22.SetAsBox(0.3,0.3, b2Vec2(6.0f-(0.7*6)+(6*i),-18.0f-4*i),0);
      fd22->shape = &bs22;
      body2->CreateFixture(fd22);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      
      b2Vec2 anchor1(16.0f-(0.7*6)+(6*i), -2.2); 
      b2Vec2 anchor2(16.0f-(0.7*6)+(6*i), -2.2);
      b2Vec2 body2anchor(2.1,-2.2) ;
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(body, body2, anchor1, anchor2, body2anchor, body2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);

      }
    }
/*! \section Coffee-cup
* This is just a simple container given the shape of coffee-cup with a handle.
* - Its fixed w.r.t ground and not a dynamic object
*/
//coffee cup : 
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->position.Set(-10,-70);
      bd->fixedRotation = true;

      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(0.5,9, b2Vec2(0.f,0.f), 0);
      fd1->shape = &bs1;

      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.5,9, b2Vec2(17.f,0.f), 0);
      fd2->shape = &bs2;

      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 1.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(9,0.5, b2Vec2(8.5f,-9.f), 0);
      fd3->shape = &bs3;

      b2FixtureDef *fd4 = new b2FixtureDef;
      fd4->density = 1.0;
      fd4->friction = 0.5;
      fd4->restitution = 0.f;
      fd4->shape = new b2PolygonShape;
      b2PolygonShape bs4;
      bs4.SetAsBox(5,0.9, b2Vec2(22.f,6.f), 0);
      fd4->shape = &bs4;

      b2FixtureDef *fd5 = new b2FixtureDef;
      fd5->density = 1.0;
      fd5->friction = 0.5;
      fd5->restitution = 0.f;
      fd5->shape = new b2PolygonShape;
      b2PolygonShape bs5;
      bs5.SetAsBox(5,0.9, b2Vec2(22.f,-4.f), 0);
      fd5->shape = &bs5;

      b2FixtureDef *fd6 = new b2FixtureDef;
      fd6->density = 1.0;
      fd6->friction = 0.5;
      fd6->restitution = 0.f;
      fd6->shape = new b2PolygonShape;
      b2PolygonShape bs6;
      bs6.SetAsBox(0.9,5.45, b2Vec2(26.5f,1.f), 0);
      fd6->shape = &bs6;

      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
      box1->CreateFixture(fd4);
      box1->CreateFixture(fd5);
      box1->CreateFixture(fd6);
    }
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
