#pragma once
#include <meta>
#include <type_traits>
template <typename T, std::meta::info Template>
concept SpecializationOf = std::meta::has_template_arguments(^^T) &&
                           std::meta::template_of(^^T) == Template;
