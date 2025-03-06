#ifndef IDENTIFIER_GENERATOR_H
#define IDENTIFIER_GENERATOR_H

namespace Engine
{

using Identifier = int;

template<typename B>
class IdentifierGenerator
{
public:

    // Generate a unique ID for a specific type (e.g., ComponentA, ComponentB)
    template<typename C = B>
    inline static Identifier getTypeID() {
        static Identifier id = generateTypeID();
        return id;
    }

	// Generate a unique ID for each instance (e.g., GameObject1, GameObject2)
    static Identifier getInstanceID() {
        static Identifier id = 0;
        return id++;
    }

private:
    IdentifierGenerator() = delete;
    ~IdentifierGenerator() = delete;

    // This generates unique type-based IDs for different types
    inline static Identifier generateTypeID() {
        static Identifier id = 0;
        return id++;
    }
};

}

#endif 