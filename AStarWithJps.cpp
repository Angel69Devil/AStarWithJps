#include "AStarWithJps.h"
#include <cmath>
#include <algorithm>
#include <cassert>
//jps�㷨����Ҫ������A*��open��ĳ��ȡ��μ���
//http://users.cecs.anu.edu.au/~dharabor/data/papers/harabor-grastien-aaai11.pdf
//ԭ���߹�����http://harablog.wordpress.com/2011/09/07/jump-point-search/
//���İ���ͣ�http://plusplus7.com/lemonbag/jpsstudy
//Ӣ�İ���ͣ��Ƽ���http://zerowidth.com/2013/05/05/jump-point-search-explained.html
//LuaԴ����ο���https://github.com/Yonaba/Jumper
void AStarWithJps::expandSuccessors(const NodeSavingF* node){
	findNeighbours(node);
	//��������
	for(std::vector<NodeSavingF*>::reverse_iterator it = ret.rbegin(); it != ret.rend(); ++it){
		bool skip = false;
		NodeSavingF* neighbour = *it;
		NodeSavingF* jumpNode = jump(neighbour, node, m_end);
		if(jumpNode){
			insertNodeToOpen(jumpNode, node);
		}
	}
}
void AStarWithJps::findNeighbours(const NodeSavingF* node){
	if(node->getParent() == NULL){//û�и��ڵ㣬һ����˵��ֻ��������Ϊ����nodeΪstart�ڵ�
		AStar::expandSuccessors(node);//��ô��ʹ�ø����expandSuccessors�Ϳ�����
	}
	const int x = node->getX();
	const int y = node->getY();//�����Լ������ꡣ

	const int ddx = x - node->getParent()->getX();
	assert(std::abs(ddx) <= 1);
	const int dx = ddx;//; / std::max(std::abs(ddx), 1);//���ǵĳ����У��ھ����Ǹ����ĸ��ڵ���1��1����
	const int ddy = y - node->getParent()->getY();
	assert(std::abs(ddy) <= 1);
	const int dy = ddy;

	assert(dx != 0 || dy != 0);//�ھ�

	if(dx != 0 && dy != 0){//б�߷���
		//��Ȼ�ھ�
		bool walkY = addNeighbours_Diagonal_Natural(x, y+dy);
		bool walkX = addNeighbours_Diagonal_Natural(x+dx, y);
		if(walkX || walkY){
			ret.push_back(m_map->getNode(x+dx, y+dy));//ԭ�㷨����û���ж���û���赲����֪��Ϊʲô��
			//addNeighbours_Diagonal_DiagonalNatural(x+dx, y+dy);��������Ϊ�ģ���Ҫ�ж��赲�Ĳ�������ע�͵����Ժ󿴿���û����
		}
		//ǿ���ھ�
		addNeighbours_Diagonal_Force(x-dx, y, x-dx, y+dy, walkY);
		addNeighbours_Diagonal_Force(x, y-dy, x+dx, y-dy, walkY);
	}
	else{
		if(dx != 0){//x����
			//��Ȼ�ھ�
			addNeighbours_Directional_Natural(x + dx, y);
			//������û��ǿ���ھӡ�
			addNeighbours_Directional_Force(x, y+1, x+dx, y+1);
			addNeighbours_Directional_Force(x, y-1, x+dx, y-1);
		}
		else{//y����
			assert(dy != 0);
			//��Ȼ�ھ�
			addNeighbours_Directional_Natural(x, y + dy);
			//������û��ǿ���ھӡ�
			addNeighbours_Directional_Force(x+1, y, x+1, y+dy);
			addNeighbours_Directional_Force(x-1, y, x-1, y+dy);
		}
	}
}
NodeSavingF* AStarWithJps::jump(NodeSavingF* node, const NodeSavingF* parent, const NodeSavingF* endNode) const
{
	if( node == NULL || node->isBlock())//������ڵ㲻���ڻ������赲�㣬�Ͳ�����
		return NULL;

	const int x = node->getX();
	const int y = node->getY();//�����Լ������ꡣ

	const int dx = x - node->getParent()->getX();
	const int dy = y - node->getParent()->getY();
	
	/*if(!m_map->isWalkableAt(x,y){//�ٿ�ͷ�Ѿ��жϹ���
		return NULL;
	}*/
	if(node == endNode){//������ֹ�ڵ㣬ֹͣ����
		return node;
	}
	if(dx != 0 && dy != 0){//б��
		//���ڵ������㣬������ҷ����ھ���ǿ���ھӣ�����һ���ǾͿ����ˣ�
		if(m_map->isWalkableAt(x-dx, y+dy) && !m_map->isWalkableAt(x-dx, y)
		|| m_map->isWalkableAt(x+dx, y-dy) && !m_map->isWalkableAt(x, y-dy)
		){
			return node;
		}
	}
	else{
		if(dx != 0){//x����
			//����2���ھ���һ����ǿ���ھӣ���˽ڵ�Ϊ����
			if(m_map->isWalkableAt(x+dx, y+1) && !m_map->isWalkableAt(x, y+1)
			|| m_map->isWalkableAt(x+dx, y-1) && !m_map->isWalkableAt(x, y-1)
				){
				return node;
			}
		}
		else{//y����
			//����2���ھ���һ����ǿ���ھӣ���˽ڵ�Ϊ����
			if(m_map->isWalkableAt(x+1, y+dy) && !m_map->isWalkableAt(x+1, y)
			|| m_map->isWalkableAt(x-1, y+dy) && !m_map->isWalkableAt(x-1, y)
				){
				return node;
			}
		}
	}
	//б��Ļ�����Ҫ�ݹ���ֱ��ڵ��ǲ�������
	if(dx != 0 && dy != 0){//б��	
		if(jump(m_map->getNode(x+dx, y), node, endNode) != NULL){
			return node;//ע�⣬���صĲ��ǵݹ��������ĵ㣬�����Լ�
		}
		if(jump(m_map->getNode(x, y+dy), node, endNode) != NULL){
			return node;//ע�⣬���صĲ��ǵݹ��������ĵ㣬�����Լ�
		}
	}
	//�ݹ�б������
	if(m_map->isWalkableAt(x+dx, y) || m_map->isWalkableAt(x, y+dy)){
		return jump(m_map->getNode(x+dx, y+dy), node, endNode);
	}
	//ʲôҲû���ҵ������ش���
	return NULL;
}