set_languages("c11", "cxx23")
set_encodings("utf-8")
add_rules("mode.debug", "mode.release")

target("H-Index")
    set_kind("binary")
    add_files("H-Index.cpp")
target_end()

target("DesignAddAndSearchWordsDataStructure")
    set_kind("binary")
    add_files("DesignAddAndSearchWordsDataStructure.cpp")
target_end()

target("Pow")
    set_kind("binary")
    add_files("Pow.cpp")
target_end()

target("MinimumNumberOfArrowsToBurstBalloons")
    set_kind("binary")
    add_files("MinimumNumberOfArrowsToBurstBalloons.cpp")
target_end()

target("CloneGraph")
    set_kind("binary")
    add_files("CloneGraph.cpp")
target_end()

target("EvaluateReversePolishNotation")
    set_kind("binary")
    add_files("EvaluateReversePolishNotation.cpp")
target_end()

target("RotateImage")
    set_kind("binary")
    add_files("RotateImage.cpp")
target_end()

target("Combinations")
    set_kind("binary")
    add_files("Combinations.cpp")
target_end()

target("RemoveDuplicatesFromSortedArrayII")
    set_kind("binary")
    add_files("RemoveDuplicatesFromSortedArrayII.cpp")
target_end()

target("IPO")
    set_kind("binary")
    add_files("IPO.cpp")
target_end()