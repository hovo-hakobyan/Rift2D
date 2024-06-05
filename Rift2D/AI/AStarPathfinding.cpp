#include "AStarPathfinding.h"
#include <iostream>
#include <set>
#include "LevelGrid.h"
#include "Utils.h"

namespace rift2d
{
	AStarPathfinding::AStarPathfinding(int rows, int cols):
	m_rows(rows), m_cols(cols)
	{
	}

	std::deque<glm::vec2> AStarPathfinding::findPath(const glm::vec2& startPos, const glm::vec2& targetPos)
	{
		std::vector<Node> openList;
		std::set<Node> closedList;
		const auto [startRow, startCol] = Utils::getRowColIdx(startPos);
		const auto [endRow, endCol] = Utils::getRowColIdx(targetPos);

		const Node startNode{ startRow,startCol };
		const Node endNode{ endRow,endCol };
		openList.push_back(startNode);

		while (not openList.empty())
		{
			auto currentNodeIter = std::min_element(openList.begin(), openList.end());
			Node currentNode = *currentNodeIter;
			openList.erase(currentNodeIter);
			closedList.insert(currentNode);

			if(currentNode == endNode)
			{
				std::deque<glm::vec2> path;
				Node* pathNode = &currentNode;

				while (pathNode != nullptr)
				{
					path.push_front(Utils::positionFromRowCol(pathNode->row, pathNode->col));
					pathNode = pathNode->pParent;
					
				}
				path.pop_front();
				cleanupNodes();
				return path;
			}

			std::vector<Node> neighbors = getNeighbors(currentNode);
			for(auto& neighbor : neighbors)
			{
				if (closedList.find(neighbor) != closedList.end()) continue;

				neighbor.gCost = currentNode.gCost + distance(currentNode.row, currentNode.col, neighbor.row, neighbor.col);

				auto openNode = std::find(openList.begin(), openList.end(), neighbor);
				if (openNode != openList.end() and neighbor.gCost >= openNode->gCost) continue;

				neighbor.hCost = distance(neighbor.row, neighbor.col, endNode.row, endNode.col);
				neighbor.fCost = neighbor.gCost + neighbor.hCost;
				neighbor.pParent = new Node(currentNode);
				m_cleanupNodes.push_back(neighbor.pParent);

				openList.push_back(neighbor);
			}

		}

		cleanupNodes();
		return {};

	}

	std::vector<Node> AStarPathfinding::getNeighbors(const Node& node) const
	{
		std::vector<Node> neighbors;
		int deltas[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
		auto& levelGrid = LevelGrid::GetInstance();

		for(const auto& delta : deltas)
		{
			const int newRow = node.row + delta[0];
			const int newCol = node.col + delta[1];
			const int idx = Utils::indexFromRowsCols(newRow, newCol, m_cols);


			if (!levelGrid.isValidTileIdx(idx)) continue;
			if (!levelGrid.isTileEmpty(idx)) continue;

			neighbors.emplace_back(newRow,newCol);
		}

		return neighbors;
	}

	float AStarPathfinding::distance(int row, int col, int targetRow, int targetCol)
	{
		return static_cast<float>(std::abs(row - targetRow) + std::abs(col - targetCol));
	}

	void AStarPathfinding::cleanupNodes()
	{
		for (auto nodePtr : m_cleanupNodes)
		{
			delete nodePtr;
		}
		m_cleanupNodes.clear();
	}
}
