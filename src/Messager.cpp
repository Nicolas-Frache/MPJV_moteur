#pragma once
class Messager {
public:
  void sendCollisionMessage() {
    collisionDetected = true;
  }

  bool consumeCollisionMessage() {
    bool tmp = collisionDetected;
    collisionDetected = false;
    return tmp;
  }

private:
  bool collisionDetected = false;
};