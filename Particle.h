#pragma once

#include <functional>

class Particle
{
private:
	int id;
public:
    int getId() const;
};

struct ParticleHash {
    std::size_t operator()(const Particle& particle) const {
        return std::hash<int>()(particle.getId());
    }
};
