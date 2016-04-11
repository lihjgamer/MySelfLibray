solution "LibraryTest"
location "../"
configurations { "Debug", "Release" } 

-- 这里是相对于解决方案的配置目录 还是 当前 premake 的目录 ？？？？？？ 测试后给出答案
-- 答案 : 所有的路径都是相对于premake4 的路径
includedirs {
"../LibraryTest",
"../Library/include/logger",
"../Library/include/mem_pool",
"../Library/include/sql",
"../Library/include/thread",
"../Library/include/time",
"../Library/include/net",
"../Library/src/logger",
"../Library/src/mem_pool",
"../Library/src/sql",
"../Library/src/thread",
"../Library/src/time",
"../Library/src/net",
"../Depend/mysql/include"
}
defines{"_DEBUG","WIN32","_WINDOWS"}
        
language "C++"
project "LibraryTest"
location "../LibraryTest"
kind "ConsoleApp"
links {"Library","libmysql"}
files { "../LibraryTest/**.h", "../LibraryTest/**.cpp"}
libdirs{"../Debug"}
targetdir "../Debug"
debugdir "../Debug"	-- 工作目录
configuration "Debug"
defines { "DEBUG" }
flags { "Symbols" }

configuration "Release"
defines { "NDEBUG" }
flags { "Optimize" }

project "Library"
location "../Library"
kind "StaticLib"
excludes{
"./LibraryTest",
}
targetdir "../Debug"
targetname "Library"
files { "../Library/include/**.h", "../Library/src/**.cpp","../Depend/mysql/include/**.h"}

configuration "Debug"
flags { "Symbols" }

configuration "Release"
defines { "NDEBUG" }
flags { "Optimize" }
