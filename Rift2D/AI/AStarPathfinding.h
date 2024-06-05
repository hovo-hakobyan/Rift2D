#pragma once
#include <deque>
#include <vector>
#include <glm/vec2.hpp>

// Credits https://medium.com/@nicholas.w.swift/easy-a-star-pathfinding-7e6689c7f7b2
namespace rift2d
{
	class LevelGrid;
	struct Node final
	{
		int row;
		int col;
		float fCost;
		float gCost;
		float hCost;
		Node* pParent;

		Node(int row, int col, Node* parent = nullptr)
			:row{row}, col{col}, fCost{0},gCost{0}, hCost{0},pParent{parent} 
		{}

		bool operator==(const Node& other) const
		{
			return row == other.row and col == other.col;
		}

		bool operator<(const Node& other) const
		{
			return std::tie(row, col) < std::tie(other.row, other.col);
		}
	};


	class AStarPathfinding final
	{
	public:
		AStarPathfinding(int rows, int cols);
		~AStarPathfinding() = default;
		AStarPathfinding(const AStarPathfinding& other) = delete;
		AStarPathfinding(AStarPathfinding&& other) = delete;
		AStarPathfinding& operator=(const AStarPathfinding& other) = delete;
		AStarPathfinding& operator=(AStarPathfinding&& other) = delete;

		std::deque<glm::vec2> findPath(const glm::vec2& startPos, const glm::vec2& targetPos);
	private:
		int m_rows{};
		int m_cols{};

		[[nodiscard]] std::vector<Node> getNeighbors(const Node& node) const;
		float distance(int row, int col, int targetRow, int targetCol);

		std::vector<Node*> m_cleanupNodes;
		void cleanupNodes();

	};
}
		