#include "ScoreSave.h"

#include <filesystem>

#include "Exception.h"
#include "Rift2DEngine.h"

rift2d::ScoreSave::ScoreSave(const std::string& fileName):
m_fileName(fileName)
{
}

void rift2d::ScoreSave::update(const std::string& name, int score)
{
	if (name.empty()) return;
	loadScores();

	auto it = std::find_if(m_scores.begin(), m_scores.end(), [&name](const ScoreData& data)
		{
			return data.name == name;
		});

	if(it != m_scores.end())
	{
		if (score > it->score) it->score = score;
	}
	else
	{
		m_scores.push_back({ name,score });
	}

	saveScores();
}

std::vector<rift2d::ScoreData> rift2d::ScoreSave::getTopScores(size_t count)
{
	loadScores();
	std::sort(m_scores.begin(), m_scores.end());
	if(m_scores.size() > count)
	{
		return std::vector<ScoreData>(m_scores.begin(), m_scores.begin() + count);
	}

	return m_scores;
}

void rift2d::ScoreSave::loadScores()
{
	m_scores.clear();

	const std::filesystem::path directoryPath = Rift2DEngine::getDataPath();
	const bool dirCreated = create_directories(directoryPath);
	if (!dirCreated && !exists(directoryPath))
	{
		THROW_RIFT_EXCEPTION("Save file directory doesn't exist", RiftExceptionType::Error);
	}

	const std::filesystem::path fullPath = directoryPath / m_fileName;
	std::ifstream file(fullPath.string(), std::ios::binary);
	if (!file.is_open()) return;

	size_t size;
	file.read(reinterpret_cast<char*>(&size), sizeof(size));

	m_scores.resize(size);
	for(auto& scoreData : m_scores)
	{
		size_t nameLength;
		file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

		scoreData.name.resize(nameLength);
		file.read(&scoreData.name[0], nameLength);
		file.read(reinterpret_cast<char*>(&scoreData.score), sizeof(scoreData.score));
	}

	file.close();
}

void rift2d::ScoreSave::saveScores()
{
	const std::filesystem::path directoryPath = Rift2DEngine::getDataPath();
	const bool dirCreated = create_directories(directoryPath);
	if (!dirCreated && !exists(directoryPath))
	{
		THROW_RIFT_EXCEPTION("Save file directory doesn't exist", RiftExceptionType::Error);
	}

	const std::filesystem::path fullPath = directoryPath / m_fileName;
	std::ofstream file(fullPath.string(), std::ios::binary);
	if (!file.is_open()) return;

	size_t size = m_scores.size();
	file.write(reinterpret_cast<const char*>(&size), sizeof(size));

	for(const auto& scoreData : m_scores)
	{
		size_t nameLength = scoreData.name.size();
		file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
		file.write(scoreData.name.c_str(), nameLength);
		file.write(reinterpret_cast<const char*>(&scoreData.score), sizeof(scoreData.score));
	}

	file.close();
}


