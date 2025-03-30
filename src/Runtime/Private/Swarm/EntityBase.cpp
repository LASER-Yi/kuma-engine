#include "Swarm/EntityBase.h"
#include "Swarm/Definition.h"
#include "Swarm/Manager.h"

namespace Swarm
{

FEntityBase::FEntityBase(Swarm::SignatureType InSignature)
    : Signature(InSignature)
{
}

FEntityBase::~FEntityBase() { Swarm::Manager::Get()->RemoveEntity(this); }

Swarm::SignatureType FEntityBase::GetSignature() const { return Signature; }

} // namespace Swarm
