#ifndef IDENTIFIER_GENERATOR_H
#define IDENTIFIER_GENERATOR_H

namespace Engine
{

using Identifier = int;

template<typename>
class IdentifierGenerator
{
public:

	template<typename>
    static Identifier getID() {
		// Generate a unique id for each type
		static Identifier id = generateID();
		return id;
    }

private:
	IdentifierGenerator() = delete;
	~IdentifierGenerator() = delete;

	static Identifier generateID() {
		static Identifier id = 0;
		return id++;
	}

};

}

#endif 