set(namevalidatortest_SOURCES namevalidatortest.cpp)

kde4_add_unit_test(namevalidatortest ${namevalidatortest_SOURCES})
target_link_libraries(namevalidatortest ${KDE4_KDECORE_LIBS} ${QT_QTTEST_LIBRARY})