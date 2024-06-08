#pragma once
#include <string>
#include <vector>

namespace rift2d
{
	struct ScoreData
	{
		std::string name;
		int score;

		bool operator<(const ScoreData& other) const
		{
			return score > other.score;
		}
	};
	class ScoreSave final
	{
	public:
		explicit ScoreSave(const std::string& fileName);
		~ScoreSave() = default;
		ScoreSave(const ScoreSave& other) = delete;
		ScoreSave(ScoreSave&& other) = delete;
		ScoreSave& operator=(const ScoreSave& other) = delete;
		ScoreSave& operator=(ScoreSave&& other) = delete;

		void update(const std::string& name, int score);
		std::vector<ScoreData> getTopScores(size_t count);

	private:
		std::string m_fileName;
		std::vector<ScoreData> m_scores{};

		void loadScores();
		void saveScores();
	};

}
