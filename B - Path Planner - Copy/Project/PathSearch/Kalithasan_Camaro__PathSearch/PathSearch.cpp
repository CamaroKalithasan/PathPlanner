#include "PathSearch.h"

namespace fullsail_ai { namespace algorithms {

	PathSearch::PathSearch()
	{

	}

	PathSearch::~PathSearch()
	{
	}

	void PathSearch::initialize(TileMap* _tileMap)
	{
		tileMap = _tileMap;
		
		for (int i = 0; i < tileMap->getColumnCount(); i++)
		{
			for (int j = 0; j < tileMap->getRowCount(); j++)
			{
				SearchNode* point = new SearchNode();
				point->tile = tileMap->getTile(i, j);
				nodes[point->tile] = point;
			}

		}
		//for (int x = 0; x < nodes.size(); x++)
		////for(auto currentNode = nodes.begin(); currentNode != nodes.end(); currentNode++)
		//{
		//	Tile* tileN;

		//	tileN = tileMap->getTile(tileMap->getRowCount(), tileMap->getColumnCount());

		//}
		for (int x = 0; x < tileMap->getColumnCount(); x++)
		{
			for (int y = 0; y < tileMap->getRowCount(); y++)
			{
				//even
				if (tileMap->getTile(y, x)->getRow() % 2 == 0)
				{
					//left
					if (tileMap->getTile(y, x - 1) != nullptr && tileMap->getTile(y, x - 1)->getWeight() != 0)
					{
						nodes.find(tileMap->getTile(y, x))->second->neighbors.push_back(nodes.find(tileMap->getTile(y, x - 1))->second);
					}
					//right
					if (tileMap->getTile(y, x + 1) != nullptr && tileMap->getTile(y, x + 1)->getWeight() != 0)
					{
						nodes.find(tileMap->getTile(y, x))->second->neighbors.push_back(nodes.find(tileMap->getTile(y, x + 1))->second);
					}
					//top right
					if (tileMap->getTile(y + 1, x) != nullptr && tileMap->getTile(y + 1, x)->getWeight() != 0)
					{
						nodes.find(tileMap->getTile(y, x))->second->neighbors.push_back(nodes.find(tileMap->getTile(y + 1, x))->second);
					}
					//bot right
					if (tileMap->getTile(y - 1, x) != nullptr && tileMap->getTile(y - 1, x)->getWeight() != 0)
					{
						nodes.find(tileMap->getTile(y, x))->second->neighbors.push_back(nodes.find(tileMap->getTile(y - 1, x))->second);
					}
					//top left
					if (tileMap->getTile(y + 1, x - 1) != nullptr && tileMap->getTile(y + 1, x - 1)->getWeight() != 0)
					{
						nodes.find(tileMap->getTile(y, x))->second->neighbors.push_back(nodes.find(tileMap->getTile(y + 1, x - 1))->second);
					}
					//bot left
					if (tileMap->getTile(y - 1, x - 1) != nullptr && tileMap->getTile(y - 1, x - 1)->getWeight() != 0)
					{
						nodes.find(tileMap->getTile(y, x))->second->neighbors.push_back(nodes.find(tileMap->getTile(y - 1, x - 1))->second);
					}
				}

				//odd
				else
				{
					//left
					if (tileMap->getTile(y, x - 1) != nullptr && tileMap->getTile(y, x - 1)->getWeight() != 0)
					{
						nodes.find(tileMap->getTile(y, x))->second->neighbors.push_back(nodes.find(tileMap->getTile(y, x - 1))->second);
					}
					//right
					if (tileMap->getTile(y, x + 1) != nullptr && tileMap->getTile(y, x + 1)->getWeight() != 0)
					{
						nodes.find(tileMap->getTile(y, x))->second->neighbors.push_back(nodes.find(tileMap->getTile(y, x + 1))->second);
					}
					//top right
					if (tileMap->getTile(y + 1, x + 1) != nullptr && tileMap->getTile(y + 1, x + 1)->getWeight() != 0)
					{
						nodes.find(tileMap->getTile(y, x))->second->neighbors.push_back(nodes.find(tileMap->getTile(y + 1, x + 1))->second);
					}
					//bot right
					if (tileMap->getTile(y - 1, x + 1) != nullptr && tileMap->getTile(y - 1, x + 1)->getWeight() != 0)
					{
						nodes.find(tileMap->getTile(y, x))->second->neighbors.push_back(nodes.find(tileMap->getTile(y - 1, x + 1))->second);
					}
					//top left
					if (tileMap->getTile(y + 1, x) != nullptr && tileMap->getTile(y + 1, x)->getWeight() != 0)
					{
						nodes.find(tileMap->getTile(y, x))->second->neighbors.push_back(nodes.find(tileMap->getTile(y + 1, x))->second);
					}
					//bot left
					if (tileMap->getTile(y - 1, x) != nullptr && tileMap->getTile(y - 1, x)->getWeight() != 0)
					{
						nodes.find(tileMap->getTile(y, x))->second->neighbors.push_back(nodes.find(tileMap->getTile(y - 1, x))->second);
					}
				}
			}
		}

		//for (auto &currentNode : nodes)
		//{
		//	Tile* tileCurrent = currentNode.second->tile;
		//	if (currentNode )
		//	{
		//		
		//	}
		//}
	}

