#include "Component.h"

void Component::SetTransform(Transform * t)
{
	m_Transform = t;
}


const Transform * Component::GetTransform() const
{
	return m_Transform;
}

Transform* Component::GetTransform()
{
	return m_Transform;
}
