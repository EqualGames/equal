#ifndef EQUAL_TAGCOMPONENT_H
#define EQUAL_TAGCOMPONENT_H

struct TagComponent {
  std::string name{"unknown"};

  TagComponent() = default;

  TagComponent(const std::string &name) : name(name) {}
};

#endif // EQUAL_TAGCOMPONENT_H
