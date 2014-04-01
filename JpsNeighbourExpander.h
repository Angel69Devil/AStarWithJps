#pragma once
#include "NeighbourExpander.h"
#include "astar.h"
#include "map.h"
class Node;
class JpsNeighbourExpander : public NeighbourExpander{
public:
	JpsNeighbourExpander(AStar* holder):NeighbourExpander(holder), ret(8){}
	void expandSuccessors(const NodeSavingF* node);

protected:
	void findNeighbours(const NodeSavingF* node);
	NodeSavingF* jump(NodeSavingF* node, const NodeSavingF* parent, const NodeSavingF* endNode) const;
protected:
	void addNeighbours_Directional_Natural(const int blockx, const int blocky){
		NodeSavingF* neighbour = m_holder->getMap()->getNode(blockx, blocky);
		if(neighbour && !neighbour->isBlock()){
			pushNode(neighbour);//��������Ȼ�ھӡ�
		}
	}
	void addNeighbours_Directional_Force(const int blockx, const int blocky, const int neighbourx, const int neighboury){
		if(!m_holder->getMap()->isWalkableAt(blockx, blocky)){
			NodeSavingF* neighbour = m_holder->getMap()->getNode(neighbourx, neighboury);
			if(neighbour && !neighbour->isBlock()){
				pushNode(neighbour);//������ǿ���ھӡ�
			}
		}
	}
	bool addNeighbours_Diagonal_Natural(const int blockx, const int blocky){
		NodeSavingF* neighbour = m_holder->getMap()->getNode(blockx, blocky);
		if(neighbour && !neighbour->isBlock()){
			pushNode(neighbour);//x,y������Ȼ�ھ�
			return true;
		}
		return false;
	}
	void addNeighbours_Diagonal_DiagonalNatural(const int blockx, const int blocky){
		//addNeighbours_Directional_Natural(blockx, blocky);//������б����Ȼ�ھӡ�
		NodeSavingF* neighbour = m_holder->getMap()->getNode(blockx, blocky);
		if(neighbour && !neighbour->isBlock()){
			pushNode(neighbour);//x,y������Ȼ�ھ�
			//return true;
		}
	}
	void addNeighbours_Diagonal_Force(const int blockx, const int blocky, const int neighbourx, const int neighboury, bool walkable){
		if(walkable){
			if(!m_holder->getMap()->isWalkableAt(blockx, blocky)){
				NodeSavingF* neighbour = m_holder->getMap()->getNode(neighbourx, neighboury);
				if(neighbour && !neighbour->isBlock()){
					pushNode(neighbour);//ǿ���ھӡ�
				}
			}
		}
	}
	void pushNode(NodeSavingF* node){
		ret.push_back(node);
	}
	std::vector<NodeSavingF*> ret;
};