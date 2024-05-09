#pragma once
#include <vector>

#include "Singleton.h"


namespace rift2d
{
	class GameObject;
	class LevelGrid final : public Singleton<LevelGrid>
	{
	public:
		~LevelGrid() override = default;
		LevelGrid(const LevelGrid& other) = delete;
		LevelGrid(LevelGrid&& other) noexcept = delete;
		LevelGrid& operator=(const LevelGrid& other) = delete;
		LevelGrid& operator=(LevelGrid&& other) noexcept = delete;
		
		void setup(int rows, int cols);
		void setTile(int x, int y, bool empty, GameObject* occupant = nullptr);
		bool isTileEmpty(int x, int y) const;
		GameObject* getOccupant(int x, int y) const;
	private:
		friend class Singleton;
		LevelGrid() = default;

		struct Tile
		{
			bool isEmpty{};
			GameObject* pOccupant{};
		};

		int m_rows{};
		int m_cols{};
		std::vector<Tile> m_grid{};

		bool isValidTile(int x, int y) const;
	};


}
