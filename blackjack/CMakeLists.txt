add_library(blackjack "")
target_sources(blackjack
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/Deck.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Card.cpp
)

target_include_directories(blackjack
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${PROJECT_BINARY_DIR}
  ${PROJECT_DIR}/external
)

target_compile_options(blackjack PRIVATE $<$<CONFIG:Debug>:
  -Wall -Wextra -pedantic-errors -Wconversion -Wsign-conversion -g
  >)
