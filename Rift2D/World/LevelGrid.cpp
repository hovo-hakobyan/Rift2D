#include "LevelGrid.h"
#include "GameObject.h"
#include "Exception.h"
#include "Settings.h"
#include "Utils.h"

void rift2d::LevelGrid::setup(int rows, int cols)
{
	m_rows = rows;
	m_cols = cols;
	m_grid.clear();
	m_grid.resize(static_cast<size_t>( m_rows) * m_cols);
	m_isInitialized = true;
}

void rift2d::LevelGrid::setTile(int x, int y, bool empty, GameObject* occupant)
{
	if (!m_isInitialized) return;
	if(!isValidTile(x, y)) THROW_RIFT_EXCEPTION("Invalid tile", RiftExceptionType::Error);

	const int idx = Utils::indexFromPosition(x, y, m_cols);
	m_grid[idx].isEmpty = empty;
	m_grid[idx].pOccupant = occupant;
}

bool rift2d::LevelGrid::isTileEmpty(int idx)
{
	if (idx >= m_grid.size()) return false;
	if (static_cast<size_t>(idx) >= m_grid.size()) THROW_RIFT_EXCEPTION("Invalid tile", RiftExceptionType::Error);
	return m_grid[idx].isEmpty;
}

bool rift2d::LevelGrid::isTileEmpty(int x, int y) const
{
	if (!isValidTile(x, y)) THROW_RIFT_EXCEPTION("Invalid tile", RiftExceptionType::Error);

	const int idx = Utils::indexFromPosition(x, y, m_cols);
	return m_grid[idx].isEmpty;
	
}

rift2d::GameObject* rift2d::LevelGrid::getOccupant(int x, int y) const
{
	if (!m_isInitialized) return nullptr;
	if (!isValidTile(x, y)) THROW_RIFT_EXCEPTION("Invalid tile", RiftExceptionType::Error);

	const int idx = Utils::indexFromPosition(x, y, m_cols);
	return m_grid[idx].pOccupant;
	
}

bool rift2d::LevelGrid::isValidTile(int x, int y) const
{
	if (m_grid.empty()) return false;
	if (x >= 0 && x < settings::WINDOW_WIDTH && y >= 0 && y < settings::WINDOW_HEIGHT) return true;
	return false;
}
