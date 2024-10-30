#!lua

local name = "Command_Line_Handler_test"

-- A solution contains projects, and defines the available configurations
solution( name )
   configurations { "Debug", "Release" }
   location "build"

   -- A project defines one build target
   project( name )
      kind "ConsoleApp"
      language "C"
      files { "../../base/*.c", "src/*.c", "../../Protocol_Base/*.c", "../../Command_Line_Handler/*.c", "../../String/*.c" }
      links { "cunit", "m", "rt", "gc", "gcov", "pthread" }
      includedirs { "src", "../../base", "../../dbc", "../../Org_Mode", "../../Protocol_Base", "../../P_Indexable", "../../P_Iterable", "../../P_Iterable_kv", "../../P_DIterable", "../../P_DIterable_kv", "../../P_Basic", "../../P_Searcher", "../../P_Sorter", "../../P_Command_Line_Handler", "../../String", "../../AList", "../../DList", "../../HSet", "../../HTable", "../../Sequence", "../../Command_Line_Handler"  }

      -- A configuration defines one way a project can be built
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
         buildoptions { "-O0", "-g3", "-Wall", "-ftest-coverage", "-fprofile-arcs" }

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }


