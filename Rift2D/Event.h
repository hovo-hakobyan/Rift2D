#pragma once
#include <functional>

namespace rift2d
{
	template<typename ... Args>
	class Event final
	{
		using Delegate = std::function<void(Args...)>;

		void addFunction(Delegate delegate)
		{
			m_delegates.push_back(delegate);
		}

		void broadcast(Args... args)
		{
			for (auto& delegate : m_delegates) delegate(std::forward<Args>(args)...);
			
		}

	private:
		std::vector<Delegate> m_delegates;
	};


}
