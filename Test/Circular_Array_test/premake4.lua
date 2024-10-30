#!lua

local name = "Circular_Array_test"

-- A solution contains projects, and defines the available configurations
solution( name )
   configurations { "Debug", "Release" }
   location "build"

   -- A project defines one build target
   project( name )
      kind "ConsoleApp"
      language "C"
      files { "../../base/*.c", "src/*.c", "../../String/*.c", "../../Common/Circular_Array/*.c", "../../Common/P_Basic/*.c", "../../Common/P_Indexable/*.c", "../../Protocol_Base/*.c" }
      links { "cunit", "m", "rt", "gc", "gcov", "pthread" }
      includedirs { "src", "../../base", "../../dbc", "../../Circular_Array", "../../Common/Circular_Array", "../../Common/P_Basic", "../../Common/P_Indexable", "../../Protocol_Base", "../../P_Indexable", "../../P_Basic", "../../String" }

      -- A configuration defines one way a project can be built
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
         buildoptions { "-O0", "-g3", "-Wall", "-ftest-coverage", "-fprofile-arcs" }

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }


