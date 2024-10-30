#!lua

local name = "HSorter_test"

-- A solution contains projects, and defines the available configurations
solution( name )
   configurations { "Debug", "Release" }
   location "build"

   -- A project defines one build target
   project( name )
      kind "ConsoleApp"
      language "C"
      files { "src/*.c", "../../Protocol_Base/*.c" }
      links { "cunit", "m", "rt", "gc", "gcov", "pthread" }
      includedirs { "src", "../../base", "../../dbc", "../../HSorter", "../../Protocol_Base", "../../P_Indexable", "../../P_Basic", "../../P_Iterable", "../../P_Iterable_kv", "../../P_DIterable", "../../P_DIterable_kv", "../../P_Clonable", "../../P_Searcher", "../../P_Sorter", "../../Sequence"  }

      -- A configuration defines one way a project can be built
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
         buildoptions { "-O0", "-g3", "-Wall", "-ftest-coverage", "-fprofile-arcs" }

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }


