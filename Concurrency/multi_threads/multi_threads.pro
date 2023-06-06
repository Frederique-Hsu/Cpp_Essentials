TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest

SOURCES += \
        avoid_data_race/mutual_exclusion.cpp \
        avoid_data_race/test_mutual_exclusion.c++ \
        main.cpp \
        producer_consumer.cpp \
        test_producer_consumer.c++ \
        test_threads.c++ \
        threads.cpp \
        utils.cpp

HEADERS += \
    avoid_data_race/mutual_exclusion.hpp \
    condition_variable/sync_queue.hpp \
    producer_consumer.hpp \
    test_threads.h++ \
    threads.hpp \
    utils.hpp
