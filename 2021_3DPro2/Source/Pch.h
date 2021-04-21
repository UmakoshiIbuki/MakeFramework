#pragma once

#define NOMINMAX		// Min Maxマクロの無効化：勝手にwindowsのMin Maxに置換されるのを防止

#include <SDKDDKVer.h> // 最新のSDKを自動的に定義する
#include <windows.h>

// C Liblary ===== ===== ===== ===== ===== =====
#include <cassert>

// C++ Liblary ===== ===== ===== ===== ===== =====
// General
#include <chrono>
#include <memory>

// Stream IO
#include <filesystem>
#include <sstream>
#include <iostream>
#include <istream>

// Thread
#include <thread>
#include <mutex>

// Numerical processing
#include <random>

// STL
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <array>
#include <string>
#include <algorithm>


#include"Framework//UmaFramework.h"