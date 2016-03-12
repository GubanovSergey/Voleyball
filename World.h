#ifndef __WORLD_H_DEFINED_XX__
#define __WORLD_H_DEFINED_XX__

#include <vector>
#include <cstdio>
#include <cassert>
#include <tuple>

namespace World
{
  
class World
{
  typedef GameObject::Object Object_t;

public:
  typedef FILE* LevelSource_t;
  typedef FILE* Log_t;

  typedef std::pair<Object_t*,Object_t*> Collision;

private:  
  // Shall we use smart pointers there?
  std::vector<Object_t*> m_obj;

  Rules::RuleObject* m_rules;

  Log_t m_log;
public:


  World(const World&) = delete;
  World& operator=(const World&) = delete;

  // FILE* or fstream& should be passed as another object
  // that will hide details of level source.
  // Also there is no need to define another function to
  // initialize the world.
  explicit World(LevelSource_t* level);
  void setLog(Log_t log){assert(log);m_log=log;}

  // Timer class should have some type definitions.
  // Return value: true -- game not over
  //               false - game over
  bool update(Timer::timediff_t dt);

  void printLog();
  
  ~World();

private:
  void detectCollisions();
  void handleCollision(const Collision&);
};

} // namespace World

#endif
