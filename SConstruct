VariantDir('build', 'src')
env = Environment()
env.Program("pat",
    Glob("src/*.cpp"),
    CCFLAGS = ['-g', '-O0', '-Wall', '-std=c++11'],
    CPPPATH = [
        './include',
        ],
    LDFLAGS ='-g',
    LIBS=['glog', ],
)
