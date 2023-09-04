# Write some temp files to make GitHub Actions / packaging easy

if ((DEFINED ENV{CI}))
    set (env_file "${CMAKE_CURRENT_LIST_DIR}/.pamplejuce_env")
    message ("Writing ENV file for CI: ${env_file}")
    file(APPEND env_file "${PROJECT_NAME}\\n")
    file(APPEND env_file "${PRODUCT_NAME}\\n")
    file(APPEND env_file "${BUNDLE_ID}\\n")
    file(APPEND env_file "${COMPANY_NAME}\\n")
endif ()