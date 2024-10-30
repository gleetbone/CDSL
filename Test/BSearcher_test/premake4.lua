#!lua

local name = "BSearcher_test"

-- A solution contains projects, and defines the available configurations
solution( name )
   configurations { "Debug", "Release" }
   location "build"

   -- A project defines one build target
   project( name )
      kind "ConsoleApp"
      language "C"
      files { "src/*.c", "../../Protocol_Base/*.c", "../../Common/Sequence/*.c", "../../Common/P_Indexable/*.c", "../../String/*.c" }
      links { "cunit", "m", "rt", "gc", "gcov", "pthread" }
      includedirs { "src", "../../base", "../../dbc", "../../BSearcher", "../../Protocol_Base", "../../P_Indexable", "../../P_Iterable", "../../P_Iterable_kv", "../../P_DIterable", "../../P_DIterable_kv", "../../P_Clonable", "../../P_Searcher", "../../P_Sorter", "../../P_Basic", "../../Sequence", "../../Common/Sequence", "../../Common/P_Indexable", "../../String"  }

      -- A configuration defines one way a project can be built
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
         buildoptions { "-O0", "-g3", "-Wall", "-ftest-coverage", "-fprofile-arcs" }

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }


