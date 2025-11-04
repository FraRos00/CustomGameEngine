#include "entities/EntityManager.hpp"

void EntityManager::AddEntity(std::unique_ptr<Entity> entity) {
  entities.push_back(std::move(entity));
}

void EntityManager::UpdateAll(float dt) {
  for (auto &entity : entities) {
    entity->Update(dt);
  }
}

void EntityManager::DrawAll() const {
  for (const auto &entity : entities) {
    entity->Draw();
  }
}

void EntityManager::HandleMapCollisions(Map &map){
  for(auto &entity : entities){

    Hitbox hitbox = entity->GetHitbox();
    Vector2 position = entity->GetNextPosition();
    float offsetX = hitbox.width/2.0f;
    float offsetY = hitbox.height/2.0f;
    Rectangle recHitbox{
    position.x-offsetX, position.y-offsetY,
    hitbox.width,hitbox.height};

    if(!map.CheckCollision(recHitbox)){
        entity->SetPosition(position);
    }
}

}

void EntityManager::Clear() { entities.clear(); }