	void PathSearch::enter(int startRow, int startColumn, int goalRow, int goalColumn)
	{
		PlannerNode* starter = new PlannerNode();
		starter->searchNode = nodes[tileMap->getTile(startRow, startColumn)];
		starter->parent = nullptr;
		visited[starter->searchNode] = starter;
		prioQueue.push(starter);
		this->start = starter;
		PlannerNode* ender = new PlannerNode();
		ender->searchNode = nodes[tileMap->getTile(goalRow, goalColumn)];
		ender->parent = nullptr;
		this->end = ender;
	}

	float PathSearch::Distance(SearchNode* x, SearchNode* y)
	{
		return sqrt(pow(x->tile->getXCoordinate() - y->tile->getXCoordinate(), 2) + pow(x->tile->getYCoordinate() - y->tile->getYCoordinate(), 2) * 1.0);
	}

	void PathSearch::update(long timeslice)
	{
		while (!prioQueue.empty())
		{
			PlannerNode* planTemp = prioQueue.front();
			prioQueue.pop();
			planTemp->searchNode->tile->setFill(0xFFFF8080);
			if (planTemp->searchNode == end->searchNode)
			{
				prioQueue.clear();
				delete end;
				end = planTemp;
				break;
			}
			for (int i = 0; i < planTemp->searchNode->neighbors.size(); i++)
			{
				SearchNode* success = planTemp->searchNode->neighbors[i];
				float tempGivenCost = planTemp->givenCost + (Distance(success, planTemp->searchNode) * success->tile->getWeight());
				if (visited[success] != NULL)
				{
					if (tempGivenCost < visited[success]->givenCost)
					{
						prioQueue.remove(visited[success]);
						visited[success]->givenCost = tempGivenCost;
						visited[success]->finalCost = visited[success]->givenCost + visited[success]->huerCost * 1.2f;
						visited[success]->parent = planTemp;
						prioQueue.push(visited[success]);
					}
				}
				else
				{
					PlannerNode* successNode = new PlannerNode();
					successNode->searchNode = success;
					successNode->huerCost = Distance(end->searchNode, success);
					successNode->givenCost = tempGivenCost;
					successNode->finalCost = successNode->givenCost + successNode->huerCost * 1.2f;
					successNode->parent = planTemp;
					prioQueue.push(successNode);
					visited[success] = successNode;
				}
			}
			if (timeslice == 0)
			{
				break;
			}
		}
	}

	void PathSearch::exit()
	{
		for (int i = 0; i < visited.size(); i++)
		{
			visited.clear();
			prioQueue.clear();
		}
	}

	void PathSearch::shutdown()
	{
		nodes.clear();
	}

	bool PathSearch::isDone() const
	{
		if (prioQueue.empty())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	std::vector<Tile const*> const PathSearch::getSolution() const
	{
		std::vector<Tile const*> temp;
		for (PlannerNode* plan = end; plan != nullptr; plan = plan->parent)
		{
			temp.push_back(plan->searchNode->tile);
		}
		return temp;
	}
}}  // namespace fullsail_ai::algorithms

