#include "utils/Text.hpp"
#include <iostream>
#include <raylib.h>
#include <string>

Text::Text(std::string text, Vector2 position, float fontsize, Color textColor,
           float letterSpacing, Color hoverColor, Font font)
    : text(text), font(font), fontsize(fontsize), letterSpacing(letterSpacing),
      textColor(textColor), hoverColor(hoverColor) {

  this->textMeasure =
      MeasureTextEx(font, text.c_str(), fontsize, letterSpacing);
  this->position.x = position.x - this->textMeasure.x / 2.0f;
  this->position.y = position.y - this->textMeasure.y / 2.0f;
  this->activeColor = textColor;
}

void Text::Update(const std::string &action) {
 
}

void Text::Draw() const {
  DrawTextEx(font, text.c_str(), position, fontsize, letterSpacing,
             activeColor);
}
