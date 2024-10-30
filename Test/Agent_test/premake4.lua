#!lua

local name = "Agent_test"

-- A solution contains projects, and defines the available configurations
solution( name )
   configurations { "Debug", "Release" }
   location "build"

   -- A project defines one build target
   project( name )
      kind "ConsoleApp"
      language "C"
      files { "../../base/*.c", "src/*.c", "../../Agent/*.c" }
      links { "cunit", "m", "rt", "gc", "gcov", "pthread" }
      includedirs { "src", "../../base", "../../dbc", "../../Agent" }

      -- A configuration defines one way a project can be built
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
         buildoptions { "-O0", "-g3", "-Wall", "-ftest-coverage", "-fprofile-arcs" }

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }


