#!lua

local name = "Configuration_test"

-- A solution contains projects, and defines the available configurations
solution( name )
   configurations { "Debug", "Release" }
   location "build"

   -- A project defines one build target
   project( name )
      kind "ConsoleApp"
      language "C"
      files { "../../base/*.c", "src/*.c", "../../Configuration/*.c", "../../String/*.c", "../../Common/DList/*.c", "../../Common/HTable/*.c", "../../Common/P_Basic/*.c", "../../Protocol_Base/*.c", "../../Input_File_Reader/*.c" }
      links { "cunit", "m", "rt", "gc", "gcov", "pthread" }
      includedirs { "src", "../../base", "../../dbc", "../../Configuration", "../../Common/DList", "../../Common/HTable", "../../Common/P_Basic", "../../Protocol_Base", "../../P_Indexable", "../../P_Iterable", "../../P_Iterable_kv", "../../P_DIterable", "../../P_DIterable_kv", "../../P_Basic", "../../P_Searcher", "../../P_Sorter", "../../String", "../../Input_File_Reader", "../../DList", "../../HTable"  }

      -- A configuration defines one way a project can be built
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
         buildoptions { "-O0", "-g3", "-Wall", "-ftest-coverage", "-fprofile-arcs" }

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }


