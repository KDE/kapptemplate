ecm_add_test(namevalidatortest.cpp
    LINK_LIBRARIES
        Qt${QT_MAJOR_VERSION}::Core
        Qt${QT_MAJOR_VERSION}::Test
)

ecm_add_test(macrosubstitutiontest.cpp
    LINK_LIBRARIES
        KF5::CoreAddons
        Qt${QT_MAJOR_VERSION}::Core
        Qt${QT_MAJOR_VERSION}::Test
)
