#include "noderect.h"
#include <cassert>
NodeRect::NodeRect()
//: m_nodes(NULL)
{
}

void NodeRect::allocateNodes(const int width, const int height)
{
    assert(width > 0 && height > 0);
    m_width = width;
    m_height = height;
    //m_nodes = new Node[m_width * m_height];
	m_nodeParts.allocateNodes(width, height);

}

/*Node**/NodeIdx NodeRect::getNode(const coord_type x, const coord_type y) const
{
//    assert(x < m_width && y < m_height);
//    assert(x >= 0 && y >= 0);
    if(x >= 0 && y >= 0
       && x < m_width && y < m_height)
    {
		//�ֶ����������ĺ�����ʧ�󰡡���
        //return &m_nodes[x * m_height + y];
		//return &m_nodes[y * m_width + x];
		return y * m_width + x;
    }
    return -1;
}

void NodeParts::allocateNodes(const int width, const int height){
	m_xs.allocateNodes(width, height);
	m_ys.allocateNodes(width, height);
	m_isBlocks.allocateNodes(width, height);
	//fs.allocateNodes(width, height);
	gs.allocateNodes(width, height);
	hs.allocateNodes(width, height);
	m_parentIdx.allocateNodes(width, height);
}