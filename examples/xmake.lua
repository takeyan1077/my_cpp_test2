add_rules("mode.release", "mode.debug")
add_languages("c++20")

target("example")
	add_files("*.cpp")
	add_includedirs("..")
