#pragma once
#ifndef TEXT_HPP
#define TEXT_HPP


namespace Fluky {

	class Text {

	public:
		friend class World;

		int Init();

		~Text();

		void Update() noexcept;

	};

}
#endif