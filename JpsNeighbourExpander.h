#pragma once
#include "NeighbourExpander.h"
#include "astar.h"
#include "map.h"
class Node;
class JpsNeighbourExpander : public NeighbourExpander{
public:
	JpsNeighbourExpander(AStar* holder):NeighbourExpander(holder), ret(8){}
	void expandSuccessors(const Node *node);

protected:
	void findNeighbours(const Node* node);
	Node* jump(Node* node, const Node* parent, const Node* endNode) const;
protected:
	void addNeighbours_Directional_Natural(const coord_type blockx, const coord_type blocky){
		Node* neighbour = m_holder->getMap()->getNode(blockx, blocky);
		if(neighbour && !neighbour->isBlock()){
			pushNode(neighbour);//��������Ȼ�ھӡ�
		}
	}
	void addNeighbours_Directional_Force(const coord_type blockx, const coord_type blocky, const coord_type neighbourx, const coord_type neighboury){
		if(!m_holder->getMap()->isWalkableAt(blockx, blocky)){
			Node* neighbour = m_holder->getMap()->getNode(neighbourx, neighboury);
			if(neighbour && !neighbour->isBlock()){
				pushNode(neighbour);//������ǿ���ھӡ�
			}
		}
	}
	bool addNeighbours_Diagonal_Natural(const coord_type blockx, const coord_type blocky){
		Node* neighbour = m_holder->getMap()->getNode(blockx, blocky);
		if(neighbour && !neighbour->isBlock()){
			pushNode(neighbour);//x,y������Ȼ�ھ�
			return true;
		}
		return false;
	}
	void addNeighbours_Diagonal_DiagonalNatural(const coord_type blockx, const coord_type blocky){
		//addNeighbours_Directional_Natural(blockx, blocky);//������б����Ȼ�ھӡ�
		Node* neighbour = m_holder->getMap()->getNode(blockx, blocky);
		if(neighbour && !neighbour->isBlock()){
			pushNode(neighbour);//x,y������Ȼ�ھ�
			//return true;
		}
	}
	void addNeighbours_Diagonal_Force(const coord_type blockx, const coord_type blocky, const coord_type neighbourx, const coord_type neighboury, bool walkable){
		if(walkable){
			if(!m_holder->getMap()->isWalkableAt(blockx, blocky)){
				Node* neighbour = m_holder->getMap()->getNode(neighbourx, neighboury);
				if(neighbour && !neighbour->isBlock()){
					pushNode(neighbour);//ǿ���ھӡ�
				}
			}
		}
	}
	void pushNode(Node* node){
		ret.push_back(node);
	}
	std::vector<Node*> ret;
};