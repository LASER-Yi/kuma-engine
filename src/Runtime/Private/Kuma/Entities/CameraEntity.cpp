#include "Kuma/Entities/CameraEntity.h"

#include "Kuma/Components/CameraData.h"

FCameraEntity::FCameraEntity(Swarm::FEntityInitializationContext& Context)
    : FKumaEntity(Context)
{
    Context.CreateDefaultComponent<FCameraData>();
}
