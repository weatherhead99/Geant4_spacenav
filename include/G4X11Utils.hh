#pragma once

#include <tuple>
#include <X11/Xlib.h>

class G4UImanager;
class G4UIQt;

std::tuple<Display*, Window> GetX11Info(G4UImanager* uiman);

std::tuple<Display*, Window> GetX11Info(G4UIQt* ui);
