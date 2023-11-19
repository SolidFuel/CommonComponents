/****
 * Chantool - Versatile VST3 Channel Utility for Digital Audio Workstations 
 * Copyright (C) 2023 Solid Fuel
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version. This program is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the LICENSE file
 * in the root directory.
 ****/

#include "ButtonGroupComponent.hpp"

namespace solidfuel {

void ButtonGroupComponent::paint(juce::Graphics& g) {
    if (draw_border_) {
        getLookAndFeel().drawGroupComponentOutline (g, getWidth(), getHeight(),
                                            getText(), getTextLabelPosition(), *this);
    } else {
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    }

}

void ButtonGroupComponent::resized() {
    
    juce::Grid grid;
 
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;
    using GridItem = juce::GridItem;

    grid.alignItems = juce::Grid::AlignItems::center;
    grid.justifyContent = juce::Grid::JustifyContent::start;
    grid.justifyItems = juce::Grid::JustifyItems::start;

    juce::Array<Track> layout;
    layout.resize(getNumChildComponents());
    layout.fill(Track(Fr(1)));

    if (orient_ == Horizontal) { 
        grid.templateColumns.addArray(layout);
        grid.templateRows.add(Track (Fr (1)));

    } else {
        grid.templateRows.addArray(layout);
        grid.templateColumns.add(Track (Fr (1)));
    }

    using Conn = juce::Button::ConnectedEdgeFlags;
    Conn first_flag;
    Conn last_flag;

    if (orient_ == Horizontal) {
        first_flag = Conn::ConnectedOnRight;
        last_flag = Conn::ConnectedOnLeft;
    } else {
        first_flag = Conn::ConnectedOnBottom;
        last_flag = Conn::ConnectedOnTop;

    }


    for(auto *c : buttons) {
        if (grid.items.isEmpty()) {
            c->setConnectedEdges(first_flag);
        } else if (grid.items.size() == buttons.size()-1) {
            c->setConnectedEdges(last_flag);
        } else {
            c->setConnectedEdges( first_flag | last_flag);
        }

        grid.items.add(GridItem(c));
    }

    auto bounds = getLocalBounds();
    if (draw_border_) {
        bounds = bounds.reduced(5);
        bounds.removeFromTop(10);
    }

    bounds.removeFromTop(margin_.top);
    bounds.removeFromBottom(margin_.bottom);
    bounds.removeFromLeft(margin_.left);
    bounds.removeFromRight(margin_.right);
    
    grid.performLayout (bounds);

}

} // namespace
