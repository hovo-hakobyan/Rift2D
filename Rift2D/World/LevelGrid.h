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
		bool isTileEmpty(int idx);
		bool isTileEmpty(int x, int y) const;
		bool isValidTileIdx(int idx) const;
		bool isValidRow(int row) const;
		bool isValidCol(int col) const;
		int rows() const { return m_rows; }
		int cols() const { return m_cols; }
		GameObject* getOccupant(int x, int y) const;

	private:
		friend class Singleton;
		LevelGrid() = default;

		struct Tile
		{
			bool isEmpty{true};
			GameObject* pOccupant{};
		};

		int m_rows{};
		int m_cols{};
		std::vector<Tile> m_grid{};

		bool isValidTile(int x, int y) const;
		bool m_isInitialized{ false };
	};


}
