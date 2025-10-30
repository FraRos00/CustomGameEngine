#pragma once

#include "globals/globals.hpp"
#include <raylib.h>
#include <string>
class Text {
public:
  Text(std::string text, Vector2 position,
       float fontsize = global::fontSizes["h5"], Color textColor = LIGHTGRAY,
       float letterSpacing = 0, Color hoverColor = WHITE,
       Font font = GetFontDefault());

  void Update(const std::string &action);
  void Draw() const;

  std::string getText() const { return text; }

private:
  Vector2 position;
  std::string text;
  Vector2 textMeasure;
  Font font;
  float fontsize;
  float letterSpacing;
  Color textColor;
  Color hoverColor;
  Color activeColor;
};
