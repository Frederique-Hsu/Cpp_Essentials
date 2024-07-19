TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lCatch2

DEFINES += DEBUG


# Search all the code files under the specified directory
root_dir = .

# Recursively search the source, header files, and concatenate them respectively
for(subdir, root_dir) {
        SOURCES += $$files($$join(subdir, , , /*.cpp), true)
        SOURCES += $$files($$join(subdir, , , /*.c++), true)
        SOURCES += $$files($$join(subdir, , , /*.c), true)
        HEADERS += $$files($$join(subdir, , , /*.hpp), true)
        HEADERS += $$files($$join(subdir, , , /*.h++), true)
        HEADERS += $$files($$join(subdir, , , /*.h), true)
        # FORMS   += $$files($$join(subdir, , , /*.ui), true)
}

DISTFILES += \
    CMakeLists.txt
