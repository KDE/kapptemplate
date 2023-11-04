ecm_add_test(namevalidatortest.cpp
    LINK_LIBRARIES
        Qt6::Core
        Qt6::Test
)

ecm_add_test(macrosubstitutiontest.cpp
    LINK_LIBRARIES
        KF6::CoreAddons
        Qt6::Core
        Qt6::Test
)
