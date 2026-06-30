add_subdirectory(C++)

function(kde_test_app_template)
    set(_oneValueArgs TEMPLATE NAME)
    cmake_parse_arguments(ARG "" "${_oneValueArgs}" "" ${ARGN})
    string(TOLOWER ${ARG_NAME} _lc_app_name)

    # if we use a template we build ourselves, add a proper dependency to it
    if (TARGET ${ARG_TEMPLATE}_kapptemplate)
        set(_depends_args DEPENDS ${CMAKE_BINARY_DIR}/${KDE_INSTALL_KAPPTEMPLATESDIR}/${ARG_TEMPLATE}.tar.bz2)
    endif()

    # run kapptemplate to expand the template
    # adjust the environment variable accordingly to also find templates in our build dir
    add_custom_target(${ARG_TEMPLATE}_${ARG_NAME}_generated ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/template-test/${ARG_TEMPLATE}/${_lc_app_name}/CMakeLists.txt)
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/template-test/${ARG_TEMPLATE}/${_lc_app_name}/CMakeLists.txt
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/template-test/${ARG_TEMPLATE}/${_lc_app_name}"
        COMMAND ${CMAKE_COMMAND} -E env --modify "XDG_DATA_DIRS=path_list_prepend:${CMAKE_BINARY_DIR}/${KDE_INSTALL_DATAROOTDIR}"
            $<TARGET_FILE:kapptemplate> ARGS
            -platform offscreen
            "${ARG_NAME}"
            "${CMAKE_CURRENT_BINARY_DIR}/template-test/${ARG_TEMPLATE}"
            "Au Thor"
            "null@kde.org"
            "42.23.0"
            ${ARG_TEMPLATE}
        ${_depends_args}
    )
    add_dependencies(${ARG_TEMPLATE}_${ARG_NAME}_generated kapptemplate)
    if(TARGET ${ARG_TEMPLATE}_kapptemplate)
        add_dependencies(${ARG_TEMPLATE}_${ARG_NAME}_generated ${ARG_TEMPLATE}_kapptemplate)
    endif()

    # run cmake on the expanded template and compile it
    add_test(TemplateTest_${ARG_TEMPLATE}_${ARG_NAME} ${CMAKE_CTEST_COMMAND}
        --build-and-test
        "${CMAKE_CURRENT_BINARY_DIR}/template-test/${ARG_TEMPLATE}/${_lc_app_name}"
        "${CMAKE_CURRENT_BINARY_DIR}/template-build/${ARG_TEMPLATE}/${_lc_app_name}"
        --build-generator ${CMAKE_GENERATOR}
        --build-makeprogram ${CMAKE_MAKE_PROGRAM}
        --build-noclean
    )

    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES template-test template-build)
endfunction()

if(BUILD_TESTING AND NOT WIN32 AND ECM_VERSION VERSION_GREATER_EQUAL 6.28)
    kde_test_app_template(TEMPLATE kde-frameworks6-simple NAME TestApp)
    #kde_test_app_template(TEMPLATE kde-frameworks6 NAME TestApp) missing dependencies on the CI

    kde_test_app_template(TEMPLATE kirigami6 NAME TestApp)
    kde_test_app_template(TEMPLATE kirigamiaddons6 NAME TestApp)
endif()
