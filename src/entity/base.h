#ifndef WINDFALL_ENTITY_BASE_H_
#define WINDFALL_ENTITY_BASE_H_

#include "graphics/texture.h"
#include "math/vector.h"

namespace windfall::entity::base {

namespace impl {

namespace texture = windfall::graphics::texture;
namespace vector = windfall::math::vector;

}  // namespace impl

struct Positional {
    impl::vector::Vector2D r;  // Position     / px
    impl::vector::Vector2D v;  // Velocity     / px s-1
    impl::vector::Vector2D a;  // Acceleration / px s-2

    impl::vector::Vector2D f;  // Sum of external forces / kg px s-2

    Positional() = default;
};

struct PhysicalProperty {
    float mass;  // kg
    float drag_factor;

    PhysicalProperty() = default;
    PhysicalProperty(float mass, float drag_factor)
        : mass(mass), drag_factor(drag_factor) {}
    PhysicalProperty(const PhysicalProperty&) = default;
};

class BaseEntity {
public:
    explicit BaseEntity(const PhysicalProperty& phys) : phys_(phys) {}
    virtual ~BaseEntity() = default;

    impl::vector::Vector2D CalcGravity(const impl::vector::Vector2D& g) const;
    impl::vector::Vector2D CalcDrag(float fluid_factor) const;

    void AddForce(const impl::vector::Vector2D& force);

    void UpdateA();
    void UpdateV(float dt);
    void UpdateR(float dt);

    void RenderDebugInfo(const impl::texture::Texture& target) const;

private:
    Positional pos_;
    PhysicalProperty phys_;
};

}  // namespace windfall::entity::base

#endif  // WINDFALL_ENTITY_BASE_H_
