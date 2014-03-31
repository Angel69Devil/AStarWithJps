#pragma once

#include "astar.h"
#include "map.h"
class AStarWithJps : public AStar
{
protected:
	void expandSuccessors(const Node* node);//����û��ʹ���麯������Ҫ�������ܲ������ִ�е���
	void findNeighbours(const Node* node);
	Node* jump(Node* node, const Node* parent, const Node* endNode) const;
protected:
	void addNeighbours_Directional_Natural(const int blockx, const int blocky){
		Node* neighbour = m_map->getNode(blockx, blocky);
		if(!neighbour->isBlock()){
			ret.push_back(neighbour);//��������Ȼ�ھӡ�
		}
	}
	void addNeighbours_Directional_Force(const int blockx, const int blocky, const int neighbourx, const int neighboury){
		if(m_map->isWalkableAt(blockx, blocky)){
			Node* neighbour = m_map->getNode(neighbourx, neighboury);
			ret.push_back(neighbour);//������ǿ���ھӡ�
		}
	}
	bool addNeighbours_Diagonal_Natural(const int blockx, const int blocky){
		Node* neighbour = m_map->getNode(blockx, blocky);
		if(!neighbour->isBlock()){
			ret.push_back(neighbour);//x,y������Ȼ�ھ�
			return true;
		}
		return false;
	}
	void addNeighbours_Diagonal_DiagonalNatural(const int blockx, const int blocky){
		addNeighbours_Directional_Natural(blockx, blocky);//������б����Ȼ�ھӡ�
	}
	void addNeighbours_Diagonal_Force(const int blockx, const int blocky, const int neighbourx, const int neighboury, bool walkable){
		if(walkable){
			if(m_map->isWalkableAt(blockx, blocky)){
				Node* neighbour = m_map->getNode(neighbourx, neighboury);
				ret.push_back(neighbour);//ǿ���ھӡ�
			}
		}
	}
	std::vector<Node*> ret;

};