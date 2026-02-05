set_project("LeetCode")

add_rules("mode.debug", "mode.release")
set_languages("cxx23")
set_encodings("utf-8")

target("AlignTheTextLeftAndRight")
    set_kind("binary")
    add_files("AlignTheTextLeftAndRight.cpp")
target_end()

target("TrappingRainWater")
    set_kind("binary")
    add_files("TrappingRainWater.cpp")
target_end()

target("Loot")
    set_kind("binary")
    add_files("Loot.cpp")
target_end()

target("TheNumberOfIslands")
    set_kind("binary")
    add_files("TheNumberOfIslands.cpp")
target_end()