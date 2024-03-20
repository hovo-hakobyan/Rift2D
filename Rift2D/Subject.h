#pragma once
#include <functional>

namespace rift2d
{
	template<typename ... Args>
	class Subject final
	{
		public:

		using CallbackFunction = std::function<void(Args...)>;

		void subscribe(CallbackFunction function)
		{
			m_observers.push_back(function);
		}

		void notify(Args... args)
		{
			for (auto& observer : m_observers) observer(std::forward<Args>(args)...);
			
		}

	private:
		std::vector<CallbackFunction> m_observers;
	};


}
