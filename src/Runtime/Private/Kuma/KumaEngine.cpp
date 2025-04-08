#include "Kuma/KumaEngine.h"
#include "Engine/Engine.h"
#include "Kuma/Components/Primitive.h"
#include "Kuma/Entities/KumaEntity.h"
#include "Kuma/Entities/KumaWorld.h"
#include "Kuma/Systems/PrimitiveSystem.h"
#include "Swarm/Manager.h"
#include "Vector.h"

void KKumaEngine::Initialize()
{
    KEngine::Initialize();
    Swarm::Manager::Get()->AddSystem<KPrimitiveSystem>();
    CurrentWorld = Swarm::Manager::Get()->MakeEntity<FKumaWorld>();

    std::vector<Math::FVector> Cube;
    {

        // Front
        Cube.push_back({-0.5, -0.5, 0.5});
        Cube.push_back({0.5, -0.5, 0.5});
        Cube.push_back({0.5, 0.5, 0.5});
        Cube.push_back({0.5, 0.5, 0.5});
        Cube.push_back({-0.5, 0.5, 0.5});
        Cube.push_back({-0.5, -0.5, 0.5});

        // Back
        Cube.push_back({0.5, -0.5, -0.5});
        Cube.push_back({-0.5, -0.5, -0.5});
        Cube.push_back({-0.5, 0.5, -0.5});
        Cube.push_back({-0.5, 0.5, -0.5});
        Cube.push_back({0.5, 0.5, -0.5});
        Cube.push_back({0.5, -0.5, -0.5});

        // Top
        Cube.push_back({-0.5, 0.5, 0.5});
        Cube.push_back({0.5, 0.5, 0.5});
        Cube.push_back({0.5, 0.5, -0.5});
        Cube.push_back({0.5, 0.5, -0.5});
        Cube.push_back({-0.5, 0.5, -0.5});
        Cube.push_back({-0.5, 0.5, 0.5});

        // Bottom
        Cube.push_back({-0.5, -0.5, -0.5});
        Cube.push_back({0.5, -0.5, -0.5});
        Cube.push_back({0.5, -0.5, 0.5});
        Cube.push_back({0.5, -0.5, 0.5});
        Cube.push_back({-0.5, -0.5, 0.5});
        Cube.push_back({-0.5, -0.5, -0.5});

        // Left
        Cube.push_back({-0.5, -0.5, -0.5});
        Cube.push_back({-0.5, -0.5, 0.5});
        Cube.push_back({-0.5, 0.5, 0.5});
        Cube.push_back({-0.5, 0.5, 0.5});
        Cube.push_back({-0.5, 0.5, -0.5});
        Cube.push_back({-0.5, -0.5, -0.5});

        // Right
        Cube.push_back({0.5, -0.5, -0.5});
        Cube.push_back({0.5, -0.5, 0.5});
        Cube.push_back({0.5, 0.5, 0.5});
        Cube.push_back({0.5, 0.5, 0.5});
        Cube.push_back({0.5, 0.5, -0.5});
        Cube.push_back({0.5, -0.5, -0.5});
    }

    std::vector<Math::FVector> Color;
    {
        // Front
        Color.push_back({0.5, 0.5, 0.5});
        Color.push_back({0.5, 0.5, 0.5});
        Color.push_back({0.5, 0.5, 0.5});
        Color.push_back({0.5, 0.5, 0.5});
        Color.push_back({0.5, 0.5, 0.5});
        Color.push_back({0.5, 0.5, 0.5});

        // Back
        Color.push_back({1.0, 1.0, 1.0});
        Color.push_back({1.0, 1.0, 1.0});
        Color.push_back({1.0, 1.0, 1.0});
        Color.push_back({1.0, 1.0, 1.0});
        Color.push_back({1.0, 1.0, 1.0});
        Color.push_back({1.0, 1.0, 1.0});

        // Top
        Color.push_back({0.0, 0.0, 0.5});
        Color.push_back({0.0, 0.0, 0.5});
        Color.push_back({0.0, 0.0, 0.5});
        Color.push_back({0.0, 0.0, 0.5});
        Color.push_back({0.0, 0.0, 0.5});
        Color.push_back({0.0, 0.0, 0.5});

        // Bottom
        Color.push_back({0.0, 0.5, 0.5});
        Color.push_back({0.0, 0.5, 0.5});
        Color.push_back({0.0, 0.5, 0.5});
        Color.push_back({0.0, 0.5, 0.5});
        Color.push_back({0.0, 0.5, 0.5});
        Color.push_back({0.0, 0.5, 0.5});

        // Left
        Color.push_back({0.5, 0.0, 0.0});
        Color.push_back({0.5, 0.0, 0.0});
        Color.push_back({0.5, 0.0, 0.0});
        Color.push_back({0.5, 0.0, 0.0});
        Color.push_back({0.5, 0.0, 0.0});
        Color.push_back({0.5, 0.0, 0.0});

        // Right
        Color.push_back({0.0, 0.5, 0.0});
        Color.push_back({0.0, 0.5, 0.0});
        Color.push_back({0.0, 0.5, 0.0});
        Color.push_back({0.0, 0.5, 0.0});
        Color.push_back({0.0, 0.5, 0.0});
        Color.push_back({0.0, 0.5, 0.0});
    }

    auto Entity = Swarm::Manager::Get()->MakeEntity<FKumaEntity>();
    Entity->AddComponent<FPrimitiveComponent>(Cube, Color);

    CurrentWorld->AddToWorld(Entity);

    // for (auto& AnotherVertex : Vertex)
    // {
    //     AnotherVertex.X -= 0.6;
    // }

    // auto AnotherEntity = Swarm::Manager::Get()->MakeEntity<FKumaEntity>();
    // AnotherEntity->AddComponent<FPrimitiveComponent>(Vertex);

    // CurrentWorld->AddToWorld(AnotherEntity);
}

void KKumaEngine::Shutdown()
{
    CurrentWorld = nullptr;

    KEngine::Shutdown();
}
