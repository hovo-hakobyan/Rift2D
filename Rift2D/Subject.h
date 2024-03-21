#pragma once
#include <functional>

namespace rift2d
{
	template<typename ... Args>
	class Subject final
	{
		public:
		using CallbackFunction = std::function<void(Args...)>;
		using Observer = std::pair<unsigned int, CallbackFunction>;
		using ObserverId = unsigned int;

		ObserverId subscribe(CallbackFunction function)
		{
			ObserverId id = nextId++;
			m_observers.push_back({id,function});
			return id;
		}

		void unsubscribe(ObserverId id)
		{
			auto it = std::remove_if(m_observers.begin(), m_observers.end(),
				[id](const Observer& observer)
				{
					return observer.first == id;
				});

			m_observers.erase(it, m_observers.end());
		}

		void notify(Args... args)
		{
			for (auto& observer : m_observers) observer.second(std::forward<Args>(args)...);
			
		}

	private:
		std::vector<Observer> m_observers;
		ObserverId nextId{ 0 };
	};


}
