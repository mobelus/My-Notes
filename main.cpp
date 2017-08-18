#include <string>
#include <vector>
#include <set>
#include <iostream>


class Tree;
class Node;

class Node
{
public:
	
	Node(Node* _parent, std::string _name)
	{
		m_prev = _parent;
		m_name = _name;
	}

	Node* AddChild(std::string _child_name)
	{
		Node* nd = new Node(this, _child_name);
		m_children.push_back(nd);
		return nd;
	}

	Node* DelChild(std::string _child_name)
	{
		for (auto &vec : m_children)
		{
			if (vec->m_name == _child_name)
			{
				m_children.erase(*vec, (*vec + 1));
				break;
			}
		}
	}

	~Node()
	{
		for (auto &vec : m_children)
			delete(vec);
	}

	//getChildren

private:
	Node* m_prev;
	std::string m_name;
	std::vector<Node*> m_children;
	//node_vec* m_children;

	enum OBJ_TYPE
	{
		OBJ_FOLDER = 0,
		OBJ_FILE,
		OBJ_OTHER,
	};

	friend class Tree;
};

class Tree
{
public:	
	Tree()
	{
		m_Root = new Node(0, ".");
		m_ActiveNode = m_Root;
	}

	~Tree()
	{
		if (m_Root)
			delete m_Root;
	}
///////////////////////
	void setActiveNode(Node* curNode)
	{
		m_ActiveNode = curNode;
	}

	void setActiveNode(std::string strNode)
	{
		m_ActiveNode = getNode(strNode);
	}


	Node* getNode(std::string name)
	{
		for (auto &children : m_ActiveNode->m_children)
		{
			if (children->m_name == name)
			{
				return children;
			}
		}

		return nullptr;
	}

	void goLevelUp() // one level up from current position in tree
	{
		if (m_ActiveNode != m_Root)
		{
			m_ActiveNode = m_ActiveNode->m_prev;
		}
	}

	void AddTreeItem(std::string name)
	{
		m_ActiveNode->AddChild(name);
	}

	void DelTreeItem(std::string name)
	{
		m_ActiveNode->AddChild(name);
	}

	void DelTreePart(std::string name)
	{
		m_ActiveNode->AddChild(name);
	}


///////////////////////
	

	void printTree(Node* node = 0, int lvlCounter = -1)
	{
		lvlCounter++;

		std::string strTab(lvlCounter, '\t');

		Node* tmpNode = node ? node : m_Root;

		if ( !node )
		{
			std::cout << strTab << m_Root->m_name << std::endl;
			printTree(m_Root, lvlCounter);
		}
		else
		{
			for (auto &children : tmpNode->m_children)
			{
				std::cout << strTab << children->m_name << std::endl;
				printTree(children, lvlCounter);
			}
		}
	}


	void printDirOnOneLevel()
	{
		for (auto &children : m_ActiveNode->m_children)
		{
			std::cout << children->m_name << std::endl;
		}
	}

	/*
	void printDirAllLevels()
	{
		for (auto &children : m_ActiveNode->m_children)
		{
			std::cout << children->m_name << std::endl;
		}
	}
	*/


private:
	Node* m_Root;
	Node* m_ActiveNode;
};




int main()
{
	Tree tr;
	tr.AddTreeItem("Dir_1");
	tr.AddTreeItem("Dir_2");
	tr.AddTreeItem("Fl_1.exe");
	tr.AddTreeItem("Fl_2.exe");

	tr.setActiveNode("Dir_2");
	tr.AddTreeItem("Dir_1");
	tr.AddTreeItem("Dir_2");
	tr.AddTreeItem("Fl_1.exe");
	tr.AddTreeItem("Fl_2.exe");


	tr.printTree();
	getchar();
}
