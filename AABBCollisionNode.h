#pragma once

class AABBCollisionNode
{
public:
	AABBCollisionNode();
	~AABBCollisionNode();

private:
	/*
	  1------2
	 / |    /|
	/  |   / |
	5-----4  |
	|  0--|--3
	| /   | /
	|/    |/
	6-----7
	*/
	D3DXVECTOR2 min, max;

	friend class AABBTreeCollider;
};
