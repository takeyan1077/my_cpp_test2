add_rules("mode.release", "mode.debug")
add_languages("c++23")

target("example")
	add_files("*.cpp")
	add_includedirs("..")
	add_tests("test example")
