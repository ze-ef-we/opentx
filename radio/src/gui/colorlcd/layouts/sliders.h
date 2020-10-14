/*
 * Copyright (C) OpenTX
 *
 * Based on code named
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#pragma once

#include "libopenui.h"

class MainViewSlider : public Window
{
  public:
    MainViewSlider(Window * parent, const rect_t & rect, std::function<int16_t()> getValue):
      Window(parent, rect),
      getValue(std::move(getValue))
    {
    }

    void checkEvents() override
    {
      Window::checkEvents();
      int8_t newValue = getValue();
      if (value != newValue) {
        value = newValue;
        invalidate();
      }
    }

  protected:
    std::function<int16_t()> getValue;
    int8_t value = 0;
};

class MainViewHorizontalSlider : public MainViewSlider
{
  public:
    using MainViewSlider::MainViewSlider;

    void paint(BitmapBuffer * dc) override
    {
      drawHorizontalSlider(dc, 0, 0, width(), getValue(), -RESX, RESX, width() / 5, OPTION_SLIDER_TICKS | OPTION_SLIDER_BIG_TICKS | OPTION_SLIDER_SQUARE_BUTTON);
    }
};

class MainView6POS : public MainViewSlider
{
  public:
    using MainViewSlider::MainViewSlider;

    void paint(BitmapBuffer * dc) override
    {
      drawHorizontalSlider(dc, 0, 0, width(), getValue(), 1, XPOTS_MULTIPOS_COUNT + 1, XPOTS_MULTIPOS_COUNT, OPTION_SLIDER_TICKS |  OPTION_SLIDER_SQUARE_BUTTON);
    }
};

class MainViewVerticalSlider : public MainViewSlider
{
  public:
    using MainViewSlider::MainViewSlider;

    void paint(BitmapBuffer * dc) override
    {
      drawVerticalSlider(dc, 0, 0, height(), getValue(), -RESX, RESX, height() / 5, OPTION_SLIDER_TICKS | OPTION_SLIDER_BIG_TICKS | OPTION_SLIDER_SQUARE_BUTTON);
    }
};