Import('env')

env.Append(CPPPATH=[[env.Dir(d) for d in ["include"]]])

sources = [
  "src/IOStreamLogger.cpp",
  "src/Logger.cpp"
]

library = env.Library("build/gog43", source=sources)

Default(library)
Return("library")