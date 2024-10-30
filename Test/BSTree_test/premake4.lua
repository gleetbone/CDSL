#!lua

local name = "BSTree_test"

-- A solution contains projects, and defines the available configurations
solution( name )
   configurations { "Debug", "Release" }
   location "build"

   -- A project defines one build target
   project( name )
      kind "ConsoleApp"
      language "C"
      files { "../../base/*.c", "src/*.c", "../../Protocol_Base/*.c", "../../String/*.c", "../../Common/P_Basic/*.c", "../../Common/P_Iterable/*.c", "../../Common/P_DIterable/*.c" }
      links { "cunit", "m", "rt", "gc", "gcov", "pthread" }
      includedirs { "src", "../../base", "../../dbc", "../../BSTree", "../../Protocol_Base", "../../P_Indexable", "../../P_Iterable", "../../P_Iterable", "../../P_DIterable", "../../P_DIterable", "../../P_Basic", "../../P_Searcher", "../../P_Sorter", "../../String", "../../Common/P_Basic", "../../Common/P_Iterable", "../../Common/P_DIterable"  }

      -- A configuration defines one way a project can be built
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
         buildoptions { "-O0", "-g3", "-Wall", "-ftest-coverage", "-fprofile-arcs" }

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }


