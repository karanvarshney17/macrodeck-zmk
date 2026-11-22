# Macrodeck extra firmware code (this repo is also a Zephyr module)
if(CONFIG_MACRODECK_POWER_STATUS)
  target_sources(app PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src/power_status.c)
endif()
