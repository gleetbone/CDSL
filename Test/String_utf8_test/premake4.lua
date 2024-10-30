#!lua

local name = "String_utf8_test"

-- A solution contains projects, and defines the available configurations
solution( name )
   configurations { "Debug", "Release" }
   location "build"

   -- A project defines one build target
   project( name )
      kind "ConsoleApp"
      language "C"
      files { "src/*.c", "../../String_utf8/*.c", "../../Protocol_Base/*.c" }
      links { "cunit", "m", "rt", "gc", "gcov", "pthread", "utf8rewind" }
      includedirs { "src", "../../base", "../../dbc", "../../String_utf8", "../../Protocol_Base", "../../P_Indexable", "../../P_Iterable", "../../P_Iterable_kv", "../../P_DIterable", "../../P_DIterable_kv", "../../P_Clonable", "../../P_Searcher", "../../P_Sorter", "../../utf8"  }

      -- A configuration defines one way a project can be built
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
         buildoptions { "-O0", "-g3", "-Wall", "-ftest-coverage", "-fprofile-arcs" }

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }


