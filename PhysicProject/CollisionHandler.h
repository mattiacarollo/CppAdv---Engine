#pragma once

#include <vector>
#include <iostream>
#include "Collision.h"


template<
	int MaxCollision
>
class CollisionHandler
{
	typedef std::vector<Collision*> CollisionCollection;
	typedef CollisionCollection::iterator Iterator;

public:

	void HandleCollision() 
	{
		int i = 0;
		for (Iterator collision = m_CollisionList.begin(); collision != m_CollisionList.end(); ++collision, ++i)
		{
			(*collision)->ApplyCollision();
		}
		std::cout << "Total Collision Handled: " << i << std::endl;
		Clear();
	}

	bool AddCollision(Collision* col,RigidBody* first,RigidBody* second)
	{
		if (m_CollisionList.size() < MaxCollision && col != nullptr)
		{
			col->SetBodies(first,second);
			m_CollisionList.push_back(col);
		}
		return m_CollisionList.size() == MaxCollision;
	}

	void Clear()
	{
		for (Iterator collision = m_CollisionList.begin(); collision != m_CollisionList.end(); ++collision)
		{
			delete *collision;
		}
		m_CollisionList.clear();
	}
	
	CollisionHandler()
	{
		m_CollisionList.reserve(MaxCollision);
	}

private:
	CollisionCollection m_CollisionList;
};
