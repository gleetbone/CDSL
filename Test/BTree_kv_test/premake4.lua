#!lua

local name = "BTree_kv_test"

-- A solution contains projects, and defines the available configurations
solution( name )
   configurations { "Debug", "Release" }
   location "build"

   -- A project defines one build target
   project( name )
      kind "ConsoleApp"
      language "C"
      files { "../../base/*.c", "src/*.c", "../../String/*.c", "../../Protocol_Base/*.c", "../../Common/P_Basic/*.c", "../../Common/P_Iterable_kv/*.c", "../../Common/P_DIterable_kv/*.c"  }
      links { "cunit", "m", "rt", "gc", "gcov", "pthread" }
      includedirs { "src", "../../base", "../../dbc", "../../BTree_kv", "../../String", "../../Protocol_Base", "../../P_Indexable", "../../P_Iterable", "../../P_Iterable_kv", "../../P_DIterable", "../../P_DIterable_kv", "../../P_Basic", "../../P_Searcher", "../../P_Sorter", "../../Common/P_Basic", "../../Common/P_Iterable_kv", "../../Common/P_DIterable_kv"  }

      -- A configuration defines one way a project can be built
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
         buildoptions { "-O0", "-g3", "-Wall", "-ftest-coverage", "-fprofile-arcs" }

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }


